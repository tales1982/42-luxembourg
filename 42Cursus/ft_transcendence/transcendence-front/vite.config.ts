import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { TanStackRouterVite } from '@tanstack/router-plugin/vite'

const styledComponentsHMR = {
  name: 'styled-components-hmr',
  handleHotUpdate({ file, server }: { file: string; server: { ws: { send: (msg: object) => void } } }) {
    if (file.endsWith('.styled.ts')) {
      server.ws.send({ type: 'full-reload' });
      return [];
    }
  },
};

// https://vite.dev/config/
export default defineConfig({
  define: {
    global: 'globalThis',
  },
  plugins: [
    TanStackRouterVite({
      routesDirectory: './src/app/routes',
      generatedRouteTree: './src/routeTree.gen.ts',
      routeFileIgnorePattern: String.raw`\.styled\.ts$`,
    }),
    react({
      babel: {
        plugins: [['babel-plugin-styled-components', { displayName: true }]],
      },
    }),
    styledComponentsHMR,
  ],
  server: {
    host: '0.0.0.0',
    port: 3000,
    watch: {
      usePolling: true,
      interval: 1000,
    },
    hmr: {
      host: 'localhost',
      port: 3000,
    },
  },
})
