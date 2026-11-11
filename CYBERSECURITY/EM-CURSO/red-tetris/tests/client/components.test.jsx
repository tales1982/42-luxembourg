// @vitest-environment jsdom
import { act, fireEvent, render, screen } from '@testing-library/react';
import { Provider } from 'react-redux';
import { MemoryRouter } from 'react-router';
import { afterEach, describe, expect, it, vi } from 'vitest';
import App from '../../src/client/App.jsx';
import Board from '../../src/client/components/Board.jsx';
import { TICK_MS } from '../../src/client/components/GameRoom.jsx';
import Spectrum from '../../src/client/components/Spectrum.jsx';
import { createAppStore } from '../../src/client/store/index.js';
import { bindSocket } from '../../src/client/store/socketListeners.js';
import { createBoard } from '../../src/shared/board.js';
import { EVENTS } from '../../src/shared/events.js';

const fakeSocket = () => {
  const handlers = {};
  return { emit: vi.fn(), on: (e, fn) => { handlers[e] = fn; }, fire: (e, d) => act(() => handlers[e](d)) };
};
const renderApp = (path) => {
  const socket = fakeSocket();
  const store = createAppStore(socket);
  bindSocket(socket, store);
  const view = render(
    <Provider store={store}>
      <MemoryRouter initialEntries={[path]}>
        <App />
      </MemoryRouter>
    </Provider>,
  );
  return { socket, store, view };
};
const player = (name, extra = {}) => ({ id: name, name, isHost: false, alive: true, spectrum: Array(10).fill(0), ...extra });

afterEach(() => vi.useRealTimers());

describe('components', () => {
  it('renders a board of 200 cells without tables', () => {
    const { container } = render(<Board cells={createBoard()} />);
    expect(container.querySelectorAll('.cell')).toHaveLength(200);
    expect(container.querySelector('table')).toBeNull();
  });

  it('renders a spectrum', () => {
    const { container } = render(<Spectrum player={player('bob', { isHost: true, alive: false, spectrum: [20, 0, 0, 0, 0, 0, 0, 0, 0, 10] })} />);
    expect(screen.getByText('bob (host)')).toBeTruthy();
    expect(container.querySelector('.spectrum-dead')).toBeTruthy();
    expect(container.querySelector('.spectrum-fill').style.height).toBe('100%');
  });

  it('home form navigates to the room', () => {
    const { socket } = renderApp('/');
    fireEvent.change(screen.getByPlaceholderText('Room'), { target: { value: 'r1' } });
    fireEvent.change(screen.getByPlaceholderText('Player name'), { target: { value: 'alice' } });
    fireEvent.click(screen.getByText('Join'));
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.JOIN, { room: 'r1', name: 'alice' });
  });

  it('runs a game in the room page', () => {
    vi.useFakeTimers();
    const { socket, store, view } = renderApp('/r1/alice');
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.JOIN, { room: 'r1', name: 'alice' });

    socket.fire(EVENTS.ROOM_STATE, { status: 'waiting', players: [player('alice', { isHost: true }), player('bob')] });
    expect(screen.getByText('Press start when ready')).toBeTruthy();
    fireEvent.click(screen.getByText('Start'));
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.START);

    socket.fire(EVENTS.GAME_STARTED, { pieces: [{ type: 'T', x: 3, y: 0 }, { type: 'O', x: 4, y: 0 }] });
    socket.fire(EVENTS.ROOM_STATE, { status: 'playing', players: [player('alice', { isHost: true }), player('bob')] });
    fireEvent.keyDown(window, { key: 'ArrowLeft' });
    fireEvent.keyDown(window, { key: 'a' });
    expect(store.getState().game.engine.piece.x).toBe(2);
    act(() => vi.advanceTimersByTime(TICK_MS));
    expect(store.getState().game.engine.piece.y).toBe(1);

    socket.fire(EVENTS.ROOM_ERROR, { message: 'oops' });
    expect(screen.getByText('oops')).toBeTruthy();

    socket.fire(EVENTS.GAME_OVER, { winner: 'alice' });
    expect(screen.getByText('You win!')).toBeTruthy();
    expect(screen.getByText('Restart')).toBeTruthy();

    socket.fire(EVENTS.GAME_OVER, { winner: 'bob' });
    expect(screen.getByText('bob wins')).toBeTruthy();
    socket.fire(EVENTS.GAME_OVER, { winner: null });
    expect(screen.getByText('Game over')).toBeTruthy();

    view.unmount();
    expect(socket.emit).toHaveBeenCalledWith(EVENTS.LEAVE);
  });

  it('shows lost and waiting states', () => {
    const { socket } = renderApp('/r1/bob');
    socket.fire(EVENTS.ROOM_STATE, { status: 'waiting', players: [player('alice', { isHost: true }), player('bob')] });
    expect(screen.getByText('Waiting for the host...')).toBeTruthy();
    socket.fire(EVENTS.GAME_STARTED, { pieces: [{ type: 'T', x: 3, y: 0 }] });
    socket.fire(EVENTS.PENALTY, { lines: 25 });
    expect(screen.getByText('You lost')).toBeTruthy();
  });
});
