import { configureStore } from "@reduxjs/toolkit";
import authReducer from "./slices/auth.slice";
import tasksReducer from "./slices/tasks.slice";
import chatReducer from "./slices/chat.slice";
import notificationsReducer from "./slices/notifications.slice";
import paymentReducer from "./slices/payment.slice";
import languageReducer from "./slices/LanguagesSlices";
import blockchainReducer from "./slices/blockchain.slice";
import submissionReducer from "./slices/submission.slice";
import profileReducer from "./slices/profile.slice";

export const store = configureStore({
  reducer: {
    auth: authReducer,
    tasks: tasksReducer,
    chat: chatReducer,
    notifications: notificationsReducer,
    payment: paymentReducer,
    language: languageReducer,
    blockchain: blockchainReducer,
    submissions: submissionReducer,
    profile: profileReducer,
  },
  middleware: (g) => g({ serializableCheck: false }),
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;
