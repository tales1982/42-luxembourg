import { COLS, ROWS } from '../shared/board.js';
import { EVENTS } from '../shared/events.js';
import Game from './Game.js';
import Player from './Player.js';

export const INITIAL_PIECES = 14;
export const PIECES_BATCH = 7;
const MAX_PIECE_INDEX = 100000;
const NAME_PATTERN = /^[\w-]{1,16}$/;

const isValidSpectrum = (spectrum) =>
  Array.isArray(spectrum) &&
  spectrum.length === COLS &&
  spectrum.every((h) => Number.isInteger(h) && h >= 0 && h <= ROWS);

export const registerSocketHandlers = (io, games = new Map()) => {
  const broadcastState = (game) => io.to(game.name).emit(EVENTS.ROOM_STATE, game.toJSON());

  const endIfOver = (game) => {
    if (game.checkEnd()) io.to(game.name).emit(EVENTS.GAME_OVER, { winner: game.winner });
  };

  io.on('connection', (socket) => {
    let current = null; // { game, player }

    const fail = (message) => socket.emit(EVENTS.ROOM_ERROR, { message });
    const inGame = (handler) => (payload) => {
      if (current) handler(current.game, current.player, payload ?? {});
    };

    const leave = () => {
      if (!current) return;
      const { game, player } = current;
      current = null;
      socket.leave(game.name);
      game.removePlayer(player.id);
      if (game.isEmpty()) {
        games.delete(game.name);
        return;
      }
      endIfOver(game);
      broadcastState(game);
    };

    socket.on(EVENTS.JOIN, (payload) => {
      const { room, name } = payload ?? {};
      if (current) return fail('Already in a room');
      if (!NAME_PATTERN.test(room ?? '') || !NAME_PATTERN.test(name ?? '')) {
        return fail('Invalid room or player name (1-16 chars: letters, digits, _ or -)');
      }
      const game = games.get(room) ?? new Game(room);
      const player = new Player(socket.id, name);
      try {
        game.addPlayer(player);
      } catch (err) {
        return fail(err.message);
      }
      games.set(room, game);
      socket.join(room);
      current = { game, player };
      broadcastState(game);
    });

    socket.on(EVENTS.LEAVE, leave);
    socket.on('disconnect', leave);

    socket.on(
      EVENTS.START,
      inGame((game, player) => {
        try {
          game.start(player.id);
        } catch (err) {
          return fail(err.message);
        }
        io.to(game.name).emit(EVENTS.GAME_STARTED, { pieces: game.getPieces(0, INITIAL_PIECES) });
        broadcastState(game);
      }),
    );

    socket.on(
      EVENTS.PIECES_REQUEST,
      inGame((game, _player, { index }) => {
        if (game.status !== 'playing' || !Number.isInteger(index) || index < 0 || index > MAX_PIECE_INDEX) return;
        socket.emit(EVENTS.PIECES, { index, pieces: game.getPieces(index, PIECES_BATCH) });
      }),
    );

    socket.on(
      EVENTS.SPECTRUM,
      inGame((game, player, { spectrum }) => {
        if (!isValidSpectrum(spectrum)) return;
        player.spectrum = spectrum;
        broadcastState(game);
      }),
    );

    socket.on(
      EVENTS.LINES,
      inGame((game, player, { count }) => {
        if (game.status !== 'playing' || !player.alive || !Number.isInteger(count) || count < 2 || count > 4) return;
        game.opponentsOf(player.id).forEach((o) => io.to(o.id).emit(EVENTS.PENALTY, { lines: count - 1 }));
      }),
    );

    socket.on(
      EVENTS.LOST,
      inGame((game, player) => {
        if (game.status !== 'playing') return;
        game.playerLost(player.id);
        endIfOver(game);
        broadcastState(game);
      }),
    );
  });

  return games;
};
