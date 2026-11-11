import { TYPES, shuffle } from '../shared/pieces.js';
import Piece from './Piece.js';

export class GameError extends Error {
  constructor(message) {
    super(message);
    this.name = 'GameError';
  }
}

export default class Game {
  constructor(name, random = Math.random) {
    this.name = name;
    this.random = random;
    this.players = new Map();
    this.status = 'waiting'; // 'waiting' | 'playing' | 'finished'
    this.pieces = [];
    this.winner = null;
    this.solo = false;
  }

  addPlayer(player) {
    if (this.status === 'playing') throw new GameError('Game already in progress, wait for the next round');
    if (this.getPlayers().some((p) => p.name === player.name)) throw new GameError('Name already taken in this room');
    player.isHost = this.players.size === 0;
    this.players.set(player.id, player);
  }

  removePlayer(id) {
    const player = this.players.get(id);
    if (!player) return;
    this.players.delete(id);
    if (player.isHost && this.players.size > 0) this.getPlayers()[0].isHost = true;
  }

  getPlayers() {
    return [...this.players.values()];
  }

  isEmpty() {
    return this.players.size === 0;
  }

  start(playerId) {
    if (!this.players.get(playerId)?.isHost) throw new GameError('Only the host can start the game');
    if (this.status === 'playing') throw new GameError('Game already started');
    this.players.forEach((p) => p.reset());
    this.pieces = [];
    this.winner = null;
    this.solo = this.players.size === 1;
    this.status = 'playing';
  }

  // Same sequence for every player of the room, generated in 7-piece bags.
  getPieces(index, count) {
    while (this.pieces.length < index + count) {
      this.pieces.push(...shuffle(TYPES, this.random).map((type) => new Piece(type)));
    }
    return this.pieces.slice(index, index + count);
  }

  alivePlayers() {
    return this.getPlayers().filter((p) => p.alive);
  }

  opponentsOf(id) {
    return this.alivePlayers().filter((p) => p.id !== id);
  }

  playerLost(id) {
    const player = this.players.get(id);
    if (player) player.alive = false;
  }

  // Ends the round when it is over. Returns true if it just ended.
  checkEnd() {
    if (this.status !== 'playing') return false;
    const alive = this.alivePlayers();
    if (this.solo ? alive.length > 0 : alive.length > 1) return false;
    this.status = 'finished';
    this.winner = this.solo ? null : (alive[0]?.name ?? null);
    return true;
  }

  toJSON() {
    return { name: this.name, status: this.status, winner: this.winner, players: this.getPlayers().map((p) => p.toJSON()) };
  }
}
