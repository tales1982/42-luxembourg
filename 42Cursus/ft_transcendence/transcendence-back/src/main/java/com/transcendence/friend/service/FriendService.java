package com.transcendence.friend.service;

import com.transcendence.friend.dto.FriendResponse;
import com.transcendence.friend.entity.Friend;
import com.transcendence.friend.entity.FriendStatus;
import com.transcendence.friend.repository.FriendRepository;
import com.transcendence.user.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.List;

@Service
@RequiredArgsConstructor
public class FriendService {

    private final FriendRepository friendRepository;
    private final UserRepository userRepository;

    @Transactional
    public FriendResponse sendRequest(Long requesterId, String targetEmail) {
        var requester = userRepository.findById(requesterId)
                .orElseThrow(() -> new RuntimeException("User not found"));
        var addressee = userRepository.findByEmail(targetEmail)
                .orElseThrow(() -> new RuntimeException("User not found: " + targetEmail));

        if (requesterId.equals(addressee.getId())) {
            throw new RuntimeException("Cannot send friend request to yourself");
        }
        if (friendRepository.existsBetween(requesterId, addressee.getId())) {
            throw new RuntimeException("Friend request already exists");
        }

        var friend = Friend.builder()
                .requester(requester)
                .addressee(addressee)
                .status(FriendStatus.PENDING)
                .build();

        return FriendResponse.from(friendRepository.save(friend), requesterId);
    }

    @Transactional
    public FriendResponse accept(Long friendId, Long userId) {
        var friend = friendRepository.findById(friendId)
                .orElseThrow(() -> new RuntimeException("Friend request not found"));

        if (!friend.getAddressee().getId().equals(userId)) {
            throw new RuntimeException("Not authorized");
        }
        if (friend.getStatus() != FriendStatus.PENDING) {
            throw new RuntimeException("Request is not pending");
        }

        friend.setStatus(FriendStatus.ACCEPTED);
        friend.setUpdatedAt(LocalDateTime.now());
        return FriendResponse.from(friendRepository.save(friend), userId);
    }

    @Transactional
    public void reject(Long friendId, Long userId) {
        var friend = friendRepository.findById(friendId)
                .orElseThrow(() -> new RuntimeException("Friend request not found"));

        if (!friend.getAddressee().getId().equals(userId)) {
            throw new RuntimeException("Not authorized");
        }
        friendRepository.delete(friend);
    }

    @Transactional
    public void remove(Long friendId, Long userId) {
        var friend = friendRepository.findById(friendId)
                .orElseThrow(() -> new RuntimeException("Friend not found"));

        if (!friend.getRequester().getId().equals(userId) && !friend.getAddressee().getId().equals(userId)) {
            throw new RuntimeException("Not authorized");
        }
        friendRepository.delete(friend);
    }

    public List<FriendResponse> listFriends(Long userId) {
        return friendRepository.findAcceptedByUserId(userId)
                .stream()
                .map(f -> FriendResponse.from(f, userId))
                .toList();
    }

    public List<FriendResponse> listPendingReceived(Long userId) {
        return friendRepository.findByAddresseeIdAndStatus(userId, FriendStatus.PENDING)
                .stream()
                .map(f -> FriendResponse.from(f, userId))
                .toList();
    }

    public List<FriendResponse> listPendingSent(Long userId) {
        return friendRepository.findByRequesterIdAndStatus(userId, FriendStatus.PENDING)
                .stream()
                .map(f -> FriendResponse.from(f, userId))
                .toList();
    }
}
