import http from 'node:http';
import path from 'node:path';
import express from 'express';
import { Server } from 'socket.io';
import { registerSocketHandlers } from './socket.js';

// Serves index.html, bundle.js and assets over HTTP, and the game over socket.io.
export const createServer = ({ staticDir } = {}) => {
  const app = express();
  if (staticDir) {
    app.use(express.static(staticDir));
    // SPA fallback: every /<room>/<player> URL gets index.html.
    app.use((req, res, next) => {
      if (req.method !== 'GET') return next();
      res.sendFile(path.join(staticDir, 'index.html'), (err) => {
        if (err) res.status(404).send('Client not built. Run "npm run build".');
      });
    });
  }
  const httpServer = http.createServer(app);
  const io = new Server(httpServer);
  const games = registerSocketHandlers(io);
  return { app, httpServer, io, games };
};
