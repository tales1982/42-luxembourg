import { spawnPosition } from '../shared/pieces.js';

export default class Piece {
  constructor(type) {
    const { x, y } = spawnPosition(type);
    this.type = type;
    this.x = x;
    this.y = y;
  }

  toJSON() {
    return { type: this.type, x: this.x, y: this.y };
  }
}
