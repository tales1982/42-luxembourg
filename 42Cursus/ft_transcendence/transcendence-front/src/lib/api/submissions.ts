import { api } from "./client";
import { env } from "../../config/env";
import type {
  TaskSubmissionRequest,
  TaskSubmissionResponse,
  TaskAttachmentResponse,
  ReviewSubmissionRequest,
  Page,
} from "../../types";

// Backend builds the URL using Docker's internal hostname; fix it to use the browser-accessible base URL
function fixAttachmentUrl(attachment: TaskAttachmentResponse): TaskAttachmentResponse {
  const fixed = attachment.url.replace(/^https?:\/\/[^/]+/, env.API_BASE_URL);
  return { ...attachment, url: fixed };
}

// Task Submissions API
export const submissionApi = {
  // Get submissions for a task
  getTaskSubmissions: (taskId: number) =>
    api.get<TaskSubmissionResponse[]>(`/api/submissions/task/${taskId}`).then((res) => res.data),

  // Get current user's submissions
  getMySubmissions: (page = 0, size = 10) =>
    api.get<Page<TaskSubmissionResponse>>("/api/submissions/my", { params: { page, size } }).then((res) => res.data),

  // Get submission by ID
  getSubmission: (id: number) =>
    api.get<TaskSubmissionResponse>(`/api/submissions/${id}`).then((res) => res.data),

  // Submit a task
  submitTask: (taskId: number, data: TaskSubmissionRequest) =>
    api.post<TaskSubmissionResponse>(`/api/submissions/task/${taskId}`, data).then((res) => res.data),

  // Review a submission (approve/reject)
  reviewSubmission: (submissionId: number, data: ReviewSubmissionRequest) =>
    api.post<TaskSubmissionResponse>(`/api/submissions/${submissionId}/review`, data).then((res) => res.data),

  // Approve submission (shorthand)
  approveSubmission: (submissionId: number, reviewNotes?: string) =>
    api.post<TaskSubmissionResponse>(`/api/submissions/${submissionId}/review`, {
      approved: true,
      reviewNotes,
    }).then((res) => res.data),

  // Reject submission (shorthand)
  rejectSubmission: (submissionId: number, reviewNotes?: string) =>
    api.post<TaskSubmissionResponse>(`/api/submissions/${submissionId}/review`, {
      approved: false,
      reviewNotes,
    }).then((res) => res.data),

  // Get attachments for a submission
  getAttachments: (submissionId: number) =>
    api.get<TaskAttachmentResponse[]>(`/api/submissions/${submissionId}/attachments`)
      .then((res) => res.data.map(fixAttachmentUrl)),

  // Upload proof file for a submission
  uploadProofFile: (submissionId: number, file: File) => {
    const formData = new FormData();
    formData.append("file", file);
    // Use transformRequest to delete Content-Type before sending.
    // The axios instance defaults to "application/json" which overrides FormData detection.
    // Deleting it here lets the browser set "multipart/form-data; boundary=..." automatically.
    return api.post(`/api/submissions/${submissionId}/upload`, formData, {
      transformRequest: [(data, headers) => {
        if (headers) delete (headers as Record<string, string>)["Content-Type"];
        return data;
      }],
    }).then((res) => res.data);
  },
};
