import { describe, expect, it } from 'vitest';
import { SHAPES, TYPES, getKicks, rotateMatrix, shuffle, spawnPosition } from '../../src/shared/pieces.js';

describe('pieces', () => {
  it('rotates a matrix clockwise', () => {
    expect(rotateMatrix([[1, 2], [3, 4]])).toEqual([[3, 1], [4, 2]]);
  });

  it('has 4 rotations of 4 cells for every type', () => {
    TYPES.forEach((type) => {
      expect(SHAPES[type]).toHaveLength(4);
      SHAPES[type].forEach((m) => expect(m.flat().filter(Boolean)).toHaveLength(4));
    });
  });

  it('spawns pieces in the middle of the field', () => {
    expect(spawnPosition('O')).toEqual({ x: 4, y: 0 });
    expect(spawnPosition('I')).toEqual({ x: 3, y: -1 });
    expect(spawnPosition('T')).toEqual({ x: 3, y: 0 });
  });

  it('returns SRS kicks', () => {
    expect(getKicks('O', 0)).toEqual([[0, 0]]);
    expect(getKicks('I', 0)).toHaveLength(5);
    expect(getKicks('T', 3)[1]).toEqual([-1, 0]);
  });

  it('shuffles into a permutation without mutating the input', () => {
    const input = [...TYPES];
    const result = shuffle(input, () => 0);
    expect([...result].sort()).toEqual([...TYPES].sort());
    expect(input).toEqual(TYPES);
  });
});
