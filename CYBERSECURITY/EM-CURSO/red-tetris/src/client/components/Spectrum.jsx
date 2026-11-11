import { ROWS } from '../../shared/board.js';

const Spectrum = ({ player }) => (
  <div className={`spectrum ${player.alive ? '' : 'spectrum-dead'}`}>
    <div className="spectrum-name">
      {player.name}
      {player.isHost ? ' (host)' : ''}
    </div>
    <div className="spectrum-columns">
      {player.spectrum.map((height, c) => (
        <div key={c} className="spectrum-column">
          <div className="spectrum-fill" style={{ height: `${(height / ROWS) * 100}%` }} />
        </div>
      ))}
    </div>
  </div>
);

export default Spectrum;
