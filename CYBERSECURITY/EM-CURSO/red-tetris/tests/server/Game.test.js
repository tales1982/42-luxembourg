import { describe, expect, it } from 'vitest';
import Game, { GameError } from '../../src/server/Game.js';
import Piece from '../../src/server/Piece.js';
import Player from '../../src/server/Player.js';

const setup = (...names) => {
  const game = new Game('room', () => 0.5);
  names.forEach((name) => game.addPlayer(new Player(`id-${name}`, name)));
  return game;
};

describe('Piece and Player', () => {
  it('serializes a piece at its spawn position', () => {
    expect(new Piece('O').toJSON()).toEqual({ type: 'O', x: 4, y: 0 });
  });

  it('creates a player with an empty spectrum', () => {
    const p = new Player('1', 'bob');
    expect(p.toJSON()).toEqual({ id: '1', name: 'bob', isHost: false, alive: true, spectrum: Array(10).fill(0) });
  });
});

describe('Game', () => {
  it('makes the first player host and rejects duplicate names', () => {
    const game = setup('a', 'b');
    expect(game.players.get('id-a').isHost).toBe(true);
    expect(game.players.get('id-b').isHost).toBe(false);
    expect(() => game.addPlayer(new Player('x', 'a'))).toThrow(GameError);
  });

  it('transfers host when the host leaves', () => {
    const game = setup('a', 'b');
    game.removePlayer('id-a');
    expect(game.players.get('id-b').isHost).toBe(true);
    game.removePlayer('unknown');
    game.removePlayer('id-b');
    expect(game.isEmpty()).toBe(true);
  });

  it('only lets the host start, and blocks joining while playing', () => {
    const game = setup('a', 'b');
    expect(() => game.start('id-b')).toThrow('Only the host');
    game.start('id-a');
    expect(game.status).toBe('playing');
    expect(() => game.start('id-a')).toThrow('already started');
    expect(() => game.addPlayer(new Player('c', 'c'))).toThrow('in progress');
  });

  it('gives every player the same pieces sequence', () => {
    const game = setup('a');
    const first = game.getPieces(0, 10);
    expect(first).toHaveLength(10);
    expect(game.getPieces(3, 2)).toEqual(first.slice(3, 5));
    expect(game.getPieces(0, 7).map((p) => p.type).sort()).toEqual(['I', 'J', 'L', 'O', 'S', 'T', 'Z']);
  });

  it('ends a multiplayer game when one player remains', () => {
    const game = setup('a', 'b', 'c');
    game.start('id-a');
    expect(game.opponentsOf('id-a').map((p) => p.name)).toEqual(['b', 'c']);
    game.playerLost('id-b');
    expect(game.checkEnd()).toBe(false);
    game.playerLost('id-c');
    game.playerLost('unknown');
    expect(game.checkEnd()).toBe(true);
    expect(game.winner).toBe('a');
    expect(game.checkEnd()).toBe(false);
    expect(game.toJSON().status).toBe('finished');
  });

  it('ends a solo game when the player loses', () => {
    const game = setup('a');
    game.start('id-a');
    expect(game.checkEnd()).toBe(false);
    game.playerLost('id-a');
    expect(game.checkEnd()).toBe(true);
    expect(game.winner).toBeNull();
  });
});
