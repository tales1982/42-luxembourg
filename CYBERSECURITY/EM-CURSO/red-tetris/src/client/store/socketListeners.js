import { EVENTS } from '../../shared/events.js';
import { errorReceived, gameOver, gameStarted, piecesReceived, roomStateReceived } from './gameSlice.js';
import { receivePenalty } from './thunks.js';

export const bindSocket = (socket, { dispatch }) => {
  socket.on(EVENTS.ROOM_STATE, (state) => dispatch(roomStateReceived(state)));
  socket.on(EVENTS.ROOM_ERROR, ({ message }) => dispatch(errorReceived(message)));
  socket.on(EVENTS.GAME_STARTED, ({ pieces }) => dispatch(gameStarted(pieces)));
  socket.on(EVENTS.PIECES, (payload) => dispatch(piecesReceived(payload)));
  socket.on(EVENTS.PENALTY, ({ lines }) => dispatch(receivePenalty(lines)));
  socket.on(EVENTS.GAME_OVER, ({ winner }) => dispatch(gameOver({ winner })));
};
