import { getSpectrum } from '../../shared/board.js';
import { applyPenalty, step } from '../../shared/engine.js';
import { EVENTS } from '../../shared/events.js';
import { engineUpdated, joined, left, piecesRequested } from './gameSlice.js';

const REFILL_THRESHOLD = 5;

export const joinRoom = (room, playerName) => (dispatch, _getState, { socket }) => {
  dispatch(joined({ room, playerName }));
  socket.emit(EVENTS.JOIN, { room, name: playerName });
};

export const leaveRoom = () => (dispatch, _getState, { socket }) => {
  socket.emit(EVENTS.LEAVE);
  dispatch(left());
};

export const startGame = () => (_dispatch, _getState, { socket }) => {
  socket.emit(EVENTS.START);
};

// Stores a new engine state and tells the server what changed.
export const commitEngine =
  (next, { cleared = 0 } = {}) =>
  (dispatch, getState, { socket }) => {
    const { engine: prev, pendingRequest } = getState().game;
    dispatch(engineUpdated(next));
    if (next.board !== prev.board) socket.emit(EVENTS.SPECTRUM, { spectrum: getSpectrum(next.board) });
    if (cleared > 1) socket.emit(EVENTS.LINES, { count: cleared });
    if (prev.status === 'playing' && next.status === 'lost') socket.emit(EVENTS.LOST);
    if (next.status === 'playing' && !pendingRequest && next.pieces.length - next.pieceIndex < REFILL_THRESHOLD) {
      dispatch(piecesRequested());
      socket.emit(EVENTS.PIECES_REQUEST, { index: next.pieces.length });
    }
  };

export const playerAction = (action) => (dispatch, getState) => {
  const { engine } = getState().game;
  if (!engine) return;
  const { state, cleared } = step(engine, action);
  if (state !== engine) dispatch(commitEngine(state, { cleared }));
};

export const receivePenalty = (lines) => (dispatch, getState) => {
  const { engine } = getState().game;
  if (!engine) return;
  const next = applyPenalty(engine, lines);
  if (next !== engine) dispatch(commitEngine(next));
};
