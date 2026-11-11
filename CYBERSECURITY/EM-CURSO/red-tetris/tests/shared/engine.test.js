import { describe, expect, it } from 'vitest';
import { COLS, PENALTY, ROWS, createBoard, mergePiece } from '../../src/shared/board.js';
import { addPieces, applyPenalty, createEngine, spawnNext, step } from '../../src/shared/engine.js';

const piece = (type) => ({ type, x: type === 'O' ? 4 : 3, y: type === 'I' ? -1 : 0 });
const pieces = (...types) => types.map(piece);

describe('engine', () => {
  it('spawns the first piece', () => {
    const state = createEngine(pieces('T', 'O'));
    expect(state.piece).toEqual({ type: 'T', x: 3, y: 0, rotation: 0 });
    expect(state.pieceIndex).toBe(1);
    expect(state.status).toBe('playing');
  });

  it('waits when no piece is available, then spawns when pieces arrive', () => {
    const state = createEngine([]);
    expect(state.piece).toBeNull();
    const updated = addPieces(state, 0, pieces('O'));
    expect(updated.piece.type).toBe('O');
    expect(addPieces(updated, 5, pieces('T'))).toBe(updated);
    expect(addPieces(updated, 1, pieces('T')).piece.type).toBe('O');
  });

  it('loses when a new piece cannot enter the field', () => {
    const board = mergePiece(createBoard(), { type: 'T', x: 3, y: 0, rotation: 0 });
    const state = spawnNext({ board, pieces: pieces('T'), pieceIndex: 0, piece: null, status: 'playing' });
    expect(state.status).toBe('lost');
  });

  it('handles moves and rotation', () => {
    const state = createEngine(pieces('T'));
    expect(step(state, 'left').state.piece.x).toBe(2);
    expect(step(state, 'right').state.piece.x).toBe(4);
    expect(step(state, 'down').state.piece.y).toBe(1);
    expect(step(state, 'rotate').state.piece.rotation).toBe(1);
    expect(step(state, 'unknown').state).toBe(state);
    const atWall = { ...state, piece: { ...state.piece, x: 0 } };
    expect(step(atWall, 'left').state).toBe(atWall);
  });

  it('locks only on the tick after touching the pile', () => {
    const start = createEngine(pieces('T', 'O'));
    const resting = { ...start, piece: { ...start.piece, y: 18 } };
    const first = step(resting, 'tick');
    expect(first.locked).toBe(true);
    expect(first.state.board[19][4]).toBe('T');
    expect(first.state.piece.type).toBe('O');

    const falling = step(start, 'tick');
    expect(falling.locked).toBe(false);
    expect(falling.state.piece.y).toBe(1);
  });

  it('hard drops and clears lines', () => {
    const board = createBoard().map((row, r) => (r === ROWS - 1 ? [...Array(COLS - 4).fill('Z'), 0, 0, 0, 0] : row));
    const start = { ...createEngine(pieces('I', 'T')), board };
    const moved = { ...start, piece: { ...start.piece, x: 6 } };
    const { state, locked, cleared } = step(moved, 'drop');
    expect(locked).toBe(true);
    expect(cleared).toBe(1);
    expect(state.board[ROWS - 1].every((c) => c === 0)).toBe(true);
  });

  it('ignores actions when lost or without piece', () => {
    const lost = { ...createEngine(pieces('T')), status: 'lost' };
    expect(step(lost, 'left').state).toBe(lost);
    const empty = createEngine([]);
    expect(step(empty, 'tick').state).toBe(empty);
  });

  it('applies penalty lines', () => {
    const state = createEngine(pieces('T'));
    expect(applyPenalty(state, 0)).toBe(state);
    const after = applyPenalty(state, 2);
    expect(after.board[ROWS - 1]).toEqual(Array(COLS).fill(PENALTY));
    expect(after.piece).toEqual(state.piece);
    expect(applyPenalty({ ...state, status: 'lost' }, 2).status).toBe('lost');
  });

  it('lifts the falling piece when penalty overlaps it', () => {
    const state = createEngine(pieces('T'));
    const low = { ...state, piece: { ...state.piece, y: 18 } };
    const after = applyPenalty(low, 1);
    expect(after.piece.y).toBe(17);
    expect(after.status).toBe('playing');
  });

  it('loses when penalty overflows the field', () => {
    const state = createEngine(pieces('T'));
    const full = { ...state, board: mergePiece(createBoard(), { type: 'O', x: 0, y: 0, rotation: 0 }) };
    expect(applyPenalty(full, 1).status).toBe('lost');
    const noRoom = { ...state, piece: { ...state.piece, y: 0 } };
    expect(applyPenalty(noRoom, ROWS - 1).status).toBe('lost');
  });
});
