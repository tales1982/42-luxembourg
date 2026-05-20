import { createSlice, createAsyncThunk, type PayloadAction } from "@reduxjs/toolkit";
import { chatApi } from "../../lib/api";
import type { ChatState } from "../../interfaces/ChatState.interface";
import type { ConversationResponse, MessageResponse, Page } from "../../types";



const initialState: ChatState = {
  conversations: [],
  activeConversation: null,
  messages: [],
  unreadByConversation: {},
  unreadTotal: 0,
  loading: false,
  error: null,
};

// Async thunks
export const fetchConversations = createAsyncThunk(
  "chat/fetchConversations",
  async () => {
    return await chatApi.getMyConversations();
  }
);

export const fetchMessages = createAsyncThunk(
  "chat/fetchMessages",
  async ({ conversationId, page = 0 }: { conversationId: number; page?: number }) => {
    return await chatApi.getMessages(conversationId, page, 50);
  }
);

export const sendMessage = createAsyncThunk(
  "chat/sendMessage",
  async ({ conversationId, content }: { conversationId: number; content: string }) => {
    return await chatApi.sendMessage(conversationId, { content });
  }
);

export const getOrCreateTaskConversation = createAsyncThunk(
  "chat/getOrCreateTaskConversation",
  async (taskId: number) => {
    return await chatApi.getOrCreateTaskConversation(taskId);
  }
);

export const getOrCreateDirectConversation = createAsyncThunk(
  "chat/getOrCreateDirectConversation",
  async (userId: number) => {
    return await chatApi.getOrCreateDirectConversation(userId);
  }
);

export const markConversationRead = createAsyncThunk(
  "chat/markConversationRead",
  async (conversationId: number) => {
    await chatApi.markAsRead(conversationId);
    return conversationId;
  }
);

export const fetchUnreadCounts = createAsyncThunk(
  "chat/fetchUnreadCounts",
  async () => {
    return await chatApi.getUnreadCounts();
  }
);

const chatSlice = createSlice({
  name: "chat",
  initialState,
  reducers: {
    setActiveConversation: (state, action: PayloadAction<ConversationResponse | null>) => {
      state.activeConversation = action.payload;
      state.messages = [];
    },
    addMessage: (state, action: PayloadAction<MessageResponse>) => {
      if (!state.messages.find((m) => m.id === action.payload.id)) {
        state.messages.push(action.payload);
      }
    },
    incrementUnread: (state, action: PayloadAction<number>) => {
      const convId = action.payload;
      const prev = state.unreadByConversation[convId] || 0;
      state.unreadByConversation[convId] = prev + 1;
      state.unreadTotal += 1;
    },
    clearUnread: (state, action: PayloadAction<number>) => {
      const convId = action.payload;
      const prev = state.unreadByConversation[convId] || 0;
      if (prev > 0) {
        state.unreadTotal = Math.max(0, state.unreadTotal - prev);
        delete state.unreadByConversation[convId];
      }
    },
    clearChat: (state) => {
      state.activeConversation = null;
      state.messages = [];
    },
  },
  extraReducers: (builder) => {
    // Fetch conversations
    builder.addCase(fetchConversations.pending, (state) => {
      state.loading = true;
    });
    builder.addCase(fetchConversations.fulfilled, (state, action: PayloadAction<ConversationResponse[]>) => {
      state.loading = false;
      state.conversations = action.payload;
    });
    builder.addCase(fetchConversations.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Failed to fetch conversations";
    });

    // Fetch messages
    builder.addCase(fetchMessages.fulfilled, (state, action: PayloadAction<Page<MessageResponse>>) => {
      state.messages = action.payload.content.reverse();
    });

    // Send message
    builder.addCase(sendMessage.fulfilled, (state, action: PayloadAction<MessageResponse>) => {
      if (!state.messages.find((m) => m.id === action.payload.id)) {
        state.messages.push(action.payload);
      }
    });

    // Get or create task conversation
    builder.addCase(getOrCreateTaskConversation.fulfilled, (state, action: PayloadAction<ConversationResponse>) => {
      state.activeConversation = action.payload;
      if (!state.conversations.find((c) => c.id === action.payload.id)) {
        state.conversations.push(action.payload);
      }
    });

    builder.addCase(getOrCreateDirectConversation.fulfilled, (state, action: PayloadAction<ConversationResponse>) => {
      state.activeConversation = action.payload;
      if (!state.conversations.find((c) => c.id === action.payload.id)) {
        state.conversations.push(action.payload);
      }
    });

    builder.addCase(markConversationRead.fulfilled, (state, action: PayloadAction<number>) => {
      const convId = action.payload;
      const prev = state.unreadByConversation[convId] || 0;
      if (prev > 0) {
        state.unreadTotal = Math.max(0, state.unreadTotal - prev);
        delete state.unreadByConversation[convId];
      }
    });

    builder.addCase(fetchUnreadCounts.fulfilled, (state, action: PayloadAction<Record<string, number>>) => {
      const counts = action.payload || {};
      state.unreadByConversation = {};
      state.unreadTotal = 0;
      Object.entries(counts).forEach(([id, count]) => {
        const convId = Number(id);
        if (Number.isFinite(convId) && count > 0) {
          state.unreadByConversation[convId] = count;
          state.unreadTotal += count;
        }
      });
    });
  },
});

export const { setActiveConversation, addMessage, incrementUnread, clearUnread, clearChat } = chatSlice.actions;
export default chatSlice.reducer;
