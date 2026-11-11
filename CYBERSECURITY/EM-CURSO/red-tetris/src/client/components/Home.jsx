import { useState } from 'react';
import { useNavigate } from 'react-router';

const Home = () => {
  const navigate = useNavigate();
  const [room, setRoom] = useState('');
  const [name, setName] = useState('');
  const onSubmit = (event) => {
    event.preventDefault();
    if (room && name) navigate(`/${encodeURIComponent(room)}/${encodeURIComponent(name)}`);
  };
  return (
    <form className="home" onSubmit={onSubmit}>
      <h1>Red Tetris</h1>
      <input placeholder="Room" value={room} onChange={(e) => setRoom(e.target.value)} />
      <input placeholder="Player name" value={name} onChange={(e) => setName(e.target.value)} />
      <button type="submit">Join</button>
    </form>
  );
};

export default Home;
