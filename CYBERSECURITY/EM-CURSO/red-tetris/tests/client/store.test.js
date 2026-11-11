import { describe, expect, it, vi } from 'vitest';
import { EVENTS } from '../../src/shared/events.js';
import { createAppStore } from '../../src/client/store/index.js';
import {
  errorReceived, gameOver, gameStarted, piecesReceived, roomStateReceived, selectMe, selectOpponents,
} from '../../src/client/store/gameSlice.js';
import { bindSocket } from '../../src/client/store/socketListeners.js';
import { joinRoom, leaveRoom, playerAction, receivePenalty, startGame } from '../../src/client/store/thunks.js';

const piece = (type) => ({ type, x: type === 'O' ? 4 : 3, y: type === 'I' ? -1 : 0 });
const fakeSocket = () => {
  const handlers = {};
  return {
    emit: vi.fn(),
    on: (event, fn) => {
      handlers[event] = fn;
    },
    fire: (event, data) => handlers[event](data),
  };
};
const setup = () => {
  const socket = fakeSocket();
  const store = createAppStore(socket);
  bindSocket(socket, store);
  return { socket, store, game: () => store.getState().game };
};
const players = [
  { id: '1', name: 'alice', isHost: true, alive: true, spectrum: Array(10).fill(0) },
  { id: '2', name: 'bob', isHost: false, alive: true, spectrum: Array(10).fill(0) },
];

describe('client store', () => {
  it('joins, receives room state and leaves', () => {
    const { socket, store, game } = setup();
    store.dispatch(joinRoom('r', 'alice'));
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.JOIN, { room: 'r', name: 'alice' });
    socket.fire(EVENTS.ROOM_STATE, { status: 'waiting', players });
    expect(selectMe(store.getState()).isHost).toBe(true);
    expect(selectOpponents(store.getState()).map((p) => p.name)).toEqual(['bob']);
    socket.fire(EVENTS.ROOM_ERROR, { message: 'boom' });
    expect(game().error).toBe('boom');
    store.dispatch(startGame());
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.START);
    store.dispatch(leaveRoom());
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.LEAVE);
    expect(game().room).toBeNull();
    expect(selectMe(store.getState())).toBeNull();
  });

  it('plays: moves, locks, sends spectrum and requests pieces', () => {
    const { socket, store, game } = setup();
    store.dispatch(joinRoom('r', 'alice'));
    socket.fire(EVENTS.GAME_STARTED, { pieces: [piece('T'), piece('O')] });
    expect(game().engine.piece.type).toBe('T');

    store.dispatch(playerAction('left'));
    expect(game().engine.piece.x).toBe(2);

    store.dispatch(playerAction('drop'));
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.SPECTRUM, { spectrum: [0, 0, 1, 2, 1, 0, 0, 0, 0, 0] });
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.PIECES_REQUEST, { index: 2 });
    expect(game().pendingRequest).toBe(true);

    socket.fire(EVENTS.PIECES, { index: 2, pieces: [piece('I')] });
    expect(game().pendingRequest).toBe(false);
    expect(game().engine.pieces).toHaveLength(3);
  });

  it('sends cleared lines and loses on penalty overflow', () => {
    const { socket, store, game } = setup();
    store.dispatch(joinRoom('r', 'alice'));
    socket.fire(EVENTS.GAME_STARTED, { pieces: [piece('O'), piece('T')] });
    const almostFull = Array.from({ length: 20 }, (_, r) => (r >= 18 ? [...Array(8).fill('Z'), 0, 0] : Array(10).fill(0)));
    store.dispatch({ type: 'game/engineUpdated', payload: { ...game().engine, board: almostFull, piece: { type: 'O', x: 8, y: 0, rotation: 0 } } });
    store.dispatch(playerAction('drop'));
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.LINES, { count: 2 });

    socket.fire(EVENTS.PENALTY, { lines: 25 });
    expect(game().engine.status).toBe('lost');
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.LOST);

    socket.fire(EVENTS.GAME_OVER, { winner: 'bob' });
    expect(game().roomStatus).toBe('finished');
    expect(game().winner).toBe('bob');
  });

  it('ignores actions without a running engine', () => {
    const { store, game } = setup();
    store.dispatch(playerAction('left'));
    store.dispatch(receivePenalty(2));
    store.dispatch(piecesReceived({ index: 0, pieces: [] }));
    expect(game().engine).toBeNull();
  });

  it('exposes plain action creators', () => {
    expect(gameStarted([]).type).toBe('game/gameStarted');
    expect(roomStateReceived({}).type).toBe('game/roomStateReceived');
    expect(errorReceived('x').payload).toBe('x');
    expect(gameOver({ winner: null }).payload).toEqual({ winner: null });
  });
});
