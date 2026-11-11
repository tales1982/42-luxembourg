import { COLS } from '../shared/board.js';

export default class Player {
  constructor(id, name) {
    this.id = id;
    this.name = name;
    this.isHost = false;
    this.reset();
  }

  reset() {
    this.alive = true;
    this.spectrum = Array(COLS).fill(0);
  }

  toJSON() {
    return { id: this.id, name: this.name, isHost: this.isHost, alive: this.alive, spectrum: this.spectrum };
  }
}
