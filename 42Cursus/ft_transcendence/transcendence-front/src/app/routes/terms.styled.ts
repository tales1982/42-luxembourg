import styled from "styled-components";
import { theme } from "../../styles/theme";

export const TosPage = styled.main`
  max-width: 760px;
  margin: 0 auto;
  padding: 100px 32px 80px;

  h2 {
    color: ${theme.colors.text};
    font-size: 0.82rem;
    text-transform: uppercase;
    letter-spacing: 0.09em;
    margin-top: 32px;
    margin-bottom: 10px;
    padding-bottom: 8px;
    border-bottom: 1px solid rgba(255, 255, 255, 0.07);
  }

  p {
    color: ${theme.colors.textSecondary};
    font-size: 0.9rem;
    line-height: 1.75;
    margin-bottom: 6px;
  }

  ul {
    padding-left: 1.5rem;
    margin: 4px 0 12px;
  }

  li {
    color: ${theme.colors.textSecondary};
    font-size: 0.9rem;
    line-height: 1.75;
    margin-bottom: 2px;
  }

  strong {
    color: ${theme.colors.text};
  }
`;

export const TosHeader = styled.div`
  text-align: center;
  padding-bottom: 28px;
  margin-bottom: 4px;
  border-bottom: 1px solid ${theme.colors.primary}33;

  h1 {
    font-size: 1.75rem;
    color: ${theme.colors.primary};
    margin-bottom: 0;
  }
`;

export const BackLink = styled.div`
  margin-bottom: 20px;

  a {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    font-size: 0.83rem;
    color: ${theme.colors.primary};
    text-decoration: none;
    font-weight: 500;
    transition: color 0.2s;

    &:hover {
      color: ${theme.colors.primaryHover};
    }
  }
`;
