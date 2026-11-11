import { useCallback, useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useParams } from 'react-router';
import { createBoard, renderBoard } from '../../shared/board.js';
import { useInterval } from '../hooks/useInterval.js';
import { useKeyboard } from '../hooks/useKeyboard.js';
import { selectGame, selectMe, selectOpponents } from '../store/gameSlice.js';
import { joinRoom, leaveRoom, playerAction, startGame } from '../store/thunks.js';
import Board from './Board.jsx';
import Spectrum from './Spectrum.jsx';

export const TICK_MS = 500;
const EMPTY_BOARD = createBoard();

const statusMessage = (game, me) => {
  if (game.roomStatus === 'finished') {
    if (game.winner === null) return 'Game over';
    return game.winner === game.playerName ? 'You win!' : `${game.winner} wins`;
  }
  if (game.engine?.status === 'lost') return 'You lost';
  if (game.roomStatus === 'waiting') return me?.isHost ? 'Press start when ready' : 'Waiting for the host...';
  return null;
};

const GameRoom = () => {
  const { room, player } = useParams();
  const dispatch = useDispatch();
  const game = useSelector(selectGame);
  const me = useSelector(selectMe);
  const opponents = useSelector(selectOpponents);

  useEffect(() => {
    dispatch(joinRoom(room, player));
    return () => dispatch(leaveRoom());
  }, [dispatch, room, player]);

  const playing = game.roomStatus === 'playing' && game.engine?.status === 'playing';
  const onAction = useCallback((action) => dispatch(playerAction(action)), [dispatch]);
  useInterval(() => onAction('tick'), playing ? TICK_MS : null);
  useKeyboard(onAction, playing);

  const cells = game.engine ? renderBoard(game.engine.board, game.engine.piece) : EMPTY_BOARD;
  const message = statusMessage(game, me);

  return (
    <div className="room">
      <header className="room-header">
        <h1>Red Tetris</h1>
        <span>
          Room <strong>{room}</strong> - {player}
        </span>
      </header>
      {game.error && <div className="error">{game.error}</div>}
      <main className="room-main">
        <section className="player-area">
          <Board cells={cells} />
          {message && <div className="status">{message}</div>}
          {me?.isHost && game.roomStatus !== 'playing' && (
            <button type="button" onClick={() => dispatch(startGame())}>
              {game.roomStatus === 'finished' ? 'Restart' : 'Start'}
            </button>
          )}
        </section>
        <aside className="opponents">
          {opponents.map((p) => (
            <Spectrum key={p.id} player={p} />
          ))}
        </aside>
      </main>
    </div>
  );
};

export default GameRoom;
