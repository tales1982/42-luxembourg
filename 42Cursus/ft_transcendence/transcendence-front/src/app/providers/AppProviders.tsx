import type { PropsWithChildren } from "react";
import { ThemeProvider } from "styled-components";
import { WagmiProvider } from "wagmi";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { GlobalStyle } from "../../styles/global";
import { theme } from "../../styles/theme";
import { wagmiConfig } from "../../lib/wagmi/config";
import { CustomCursor } from "../../components/ui/CustomCursor";

const queryClient = new QueryClient();

export function AppProviders({ children }: PropsWithChildren) {
  return (
    <WagmiProvider config={wagmiConfig}>
      <QueryClientProvider client={queryClient}>
        <ThemeProvider theme={theme}>
          <GlobalStyle />
          <CustomCursor />
          {children}
        </ThemeProvider>
      </QueryClientProvider>
    </WagmiProvider>
  );
}
