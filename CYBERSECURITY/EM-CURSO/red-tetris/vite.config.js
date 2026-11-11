import react from '@vitejs/plugin-react';
import { defineConfig } from 'vite';

export default defineConfig({
  plugins: [react()],
  build: {
    outDir: 'dist',
    rollupOptions: {
      output: { entryFileNames: 'bundle.js', assetFileNames: 'assets/[name][extname]' },
    },
  },
  server: {
    proxy: { '/socket.io': { target: 'http://localhost:3000', ws: true } },
  },
  test: {
    globals: true,
    environment: 'node',
    coverage: {
      provider: 'v8',
      include: ['src/**'],
      exclude: ['src/client/main.jsx', 'src/server/index.js'],
      reporter: ['text', 'html'],
      thresholds: { statements: 70, functions: 70, lines: 70, branches: 50 },
    },
  },
});
