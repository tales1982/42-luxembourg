// Pure functions on the playing field. A board is an array of rows,
// each cell is EMPTY, a piece type ('I'...'Z') or PENALTY.
import { SHAPES, getKicks } from './pieces.js';

export const ROWS = 20;
export const COLS = 10;
export const EMPTY = 0;
export const PENALTY = 'P';

export const createBoard = (rows = ROWS, cols = COLS) =>
  Array.from({ length: rows }, () => Array(cols).fill(EMPTY));

// Absolute [row, col] cells occupied by a piece.
export const getCells = ({ type, rotation, x, y }) =>
  SHAPES[type][rotation].flatMap((line, r) => line.flatMap((filled, c) => (filled ? [[y + r, x + c]] : [])));

export const isValid = (board, piece) =>
  getCells(piece).every(
    ([r, c]) => r >= 0 && r < board.length && c >= 0 && c < board[0].length && board[r][c] === EMPTY,
  );

// Returns the moved piece, or null if the move is blocked.
export const movePiece = (board, piece, dx, dy) => {
  const moved = { ...piece, x: piece.x + dx, y: piece.y + dy };
  return isValid(board, moved) ? moved : null;
};

// Clockwise rotation with SRS wall kicks. Returns null if every kick fails.
export const rotatePiece = (board, piece) => {
  const rotation = (piece.rotation + 1) % 4;
  return (
    getKicks(piece.type, piece.rotation)
      .map(([dx, dy]) => ({ ...piece, rotation, x: piece.x + dx, y: piece.y + dy }))
      .find((candidate) => isValid(board, candidate)) ?? null
  );
};

export const dropPosition = (board, piece) => {
  const next = movePiece(board, piece, 0, 1);
  return next ? dropPosition(board, next) : piece;
};

export const mergePiece = (board, piece) => {
  const cells = new Set(getCells(piece).map(([r, c]) => `${r},${c}`));
  return board.map((line, r) => line.map((cell, c) => (cells.has(`${r},${c}`) ? piece.type : cell)));
};

// Penalty lines are indestructible: they are never cleared.
const isClearable = (line) => line.every((cell) => cell !== EMPTY && cell !== PENALTY);

export const clearLines = (board) => {
  const kept = board.filter((line) => !isClearable(line));
  const cleared = board.length - kept.length;
  return { board: [...createBoard(cleared, board[0].length), ...kept], cleared };
};

// Pushes `count` penalty lines from the bottom. `overflow` is true when
// blocks were pushed out of the top of the field.
export const addPenaltyLines = (board, count) => {
  const n = Math.min(count, board.length);
  const overflow = board.slice(0, n).some((line) => line.some((cell) => cell !== EMPTY));
  const penalty = Array.from({ length: n }, () => Array(board[0].length).fill(PENALTY));
  return { board: [...board.slice(n), ...penalty], overflow };
};

// Height of the highest block in each column.
export const getSpectrum = (board) =>
  board[0].map((_, c) => {
    const top = board.findIndex((line) => line[c] !== EMPTY);
    return top === -1 ? 0 : board.length - top;
  });

// Board with the falling piece drawn on it, for display.
export const renderBoard = (board, piece) => (piece ? mergePiece(board, piece) : board);
