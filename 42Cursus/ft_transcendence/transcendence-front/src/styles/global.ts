import { createGlobalStyle } from "styled-components";

export const GlobalStyle = createGlobalStyle`
  * { box-sizing: border-box; margin: 0; padding: 0; }
  html, body, #root { height: 100%; }
  body {
    font-family: 'Inter', ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Arial, sans-serif;
    background: ${({ theme }) => theme.colors.bg};
    color: ${({ theme }) => theme.colors.text};
    -webkit-font-smoothing: antialiased;
    cursor: none;
  }
  a { color: inherit; text-decoration: none; }
  button, input, select, textarea { font: inherit; }
  h1, h2, h3, h4, h5, h6 { margin: 0; }
  ul, ol { list-style: none; padding: 0; margin: 0; }

  .custom-cursor {
    width: 14px;
    height: 14px;
    border: 2px solid ${({ theme }) => theme.colors.primary};
    border-radius: 50%;
    position: fixed;
    left: 0;
    top: 0;
    transform: translate3d(-50%, -50%, 0);
    pointer-events: none;
    z-index: 9999;
    transition: transform 0.08s ease-out, border-color 0.2s ease;
    mix-blend-mode: screen;
  }

  .custom-cursor-trail {
    width: 6px;
    height: 6px;
    background: ${({ theme }) => theme.colors.primary};
    border-radius: 50%;
    position: fixed;
    left: 0;
    top: 0;
    transform: translate3d(-50%, -50%, 0);
    pointer-events: none;
    z-index: 9998;
    opacity: 0.5;
    transition: transform 0.12s ease-out;
    mix-blend-mode: screen;
  }

  @media (hover: none) and (pointer: coarse) {
    body { cursor: auto; }
    .custom-cursor, .custom-cursor-trail { display: none; }
  }
`;
