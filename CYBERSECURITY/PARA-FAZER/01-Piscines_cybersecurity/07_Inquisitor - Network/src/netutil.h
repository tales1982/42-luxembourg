#ifndef NETUTIL_H
# define NETUTIL_H

# include <netinet/in.h>
# include <stddef.h>

/* Parses a dotted-decimal IPv4 address. Rejects anything else
 * (including IPv6) so the tool only ever deals with IPv4, as
 * required. Returns 0 on success, -1 on error. */
int	parse_ipv4(const char *str, struct in_addr *out);

/* Parses a MAC address in aa:bb:cc:dd:ee:ff (or AA-BB-...) form.
 * Returns 0 on success, -1 on error. */
int	parse_mac(const char *str, unsigned char out[6]);

/* Formats a MAC address as "aa:bb:cc:dd:ee:ff" into `out` (>= 18 bytes). */
void	mac_to_str(const unsigned char mac[6], char *out, size_t out_size);

/* Reads the hardware (MAC) address of `ifname` via SIOCGIFHWADDR.
 * Returns 0 on success, -1 on error. */
int	get_interface_mac(const char *ifname, unsigned char out[6]);

/* Picks the first non-loopback network interface that is UP, unless
 * INQUISITOR_IFACE is set in the environment, in which case that name
 * is used directly. Returns 0 on success (out filled), -1 if none
 * found. */
int	find_default_interface(char *out, size_t out_size);

#endif
