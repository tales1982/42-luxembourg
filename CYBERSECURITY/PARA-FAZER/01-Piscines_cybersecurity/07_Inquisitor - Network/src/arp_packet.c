#include <string.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include "arp_packet.h"

size_t	build_arp_reply(unsigned char *buf, size_t bufsize,
		const unsigned char eth_dst[6], const unsigned char eth_src[6],
		const unsigned char arp_sender_mac[6], struct in_addr arp_sender_ip,
		const unsigned char arp_target_mac[6], struct in_addr arp_target_ip)
{
	unsigned char	*p;

	if (bufsize < ARP_FRAME_LEN)
		return (0);
	memset(buf, 0, ARP_FRAME_LEN);
	p = buf;

	/* Ethernet header */
	memcpy(p, eth_dst, 6);
	p += 6;
	memcpy(p, eth_src, 6);
	p += 6;
	*p++ = (ETHERTYPE_ARP >> 8) & 0xff;
	*p++ = ETHERTYPE_ARP & 0xff;

	/* ARP payload */
	*p++ = 0x00; *p++ = 0x01;		/* htype = Ethernet */
	*p++ = 0x08; *p++ = 0x00;		/* ptype = IPv4 */
	*p++ = 6;				/* hlen */
	*p++ = 4;				/* plen */
	*p++ = 0x00; *p++ = ARPOP_REPLY;	/* oper = reply (2) */
	memcpy(p, arp_sender_mac, 6);
	p += 6;
	memcpy(p, &arp_sender_ip, 4);
	p += 4;
	memcpy(p, arp_target_mac, 6);
	p += 6;
	memcpy(p, &arp_target_ip, 4);
	p += 4;

	return (ARP_FRAME_LEN);
}
