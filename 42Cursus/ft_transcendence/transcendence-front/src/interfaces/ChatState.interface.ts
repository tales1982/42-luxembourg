import type { ConversationResponse, MessageResponse} from "../types";

export interface ChatState {
  conversations: ConversationResponse[];
  activeConversation: ConversationResponse | null;
  messages: MessageResponse[];
  unreadByConversation: Record<number, number>;
  unreadTotal: number;
  loading: boolean;
  error: string | null;
}
