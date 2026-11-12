# ---------- base: dependências ----------
FROM node:24-alpine AS deps
WORKDIR /app
COPY package.json package-lock.json ./
RUN npm ci

# ---------- dev: hot reload (código montado como volume) ----------
FROM deps AS dev
COPY . .
EXPOSE 3000 5173
CMD ["npx", "concurrently", "-n", "server,client", "-c", "red,blue", "npm:dev:server", "vite --host 0.0.0.0"]

# ---------- build: gera dist/ ----------
FROM deps AS build
COPY . .
RUN npm run build

# ---------- prod: só o necessário para rodar ----------
FROM node:24-alpine AS prod
ENV NODE_ENV=production PORT=3000 HOST=0.0.0.0
WORKDIR /app
COPY package.json package-lock.json ./
RUN npm ci --omit=dev && npm cache clean --force
COPY src/server ./src/server
COPY src/shared ./src/shared
COPY --from=build /app/dist ./dist
USER node
EXPOSE 3000
CMD ["node", "src/server/index.js"]
