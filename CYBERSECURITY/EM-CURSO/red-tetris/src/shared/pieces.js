// Tetrimino shapes and SRS (Super Rotation System) rules, as pure data + functions.
export const TYPES = ['I', 'J', 'L', 'O', 'S', 'T', 'Z'];

const BASE_SHAPES = {
  I: [
    [0, 0, 0, 0],
    [1, 1, 1, 1],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
  ],
  J: [
    [1, 0, 0],
    [1, 1, 1],
    [0, 0, 0],
  ],
  L: [
    [0, 0, 1],
    [1, 1, 1],
    [0, 0, 0],
  ],
  O: [
    [1, 1],
    [1, 1],
  ],
  S: [
    [0, 1, 1],
    [1, 1, 0],
    [0, 0, 0],
  ],
  T: [
    [0, 1, 0],
    [1, 1, 1],
    [0, 0, 0],
  ],
  Z: [
    [1, 1, 0],
    [0, 1, 1],
    [0, 0, 0],
  ],
};

// Clockwise rotation of a square matrix.
export const rotateMatrix = (matrix) => matrix[0].map((_, c) => matrix.map((row) => row[c]).reverse());

const allRotations = (matrix) =>
  [1, 2, 3].reduce((acc) => [...acc, rotateMatrix(acc[acc.length - 1])], [matrix]);

// SHAPES[type][rotation] -> matrix (rotation 0..3 = spawn, R, 2, L)
export const SHAPES = Object.fromEntries(TYPES.map((type) => [type, allRotations(BASE_SHAPES[type])]));

export const spawnPosition = (type) => ({ x: type === 'O' ? 4 : 3, y: type === 'I' ? -1 : 0 });

// SRS wall kicks for clockwise rotation, as [dx, dy] with dy pointing down.
const JLSTZ_KICKS = [
  [[0, 0], [-1, 0], [-1, -1], [0, 2], [-1, 2]], // 0 -> R
  [[0, 0], [1, 0], [1, 1], [0, -2], [1, -2]], // R -> 2
  [[0, 0], [1, 0], [1, -1], [0, 2], [1, 2]], // 2 -> L
  [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // L -> 0
];
const I_KICKS = [
  [[0, 0], [-2, 0], [1, 0], [-2, 1], [1, -2]],
  [[0, 0], [-1, 0], [2, 0], [-1, -2], [2, 1]],
  [[0, 0], [2, 0], [-1, 0], [2, -1], [-1, 2]],
  [[0, 0], [1, 0], [-2, 0], [1, 2], [-2, -1]],
];

export const getKicks = (type, fromRotation) => {
  if (type === 'O') return [[0, 0]];
  return (type === 'I' ? I_KICKS : JLSTZ_KICKS)[fromRotation];
};

// Fisher-Yates shuffle returning a new array. `random` is injectable for tests.
export const shuffle = (list, random = Math.random) =>
  list.reduceRight((acc, _, i) => {
    const j = Math.floor(random() * (i + 1));
    const copy = [...acc];
    [copy[i], copy[j]] = [copy[j], copy[i]];
    return copy;
  }, [...list]);
