// Network protocol: every socket.io event name used by client and server.
export const EVENTS = Object.freeze({
  // client -> server
  JOIN: 'room:join', // { room, name }
  LEAVE: 'room:leave', // -
  START: 'game:start', // - (host only)
  PIECES_REQUEST: 'pieces:request', // { index }
  SPECTRUM: 'player:spectrum', // { spectrum: number[10] }
  LINES: 'player:lines', // { count } lines cleared at once
  LOST: 'player:lost', // -

  // server -> client
  ROOM_STATE: 'room:state', // { name, status, winner, players: [{ id, name, isHost, alive, spectrum }] }
  ROOM_ERROR: 'room:error', // { message }
  GAME_STARTED: 'game:started', // { pieces: [{ type, x, y }] }
  PIECES: 'pieces', // { index, pieces }
  PENALTY: 'penalty', // { lines }
  GAME_OVER: 'game:over', // { winner: string | null }
});
