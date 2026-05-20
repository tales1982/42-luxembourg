package com.transcendence.friend.repository;

import com.transcendence.friend.entity.Friend;
import com.transcendence.friend.entity.FriendStatus;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface FriendRepository extends JpaRepository<Friend, Long> {

    @Query("SELECT f FROM Friend f WHERE (f.requester.id = :userId OR f.addressee.id = :userId) AND f.status = 'ACCEPTED'")
    List<Friend> findAcceptedByUserId(@Param("userId") Long userId);

    List<Friend> findByAddresseeIdAndStatus(Long addresseeId, FriendStatus status);

    List<Friend> findByRequesterIdAndStatus(Long requesterId, FriendStatus status);

    @Query("SELECT CASE WHEN COUNT(f) > 0 THEN true ELSE false END FROM Friend f WHERE (f.requester.id = :id1 AND f.addressee.id = :id2) OR (f.requester.id = :id2 AND f.addressee.id = :id1)")
    boolean existsBetween(@Param("id1") Long id1, @Param("id2") Long id2);

    @Query("SELECT f FROM Friend f WHERE (f.requester.id = :id1 AND f.addressee.id = :id2) OR (f.requester.id = :id2 AND f.addressee.id = :id1)")
    Optional<Friend> findBetween(@Param("id1") Long id1, @Param("id2") Long id2);
}
