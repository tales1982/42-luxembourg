import { api } from "./client";

export type FriendStatus = "PENDING" | "ACCEPTED";

export interface FriendEntry {
  id: number;
  userId: number;
  email: string;
  displayName: string;
  status: FriendStatus;
  iAmRequester: boolean;
  createdAt: string;
}

export interface UserSearchResult {
  id: number;
  email: string;
  displayName: string;
}

export const friendsApi = {
  list: (): Promise<FriendEntry[]> =>
    api.get<FriendEntry[]>("/api/friends").then((r) => r.data),

  pendingReceived: (): Promise<FriendEntry[]> =>
    api.get<FriendEntry[]>("/api/friends/pending/received").then((r) => r.data),

  pendingSent: (): Promise<FriendEntry[]> =>
    api.get<FriendEntry[]>("/api/friends/pending/sent").then((r) => r.data),

  sendRequest: (email: string): Promise<FriendEntry> =>
    api.post<FriendEntry>("/api/friends/request", null, { params: { email } }).then((r) => r.data),

  accept: (id: number): Promise<FriendEntry> =>
    api.post<FriendEntry>(`/api/friends/${id}/accept`).then((r) => r.data),

  reject: (id: number): Promise<void> =>
    api.post(`/api/friends/${id}/reject`).then(() => undefined),

  remove: (id: number): Promise<void> =>
    api.delete(`/api/friends/${id}`).then(() => undefined),

  search: (q: string): Promise<UserSearchResult[]> =>
    api.get<UserSearchResult[]>("/api/friends/search", { params: { q } }).then((r) => r.data),

  sendRequestById: (userId: number): Promise<FriendEntry> =>
    api.post<FriendEntry>(`/api/friends/request/user/${userId}`).then((r) => r.data),
};
