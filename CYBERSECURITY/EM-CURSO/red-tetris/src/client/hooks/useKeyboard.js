import { useEffect } from 'react';

export const KEY_ACTIONS = {
  ArrowLeft: 'left',
  ArrowRight: 'right',
  ArrowUp: 'rotate',
  ArrowDown: 'down',
  ' ': 'drop',
};

export const useKeyboard = (onAction, active) => {
  useEffect(() => {
    if (!active) return undefined;
    const onKeyDown = (event) => {
      const action = KEY_ACTIONS[event.key];
      if (!action) return;
      event.preventDefault();
      onAction(action);
    };
    window.addEventListener('keydown', onKeyDown);
    return () => window.removeEventListener('keydown', onKeyDown);
  }, [onAction, active]);
};
