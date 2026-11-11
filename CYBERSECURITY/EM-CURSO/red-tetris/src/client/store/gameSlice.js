import { createSlice } from '@reduxjs/toolkit';
import { addPieces, createEngine } from '../../shared/engine.js';

export const initialState = {
  room: null,
  playerName: null,
  roomStatus: null, // 'waiting' | 'playing' | 'finished'
  players: [],
  winner: null,
  error: null,
  engine: null,
  pendingRequest: false,
};

const gameSlice = createSlice({
  name: 'game',
  initialState,
  reducers: {
    joined: (state, { payload }) => ({ ...initialState, room: payload.room, playerName: payload.playerName }),
    left: () => initialState,
    roomStateReceived: (state, { payload }) => ({ ...state, players: payload.players, roomStatus: payload.status }),
    errorReceived: (state, { payload }) => ({ ...state, error: payload }),
    gameStarted: (state, { payload }) => ({
      ...state,
      roomStatus: 'playing',
      winner: null,
      error: null,
      engine: createEngine(payload),
      pendingRequest: false,
    }),
    engineUpdated: (state, { payload }) => ({ ...state, engine: payload }),
    piecesRequested: (state) => ({ ...state, pendingRequest: true }),
    piecesReceived: (state, { payload }) => ({
      ...state,
      pendingRequest: false,
      engine: state.engine && addPieces(state.engine, payload.index, payload.pieces),
    }),
    gameOver: (state, { payload }) => ({ ...state, roomStatus: 'finished', winner: payload.winner }),
  },
});

export const {
  joined,
  left,
  roomStateReceived,
  errorReceived,
  gameStarted,
  engineUpdated,
  piecesRequested,
  piecesReceived,
  gameOver,
} = gameSlice.actions;

export const selectGame = (state) => state.game;
export const selectMe = (state) => state.game.players.find((p) => p.name === state.game.playerName) ?? null;
export const selectOpponents = (state) => state.game.players.filter((p) => p.name !== state.game.playerName);

export default gameSlice.reducer;
