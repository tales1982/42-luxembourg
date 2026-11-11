import { useEffect, useRef } from 'react';

// Calls `callback` every `delay` ms. Pass `null` to pause.
export const useInterval = (callback, delay) => {
  const saved = useRef(callback);
  useEffect(() => {
    saved.current = callback;
  }, [callback]);
  useEffect(() => {
    if (delay === null) return undefined;
    const id = setInterval(() => saved.current(), delay);
    return () => clearInterval(id);
  }, [delay]);
};
