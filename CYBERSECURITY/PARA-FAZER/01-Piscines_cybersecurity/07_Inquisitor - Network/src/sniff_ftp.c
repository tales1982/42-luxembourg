#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include "sniff_ftp.h"
#include "ftp_parse.h"

#define ETH_HDR_LEN 14

typedef struct
{
	int	verbose;
	char	src_ip[INET_ADDRSTRLEN];
	char	dst_ip[INET_ADDRSTRLEN];
}	line_ctx_t;

static void	print_line(const char *line, void *user)
{
	line_ctx_t	*ctx;
	char		filename[512];

	ctx = (line_ctx_t *)user;
	if (ftp_filename_command(line, filename, sizeof(filename)))
		printf("[inquisitor] %s -> %s file: %s (%s)\n",
			ctx->src_ip, ctx->dst_ip, filename, line);
	else if (ctx->verbose)
		printf("[inquisitor] %s -> %s: %s\n", ctx->src_ip, ctx->dst_ip, line);
}

pcap_t	*sniff_ftp_open(const char *iface, char *errbuf)
{
	pcap_t			*handle;
	struct bpf_program	prog;

	handle = pcap_open_live(iface, 65535, 1, 500, errbuf);
	if (!handle)
		return (NULL);
	if (pcap_compile(handle, &prog, "tcp port 21", 1, PCAP_NETMASK_UNKNOWN) != 0)
	{
		snprintf(errbuf, PCAP_ERRBUF_SIZE, "%s", pcap_geterr(handle));
		pcap_close(handle);
		return (NULL);
	}
	if (pcap_setfilter(handle, &prog) != 0)
	{
		snprintf(errbuf, PCAP_ERRBUF_SIZE, "%s", pcap_geterr(handle));
		pcap_freecode(&prog);
		pcap_close(handle);
		return (NULL);
	}
	pcap_freecode(&prog);
	return (handle);
}

static void	handle_packet(unsigned char *user, const struct pcap_pkthdr *h,
			const unsigned char *bytes)
{
	int			verbose;
	const struct ether_header	*eth;
	const struct ip		*iph;
	const struct tcphdr	*tcph;
	size_t			ip_hlen;
	size_t			tcp_hlen;
	size_t			offset;
	line_ctx_t		ctx;

	verbose = *(int *)user;
	if (h->caplen < ETH_HDR_LEN + sizeof(struct ip))
		return;
	eth = (const struct ether_header *)bytes;
	if (ntohs(eth->ether_type) != ETHERTYPE_IP)
		return;
	iph = (const struct ip *)(bytes + ETH_HDR_LEN);
	ip_hlen = (size_t)iph->ip_hl * 4;
	if (iph->ip_p != IPPROTO_TCP)
		return;
	if (h->caplen < ETH_HDR_LEN + ip_hlen + sizeof(struct tcphdr))
		return;
	tcph = (const struct tcphdr *)(bytes + ETH_HDR_LEN + ip_hlen);
	tcp_hlen = (size_t)tcph->th_off * 4;
	offset = ETH_HDR_LEN + ip_hlen + tcp_hlen;
	if (h->caplen <= offset)
		return;

	ctx.verbose = verbose;
	inet_ntop(AF_INET, &iph->ip_src, ctx.src_ip, sizeof(ctx.src_ip));
	inet_ntop(AF_INET, &iph->ip_dst, ctx.dst_ip, sizeof(ctx.dst_ip));

	ftp_extract_lines((const char *)(bytes + offset), h->caplen - offset,
		print_line, &ctx);
}

int	sniff_ftp_run(pcap_t *handle, int verbose)
{
	return (pcap_loop(handle, -1, handle_packet, (unsigned char *)&verbose));
}
