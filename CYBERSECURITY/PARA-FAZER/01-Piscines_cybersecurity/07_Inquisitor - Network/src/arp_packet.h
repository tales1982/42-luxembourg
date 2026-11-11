#ifndef ARP_PACKET_H
# define ARP_PACKET_H

# include <stddef.h>
# include <netinet/in.h>

# define ARP_FRAME_LEN 42	/* 14-byte Ethernet header + 28-byte ARP payload */

/*
 * Builds a raw Ethernet frame carrying an ARP reply (operation = 2)
 * into `buf`, which must be at least ARP_FRAME_LEN bytes.
 *
 *   eth_dst      - Ethernet destination (the host we're sending to)
 *   eth_src      - Ethernet source (normally our own interface MAC)
 *   arp_sender_* - the "sender" fields of the ARP payload itself: what
 *                  the receiving host's ARP cache will learn/overwrite
 *   arp_target_* - the "target" fields: whose cache entry this claims
 *                  to be a reply to
 *
 * For poisoning, arp_sender_mac is our own MAC (so eth_src ==
 * arp_sender_mac) and arp_sender_ip is the IP of the *other* victim,
 * spoofing "IP <arp_sender_ip> is at MAC <arp_sender_mac>=us".
 *
 * For restoring, arp_sender_mac is the victim's *real* MAC, so the
 * receiving host's cache is corrected back to the truth.
 *
 * Returns ARP_FRAME_LEN.
 */
size_t	build_arp_reply(unsigned char *buf, size_t bufsize,
		const unsigned char eth_dst[6], const unsigned char eth_src[6],
		const unsigned char arp_sender_mac[6], struct in_addr arp_sender_ip,
		const unsigned char arp_target_mac[6], struct in_addr arp_target_ip);

#endif
