import { useEffect } from "react";
import { useConnection, useConnect, useDisconnect } from "wagmi";
import { injected } from "wagmi/connectors";
import { useAppDispatch, useAppSelector } from "../../../store/hooks";
import {
  setWalletConnected,
  setWalletDisconnected,
  connectWalletToBackend,
  fetchTokenBalance,
} from "../../../store/slices/blockchain.slice";
import {
  ConnectButton,
  WalletInfo,
  WalletAddress,
  TokenBalance,
  DisconnectButton,
} from "./WalletConnect.styled";

function truncateAddress(address: string): string {
  return `${address.slice(0, 6)}…${address.slice(-4)}`;
}

export function WalletConnect() {
  const dispatch = useAppDispatch();
  const { address, chainId, isConnected } = useConnection();
  const { mutate: connect } = useConnect();
  const { mutate: disconnect } = useDisconnect();

  const tokenBalance = useAppSelector((s) => s.blockchain.tokenBalance);
  const loading = useAppSelector((s) => s.blockchain.loading);

  // Sync wagmi state into Redux and register wallet in backend
  useEffect(() => {
    if (isConnected && address && chainId) {
      dispatch(setWalletConnected({ address, chainId }));
      dispatch(connectWalletToBackend({ address, chainId }));
      dispatch(fetchTokenBalance(address));
    } else {
      dispatch(setWalletDisconnected());
    }
  }, [isConnected, address, chainId, dispatch]);

  if (isConnected && address) {
    return (
      <WalletInfo>
        <WalletAddress title={address}>{truncateAddress(address)}</WalletAddress>
        <TokenBalance>{parseFloat(tokenBalance).toFixed(2)} ZION</TokenBalance>
        <DisconnectButton onClick={() => disconnect()}>
          &#10005;
        </DisconnectButton>
      </WalletInfo>
    );
  }

  return (
    <ConnectButton
      onClick={() => connect({ connector: injected() })}
      disabled={loading}
    >
      {loading ? "Conectando…" : "🦊 Conectar Carteira"}
    </ConnectButton>
  );
}
