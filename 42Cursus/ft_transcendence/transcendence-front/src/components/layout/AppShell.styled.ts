import styled from "styled-components";


export const Layout = styled.div`
  min-height: 100vh;
`;

export const MainArea = styled.main`
  margin-left: 256px;
  min-height: 100vh;
  display: flex;
  flex-direction: column;

  @media (max-width: 768px) {
    margin-left: 0;
  }
`;

export const Content = styled.div`
  padding: ${({ theme }) => theme.space(3)};
  flex: 1;

  @media (max-width: 768px) {
    padding: ${({ theme }) => theme.space(2)};
  }
`;

export const Overlay = styled.div<{ $visible: boolean }>`
  display: ${({ $visible }) => ($visible ? "block" : "none")};
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.5);
  z-index: 30;

  @media (min-width: 769px) {
    display: none;
  }
`;

export const Shell = styled.div`
  min-height: 100%;
  display: grid;
  grid-template-rows: auto 1fr;
`;

export const Main = styled.main`
  padding: ${({ theme }) => theme.space(3)};
  max-width: 1100px;
  width: 100%;
  margin: 0 auto;
`;