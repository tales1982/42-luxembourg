import { createAsyncThunk, createSlice } from "@reduxjs/toolkit";
import type { PayloadAction } from "@reduxjs/toolkit";
import { profileApi } from "../../lib/api";
import type { UserProfileRequest, UserProfileResponse } from "../../types";

interface ProfileState {
  profile: UserProfileResponse | null;
  loading: boolean;
  saving: boolean;
  error: string | null;
}

const initialState: ProfileState = {
  profile: null,
  loading: false,
  saving: false,
  error: null,
};

export const fetchProfile = createAsyncThunk(
  "profile/fetch",
  async (_, { rejectWithValue }) => {
    try {
      return await profileApi.getMyProfile();
    } catch {
      // New user may not have a profile yet — treat as empty
      return rejectWithValue(null);
    }
  }
);

export const saveProfile = createAsyncThunk(
  "profile/save",
  async (data: UserProfileRequest) => {
    return await profileApi.updateProfile(data);
  }
);

const profileSlice = createSlice({
  name: "profile",
  initialState,
  reducers: {
    clearProfileError: (state) => {
      state.error = null;
    },
    setProfile: (state, action: PayloadAction<UserProfileResponse | null>) => {
      state.profile = action.payload;
    },
    resetProfile: (state) => {
      state.profile = null;
    },
  },
  extraReducers: (builder) => {
    builder
      .addCase(fetchProfile.pending, (state) => {
        state.loading = true;
        state.error = null;
      })
      .addCase(fetchProfile.fulfilled, (state, action) => {
        state.loading = false;
        state.profile = action.payload;
      })
      .addCase(fetchProfile.rejected, (state) => {
        state.loading = false;
        state.profile = null; // no profile yet for this user
      })
      .addCase(saveProfile.pending, (state) => {
        state.saving = true;
        state.error = null;
      })
      .addCase(saveProfile.fulfilled, (state, action) => {
        state.saving = false;
        state.profile = action.payload;
      })
      .addCase(saveProfile.rejected, (state, action) => {
        state.saving = false;
        state.error = action.error.message ?? "Failed to save profile";
      });
  },
});

export const { clearProfileError, setProfile, resetProfile } = profileSlice.actions;
export default profileSlice.reducer;
