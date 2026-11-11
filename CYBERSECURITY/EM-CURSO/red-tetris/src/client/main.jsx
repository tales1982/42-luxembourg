import { createRoot } from 'react-dom/client';
import { Provider } from 'react-redux';
import { BrowserRouter } from 'react-router';
import { io } from 'socket.io-client';
import App from './App.jsx';
import { createAppStore } from './store/index.js';
import { bindSocket } from './store/socketListeners.js';
import './styles.css';

const socket = io();
const store = createAppStore(socket);
bindSocket(socket, store);

createRoot(document.getElementById('root')).render(
  <Provider store={store}>
    <BrowserRouter>
      <App />
    </BrowserRouter>
  </Provider>,
);
