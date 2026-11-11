#ifndef ARP_POISON_H
# define ARP_POISON_H

# include <pcap.h>
# include <netinet/in.h>

typedef struct
{
	unsigned char	our_mac[6];
	unsigned char	mac_a[6];
	unsigned char	mac_b[6];
	struct in_addr	ip_a;
	struct in_addr	ip_b;
}	poison_targets_t;

/* Sends one round of poisoning frames in both directions:
 *   tells A that B's IP is at our MAC, and tells B that A's IP is at
 *   our MAC. Returns 0 if both sends succeeded, -1 otherwise (logged
 *   by the caller via pcap_geterr). */
int	arp_poison_once(pcap_t *handle, const poison_targets_t *t);

/* Sends corrective ARP replies restoring the genuine MAC <-> IP
 * mappings on both sides. Best-effort: sent `repeats` times to raise
 * the odds of landing before the caches expire naturally. */
void	arp_restore(pcap_t *handle, const poison_targets_t *t, int repeats);

#endif
