import { describe, expect, it } from 'vitest';
import {
  COLS, EMPTY, PENALTY, ROWS, addPenaltyLines, clearLines, createBoard, dropPosition, getCells,
  getSpectrum, isValid, mergePiece, movePiece, renderBoard, rotatePiece,
} from '../../src/shared/board.js';

const T = { type: 'T', rotation: 0, x: 3, y: 0 };
const fullRow = (value = 'Z') => Array(COLS).fill(value);

describe('board', () => {
  it('creates an empty 20x10 board', () => {
    const board = createBoard();
    expect(board).toHaveLength(ROWS);
    expect(board.every((r) => r.length === COLS && r.every((c) => c === EMPTY))).toBe(true);
  });

  it('computes piece cells', () => {
    expect(getCells(T)).toEqual([[0, 4], [1, 3], [1, 4], [1, 5]]);
  });

  it('validates bounds and collisions', () => {
    const board = createBoard();
    expect(isValid(board, T)).toBe(true);
    expect(isValid(board, { ...T, x: -1 })).toBe(false);
    expect(isValid(board, { ...T, x: 8 })).toBe(false);
    expect(isValid(board, { ...T, y: 19 })).toBe(false);
    expect(isValid(board, { ...T, y: -1 })).toBe(false);
    expect(isValid(mergePiece(board, T), T)).toBe(false);
  });

  it('moves pieces or returns null when blocked', () => {
    const board = createBoard();
    expect(movePiece(board, T, 1, 0)).toEqual({ ...T, x: 4 });
    expect(movePiece(board, { ...T, x: 0 }, -1, 0)).toBeNull();
  });

  it('rotates with wall kicks', () => {
    const board = createBoard();
    expect(rotatePiece(board, T)).toEqual({ ...T, rotation: 1 });
    // I piece vertical against the left wall needs a kick to rotate back.
    const iVertical = { type: 'I', rotation: 3, x: -1, y: 5 };
    expect(isValid(board, iVertical)).toBe(true);
    const rotated = rotatePiece(board, iVertical);
    expect(rotated.rotation).toBe(0);
    expect(isValid(board, rotated)).toBe(true);
  });

  it('returns null when rotation is impossible', () => {
    const board = createBoard().map((row, r) => (r === 0 ? row : fullRow()));
    expect(rotatePiece(board, { type: 'I', rotation: 0, x: 3, y: -1 })).toBeNull();
  });

  it('drops a piece to the bottom', () => {
    expect(dropPosition(createBoard(), T).y).toBe(18);
  });

  it('clears full lines but keeps penalty lines', () => {
    const board = [...createBoard(ROWS - 2), fullRow(), fullRow(PENALTY)];
    const result = clearLines(board);
    expect(result.cleared).toBe(1);
    expect(result.board).toHaveLength(ROWS);
    expect(result.board[ROWS - 1]).toEqual(fullRow(PENALTY));
    expect(result.board[ROWS - 2]).toEqual(Array(COLS).fill(EMPTY));
  });

  it('adds penalty lines and detects overflow', () => {
    const { board, overflow } = addPenaltyLines(createBoard(), 2);
    expect(overflow).toBe(false);
    expect(board[ROWS - 1]).toEqual(fullRow(PENALTY));
    expect(board[ROWS - 3]).toEqual(Array(COLS).fill(EMPTY));
    const top = mergePiece(createBoard(), T);
    expect(addPenaltyLines(top, 1).overflow).toBe(true);
    expect(addPenaltyLines(createBoard(), 50).board).toHaveLength(ROWS);
  });

  it('computes the spectrum', () => {
    const board = mergePiece(createBoard(), { ...T, y: 18 });
    expect(getSpectrum(board)).toEqual([0, 0, 0, 1, 2, 1, 0, 0, 0, 0]);
  });

  it('renders the falling piece', () => {
    const board = createBoard();
    expect(renderBoard(board, null)).toBe(board);
    expect(renderBoard(board, T)[0][4]).toBe('T');
  });
});
