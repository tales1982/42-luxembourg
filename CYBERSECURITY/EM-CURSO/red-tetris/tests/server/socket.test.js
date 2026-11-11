import { afterEach, beforeEach, describe, expect, it } from 'vitest';
import { io as connect } from 'socket.io-client';
import { createServer } from '../../src/server/app.js';
import { INITIAL_PIECES, PIECES_BATCH } from '../../src/server/socket.js';
import { EVENTS } from '../../src/shared/events.js';

let server;
let url;
const clients = [];

const client = () => {
  const socket = connect(url, { transports: ['websocket'], forceNew: true });
  clients.push(socket);
  return socket;
};
const once = (socket, event) => new Promise((resolve) => socket.once(event, resolve));
const waitFor = (socket, event, predicate) =>
  new Promise((resolve) => {
    const handler = (data) => {
      if (!predicate(data)) return;
      socket.off(event, handler);
      resolve(data);
    };
    socket.on(event, handler);
  });
const join = async (room, name) => {
  const socket = client();
  const state = once(socket, EVENTS.ROOM_STATE);
  socket.emit(EVENTS.JOIN, { room, name });
  await state;
  return socket;
};

beforeEach(async () => {
  server = createServer();
  await new Promise((resolve) => server.httpServer.listen(0, resolve));
  url = `http://localhost:${server.httpServer.address().port}`;
});

afterEach(async () => {
  clients.splice(0).forEach((s) => s.disconnect());
  await new Promise((resolve) => server.io.close(resolve));
});

describe('socket protocol', () => {
  it('rejects invalid names and duplicate joins', async () => {
    const socket = client();
    const error = once(socket, EVENTS.ROOM_ERROR);
    socket.emit(EVENTS.JOIN, { room: 'bad room!', name: 'a' });
    expect((await error).message).toMatch(/Invalid/);

    const ok = await join('r1', 'alice');
    const dup = once(ok, EVENTS.ROOM_ERROR);
    ok.emit(EVENTS.JOIN, { room: 'r1', name: 'alice' });
    expect((await dup).message).toMatch(/Already/);

    const other = client();
    const taken = once(other, EVENTS.ROOM_ERROR);
    other.emit(EVENTS.JOIN, { room: 'r1', name: 'alice' });
    expect((await taken).message).toMatch(/taken/);
  });

  it('plays a full multiplayer round', async () => {
    const alice = await join('r2', 'alice');
    const bob = await join('r2', 'bob');

    const notHost = once(bob, EVENTS.ROOM_ERROR);
    bob.emit(EVENTS.START);
    expect((await notHost).message).toMatch(/host/);

    const startedA = once(alice, EVENTS.GAME_STARTED);
    const startedB = once(bob, EVENTS.GAME_STARTED);
    alice.emit(EVENTS.START);
    const [a, b] = await Promise.all([startedA, startedB]);
    expect(a.pieces).toHaveLength(INITIAL_PIECES);
    expect(a.pieces).toEqual(b.pieces);

    const late = client();
    const lateError = once(late, EVENTS.ROOM_ERROR);
    late.emit(EVENTS.JOIN, { room: 'r2', name: 'carol' });
    expect((await lateError).message).toMatch(/progress/);

    const more = once(alice, EVENTS.PIECES);
    alice.emit(EVENTS.PIECES_REQUEST, { index: INITIAL_PIECES });
    expect((await more).pieces).toHaveLength(PIECES_BATCH);

    const penalty = once(bob, EVENTS.PENALTY);
    alice.emit(EVENTS.LINES, { count: 3 });
    expect(await penalty).toEqual({ lines: 2 });

    const spectrum = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    const updated = waitFor(bob, EVENTS.ROOM_STATE, (s) => s.players[0].spectrum[9] === 10);
    alice.emit(EVENTS.SPECTRUM, { spectrum });
    expect((await updated).players[0].spectrum).toEqual(spectrum);

    const over = once(alice, EVENTS.GAME_OVER);
    bob.emit(EVENTS.LOST);
    expect(await over).toEqual({ winner: 'alice' });
  });

  it('transfers host and ends the game when a player leaves', async () => {
    const alice = await join('r3', 'alice');
    const bob = await join('r3', 'bob');
    const started = once(bob, EVENTS.GAME_STARTED);
    alice.emit(EVENTS.START);
    await started;

    const over = once(bob, EVENTS.GAME_OVER);
    const state = waitFor(bob, EVENTS.ROOM_STATE, (s) => s.players.length === 1);
    alice.emit(EVENTS.LEAVE);
    expect(await over).toEqual({ winner: 'bob' });
    expect((await state).players[0].isHost).toBe(true);

    bob.disconnect();
    await new Promise((resolve) => setTimeout(resolve, 50));
    expect(server.games.has('r3')).toBe(false);
  });

  it('ignores invalid payloads', async () => {
    const alice = await join('r4', 'alice');
    alice.emit(EVENTS.PIECES_REQUEST, { index: 0 }); // not playing
    alice.emit(EVENTS.SPECTRUM, { spectrum: 'nope' });
    alice.emit(EVENTS.LINES, { count: 9 });
    alice.emit(EVENTS.LOST);
    const outsider = client();
    outsider.emit(EVENTS.START);
    await new Promise((resolve) => setTimeout(resolve, 50));
    expect(server.games.get('r4').status).toBe('waiting');
  });
});
