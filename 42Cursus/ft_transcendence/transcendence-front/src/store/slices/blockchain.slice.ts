import { createSlice, createAsyncThunk, type PayloadAction } from "@reduxjs/toolkit";
import { createPublicClient, http, formatUnits } from "viem";
import { sepolia } from "viem/chains";
import { walletApi } from "../../lib/api";
import type { WalletResponse } from "../../types";
import { env } from "../../config/env";

// Minimal ERC-20 ABI
const erc20Abi = [
  {
    inputs: [{ name: "account", type: "address" }],
    name: "balanceOf",
    outputs: [{ name: "", type: "uint256" }],
    stateMutability: "view",
    type: "function",
  },
  {
    inputs: [],
    name: "totalSupply",
    outputs: [{ name: "", type: "uint256" }],
    stateMutability: "view",
    type: "function",
  },
] as const;

interface BlockchainState {
  walletAddress: string | null;
  chainId: number | null;
  isConnected: boolean;
  tokenBalance: string;
  totalSupply: string;
  wallets: WalletResponse[];
  loading: boolean;
  error: string | null;
}

const initialState: BlockchainState = {
  walletAddress: null,
  chainId: null,
  isConnected: false,
  tokenBalance: "0",
  totalSupply: "0",
  wallets: [],
  loading: false,
  error: null,
};

// Register connected wallet in the backend
export const connectWalletToBackend = createAsyncThunk(
  "blockchain/connectWalletToBackend",
  async ({ address, chainId }: { address: string; chainId: number }) => {
    return await walletApi.connectWallet({ address, chainId, isPrimary: true });
  }
);

function getPublicClient() {
  return createPublicClient({
    chain: sepolia,
    transport: http(env.RPC_URL),
  });
}

// Fetch ZION token balance from Sepolia via viem
export const fetchTokenBalance = createAsyncThunk(
  "blockchain/fetchTokenBalance",
  async (walletAddress: string) => {
    const contractAddress = env.ZION_TOKEN_ADDRESS;
    if (!contractAddress || contractAddress === "0x") return "0";

    const raw = await getPublicClient().readContract({
      address: contractAddress,
      abi: erc20Abi,
      functionName: "balanceOf",
      args: [walletAddress as `0x${string}`],
    });

    return formatUnits(raw, 18);
  }
);

// Fetch ZION total supply from contract
export const fetchTotalSupply = createAsyncThunk(
  "blockchain/fetchTotalSupply",
  async () => {
    const contractAddress = env.ZION_TOKEN_ADDRESS;
    if (!contractAddress || contractAddress === "0x") return "0";

    const raw = await getPublicClient().readContract({
      address: contractAddress,
      abi: erc20Abi,
      functionName: "totalSupply",
    });

    return formatUnits(raw, 18);
  }
);

// Fetch wallets registered in the backend
export const fetchWallets = createAsyncThunk(
  "blockchain/fetchWallets",
  async () => {
    return await walletApi.getMyWallets();
  }
);

const blockchainSlice = createSlice({
  name: "blockchain",
  initialState,
  reducers: {
    setWalletConnected: (
      state,
      action: PayloadAction<{ address: string; chainId: number }>
    ) => {
      state.walletAddress = action.payload.address;
      state.chainId = action.payload.chainId;
      state.isConnected = true;
    },
    setWalletDisconnected: (state) => {
      state.walletAddress = null;
      state.chainId = null;
      state.isConnected = false;
      state.tokenBalance = "0";
    },
    clearBlockchainError: (state) => {
      state.error = null;
    },
  },
  extraReducers: (builder) => {
    // connectWalletToBackend
    builder.addCase(connectWalletToBackend.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(
      connectWalletToBackend.fulfilled,
      (state, action: PayloadAction<WalletResponse>) => {
        state.loading = false;
        if (!state.wallets.find((w) => w.id === action.payload.id)) {
          state.wallets.push(action.payload);
        }
      }
    );
    builder.addCase(connectWalletToBackend.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Failed to register wallet";
    });

    // fetchTokenBalance
    builder.addCase(fetchTokenBalance.fulfilled, (state, action: PayloadAction<string>) => {
      state.tokenBalance = action.payload;
    });

    // fetchTotalSupply
    builder.addCase(fetchTotalSupply.fulfilled, (state, action: PayloadAction<string>) => {
      state.totalSupply = action.payload;
    });

    // fetchWallets
    builder.addCase(fetchWallets.fulfilled, (state, action: PayloadAction<WalletResponse[]>) => {
      state.wallets = action.payload;
    });
  },
});

export const { setWalletConnected, setWalletDisconnected, clearBlockchainError } =
  blockchainSlice.actions;
export default blockchainSlice.reducer;
