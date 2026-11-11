// Player-side game state machine, built only from pure functions.
// state = { board, pieces, pieceIndex, piece, status: 'playing' | 'lost' }
import { addPenaltyLines, clearLines, createBoard, dropPosition, isValid, mergePiece, movePiece, rotatePiece } from './board.js';

export const spawnNext = (state) => {
  const next = state.pieces[state.pieceIndex];
  if (!next) return { ...state, piece: null }; // waiting for the server to send more pieces
  const piece = { type: next.type, x: next.x, y: next.y, rotation: 0 };
  return isValid(state.board, piece)
    ? { ...state, piece, pieceIndex: state.pieceIndex + 1 }
    : { ...state, piece: null, status: 'lost' };
};

export const createEngine = (pieces = []) =>
  spawnNext({ board: createBoard(), pieces, pieceIndex: 0, piece: null, status: 'playing' });

// Appends pieces received from the server (ignored if `index` does not follow the queue).
export const addPieces = (state, index, pieces) => {
  if (index !== state.pieces.length) return state;
  const updated = { ...state, pieces: [...state.pieces, ...pieces] };
  return updated.piece || updated.status !== 'playing' ? updated : spawnNext(updated);
};

const unchanged = (state) => ({ state, locked: false, cleared: 0 });

const lock = (state, piece) => {
  const { board, cleared } = clearLines(mergePiece(state.board, piece));
  return { state: spawnNext({ ...state, board, piece: null }), locked: true, cleared };
};

const withPiece = (state, piece) => unchanged(piece ? { ...state, piece } : state);

// action: 'left' | 'right' | 'rotate' | 'down' | 'drop' | 'tick'
// Returns { state, locked, cleared }.
export const step = (state, action) => {
  if (state.status !== 'playing' || !state.piece) return unchanged(state);
  const { board, piece } = state;
  switch (action) {
    case 'left':
      return withPiece(state, movePiece(board, piece, -1, 0));
    case 'right':
      return withPiece(state, movePiece(board, piece, 1, 0));
    case 'rotate':
      return withPiece(state, rotatePiece(board, piece));
    case 'down':
      return withPiece(state, movePiece(board, piece, 0, 1));
    case 'drop':
      return lock(state, dropPosition(board, piece));
    case 'tick': {
      // A piece resting on the pile only locks on the following tick,
      // so the player can still slide it during that frame.
      const moved = movePiece(board, piece, 0, 1);
      return moved ? unchanged({ ...state, piece: moved }) : lock(state, piece);
    }
    default:
      return unchanged(state);
  }
};

const liftPiece = (board, piece, max) =>
  Array.from({ length: max }, (_, i) => ({ ...piece, y: piece.y - i - 1 })).find((p) => isValid(board, p)) ?? null;

export const applyPenalty = (state, lines) => {
  if (state.status !== 'playing' || lines <= 0) return state;
  const { board, overflow } = addPenaltyLines(state.board, lines);
  const lost = { ...state, board, piece: null, status: 'lost' };
  if (overflow) return lost;
  if (!state.piece || isValid(board, state.piece)) return { ...state, board };
  const lifted = liftPiece(board, state.piece, lines);
  return lifted ? { ...state, board, piece: lifted } : lost;
};
