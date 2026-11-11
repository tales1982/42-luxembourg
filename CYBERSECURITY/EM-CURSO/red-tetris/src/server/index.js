import { fileURLToPath } from 'node:url';
import { createServer } from './app.js';

const PORT = Number(process.env.PORT) || 3000;
const HOST = process.env.HOST || '0.0.0.0';
const staticDir = fileURLToPath(new URL('../../dist', import.meta.url));

const { httpServer } = createServer({ staticDir });
httpServer.listen(PORT, HOST, () => {
  console.log(`Red Tetris listening on http://localhost:${PORT}`);
});
