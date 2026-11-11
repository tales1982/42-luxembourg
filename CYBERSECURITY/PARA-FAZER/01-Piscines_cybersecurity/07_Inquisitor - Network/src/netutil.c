#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <stdlib.h>
#include "netutil.h"

int	parse_ipv4(const char *str, struct in_addr *out)
{
	if (!str || !out)
		return (-1);
	if (inet_pton(AF_INET, str, out) != 1)
		return (-1);
	return (0);
}

int	parse_mac(const char *str, unsigned char out[6])
{
	unsigned int	b[6];
	int		n;
	int		i;

	if (!str)
		return (-1);
	n = sscanf(str, "%2x:%2x:%2x:%2x:%2x:%2x",
			&b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
	if (n != 6)
	{
		n = sscanf(str, "%2x-%2x-%2x-%2x-%2x-%2x",
				&b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
	}
	if (n != 6)
		return (-1);
	for (i = 0; i < 6; i++)
	{
		if (b[i] > 0xff)
			return (-1);
		out[i] = (unsigned char)b[i];
	}
	return (0);
}

void	mac_to_str(const unsigned char mac[6], char *out, size_t out_size)
{
	snprintf(out, out_size, "%02x:%02x:%02x:%02x:%02x:%02x",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

int	get_interface_mac(const char *ifname, unsigned char out[6])
{
	int		fd;
	struct ifreq	ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return (-1);
	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", ifname);
	if (ioctl(fd, SIOCGIFHWADDR, &ifr) != 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	memcpy(out, ifr.ifr_hwaddr.sa_data, 6);
	return (0);
}

int	find_default_interface(char *out, size_t out_size)
{
	const char		*env;
	struct ifaddrs		*list;
	struct ifaddrs		*cur;
	int			found;

	env = getenv("INQUISITOR_IFACE");
	if (env && env[0] != '\0')
	{
		snprintf(out, out_size, "%s", env);
		return (0);
	}
	if (getifaddrs(&list) != 0)
		return (-1);
	found = -1;
	for (cur = list; cur; cur = cur->ifa_next)
	{
		if (cur->ifa_flags & IFF_LOOPBACK)
			continue;
		if (!(cur->ifa_flags & IFF_UP))
			continue;
		snprintf(out, out_size, "%s", cur->ifa_name);
		found = 0;
		break;
	}
	freeifaddrs(list);
	return (found);
}
