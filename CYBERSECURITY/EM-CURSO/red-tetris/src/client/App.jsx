import { Route, Routes } from 'react-router';
import GameRoom from './components/GameRoom.jsx';
import Home from './components/Home.jsx';

const App = () => (
  <Routes>
    <Route path="/:room/:player" element={<GameRoom />} />
    <Route path="*" element={<Home />} />
  </Routes>
);

export default App;
