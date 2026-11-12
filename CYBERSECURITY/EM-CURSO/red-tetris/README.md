# Red Tetris

Networked multiplayer Tetris — Full Stack JavaScript (Node.js + socket.io + React + Redux).

## Como executar

Na 42 o projeto roda **somente via Docker**. Você precisa apenas do Docker com
o Docker Compose (`docker compose version`) e do `make`. Não precisa instalar Node.

### 1. Subir o jogo

```bash
cd red-tetris
make
```

Na primeira vez ele cria a imagem, o que leva cerca de 1 minuto. Depois o
servidor fica rodando em segundo plano na porta **3000**.

### 2. Jogar

Abra no navegador `http://localhost:3000/<sala>/<seu_nome>`, por exemplo:

```
http://localhost:3000/sala1/tales
```

**Multiplayer:** abra outra aba (ou outro computador) com a **mesma sala** e
**outro nome**, por exemplo `http://localhost:3000/sala1/bob`. Quem entra
primeiro é o host, e só ele vê o botão **Start**.

Para jogar de outro computador na mesma rede, troque `localhost` pelo IP da
máquina que roda o Docker.

**Teclas:** ← → movem · ↑ gira · ↓ desce mais rápido · Espaço derruba a peça.

### 3. Parar

```bash
make down
```

### Todos os comandos

| Comando     | O que faz |
|-------------|-----------|
| `make`      | Cria a imagem e sobe o jogo em `http://localhost:3000` (em segundo plano) |
| `make logs` | Mostra os logs do servidor (Ctrl+C para sair) |
| `make down` | Para e remove os containers |
| `make test` | Roda lint, testes e cobertura dentro de um container |
| `make dev`  | Modo desenvolvimento com recarga automática em `http://localhost:5173` |
| `make clean`| Para tudo e apaga as imagens do projeto |
| `make re`   | `clean` e depois `make`: reconstrói do zero |

**Mudar a porta:** `PORT=8080 make` e abra `http://localhost:8080/sala1/tales`.

**Sem `make`:**

```bash
docker compose up --build -d app                     # subir o jogo
docker compose down                                  # parar
docker compose --profile test run --rm --build test  # testes
docker compose --profile dev up --build dev          # modo desenvolvimento
```

### Modo desenvolvimento (`make dev`)

O código da pasta é montado dentro do container. Quando você salva um arquivo,
o navegador (client) e o servidor recarregam sozinhos. Nesse modo use a porta
**5173**: `http://localhost:5173/sala1/tales`. Para sair, use Ctrl+C.

### Como funciona o Docker aqui

- `Dockerfile` com etapas: `deps` instala as dependências, `build` gera
  `dist/` (index.html + bundle.js) com Vite, e `prod` é a imagem final, só com
  o servidor, `src/shared`, `dist/` e as dependências de produção, rodando
  como usuário não root.
- `docker-compose.yml` tem três serviços: `app` (padrão), `dev` e `test`. Os
  dois últimos só sobem quando são pedidos (profiles).
- `.dockerignore` deixa de fora da imagem `node_modules`, `.git`, `.env` e o PDF.

### Problemas comuns

- **`port is already allocated`**: a porta 3000 já está em uso. Rode
  `make down` ou use `PORT=8080 make`.
- **Alterei o código e o `make` não mostra a mudança**: rode `make re`.
- **`permission denied` no Docker**: seu usuário precisa estar no grupo
  `docker`, ou use o Docker rootless da 42.

### Sem Docker (fora da 42, opcional)

Precisa de Node 20.19+ (recomendado 24).

```bash
npm install && npm run build && npm start   # http://localhost:3000
npm run dev                                 # http://localhost:5173
npm test · npm run coverage · npm run lint
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
