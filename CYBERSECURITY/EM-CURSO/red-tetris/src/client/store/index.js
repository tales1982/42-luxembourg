import { configureStore } from '@reduxjs/toolkit';
import gameReducer from './gameSlice.js';

export const createAppStore = (socket, preloadedState) =>
  configureStore({
    reducer: { game: gameReducer },
    preloadedState,
    middleware: (getDefaultMiddleware) => getDefaultMiddleware({ thunk: { extraArgument: { socket } } }),
  });
