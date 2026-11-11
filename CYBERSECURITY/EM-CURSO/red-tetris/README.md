# Red Tetris

Networked multiplayer Tetris — Full Stack JavaScript (Node.js + socket.io + React + Redux).

## Como rodar

```bash
cd red-tetris
npm install          # só na primeira vez
npm run build        # gera dist/index.html e dist/bundle.js
npm start            # sobe o servidor na porta 3000
```

Depois abra no navegador `http://localhost:3000/<sala>/<seu_nome>`, por exemplo `http://localhost:3000/sala1/tales`.

**Para jogar multiplayer:** abra outra aba com a mesma sala e outro nome, como `http://localhost:3000/sala1/bob`. Quem entrou primeiro é o host e aparece o botão **Start** para ele.

**Teclas:** ← → movem, ↑ gira, ↓ desce mais rápido, Espaço derruba a peça.

**Para desenvolver**, com recarga automática quando você edita o código:

```bash
npm run dev
```

Nesse modo abra `http://localhost:5173/sala1/tales` (porta 5173, não 3000).

**Outros comandos:**

```bash
npm test            # roda os testes
npm run coverage    # testes + cobertura
npm run lint        # verifica o código
```

## Structure

```
src/
  shared/    pure functions (no `this`), used by client and server
    pieces.js   tetrimino shapes, SRS rotations and wall kicks, shuffle
    board.js    board: collision, move, rotate, merge, clear lines, penalty, spectrum
    engine.js   one player's game state machine (tick, move, lock, penalty)
    events.js   socket.io event names (protocol)
  server/    object-oriented (classes / prototypes)
    Player.js, Piece.js, Game.js   domain model
    socket.js                       socket.io handlers
    app.js, index.js                Express HTTP + socket.io
  client/    React SPA + Redux Toolkit (no `this`)
    store/       slice, thunks (side effects -> socket), socket listeners
    hooks/       useInterval (gravity), useKeyboard
    components/  Home, GameRoom, Board (CSS grid), Spectrum (flexbox)
tests/       Vitest
```

## Who does what

- **Client**: runs its own game locally (gravity, moves, rotation, locking,
  clearing lines) using the pure functions in `src/shared`. Tells the server
  about relevant events.
- **Server**: manages rooms, players and host, generates the **shared** piece
  sequence for each room (7-piece bags), relays penalties and spectrums, and
  detects the end of the round.

## Network protocol (socket.io)

| Direction | Event | Payload | Effect |
|---|---|---|---|
| C → S | `room:join` | `{ room, name }` | Joins/creates the room. The first player becomes host. |
| C → S | `room:leave` | — | Leaves the room (same as disconnecting). |
| C → S | `game:start` | — | Host only: starts/restarts the round. |
| C → S | `pieces:request` | `{ index }` | Asks for the next pieces starting at `index`. |
| C → S | `player:spectrum` | `{ spectrum: number[10] }` | Height of each column after a change. |
| C → S | `player:lines` | `{ count }` | Lines cleared at once (2–4 → opponents get `count - 1`). |
| C → S | `player:lost` | — | The player can no longer play. |
| S → C | `room:state` | `{ name, status, winner, players[] }` | Room state (players, host, alive, spectrum). |
| S → C | `room:error` | `{ message }` | Error (invalid name, game in progress, not host...). |
| S → C | `game:started` | `{ pieces[] }` | The first 14 pieces `{ type, x, y }`, the same for everyone. |
| S → C | `pieces` | `{ index, pieces[] }` | Reply to `pieces:request` (7 pieces). |
| S → C | `penalty` | `{ lines }` | Add indestructible lines to the bottom. |
| S → C | `game:over` | `{ winner }` | End of the round (`null` in solo). |

## Controls

← → move · ↑ rotate · ↓ soft drop · Space hard drop
