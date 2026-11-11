import { EMPTY } from '../../shared/board.js';

const Board = ({ cells }) => (
  <div className="board" data-testid="board">
    {cells.flatMap((line, r) =>
      line.map((cell, c) => <div key={`${r}-${c}`} className={`cell cell-${cell === EMPTY ? 'empty' : cell}`} />),
    )}
  </div>
);

export default Board;
