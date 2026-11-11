#include <stdio.h>
#include <string.h>
#include "../src/netutil.h"
#include "../src/arp_packet.h"
#include "../src/ftp_parse.h"

static int	g_failures = 0;

static void	check(int cond, const char *label)
{
	if (cond)
		printf("OK   %s\n", label);
	else
	{
		printf("FAIL %s\n", label);
		g_failures++;
	}
}

/* --- netutil --- */

static void	test_netutil(void)
{
	struct in_addr	addr;
	unsigned char	mac[6];
	char		buf[32];

	check(parse_ipv4("192.168.1.1", &addr) == 0, "parse_ipv4 accepts valid IPv4");
	check(parse_ipv4("::1", &addr) != 0, "parse_ipv4 rejects IPv6");
	check(parse_ipv4("999.1.1.1", &addr) != 0, "parse_ipv4 rejects out-of-range octet");
	check(parse_ipv4("not-an-ip", &addr) != 0, "parse_ipv4 rejects garbage");
	check(parse_ipv4("", &addr) != 0, "parse_ipv4 rejects empty string");

	check(parse_mac("aa:bb:cc:dd:ee:ff", mac) == 0
		&& mac[0] == 0xaa && mac[5] == 0xff, "parse_mac accepts colon form");
	check(parse_mac("AA-BB-CC-DD-EE-FF", mac) == 0
		&& mac[0] == 0xaa && mac[5] == 0xff, "parse_mac accepts dash form, case-insensitive");
	check(parse_mac("not-a-mac", mac) != 0, "parse_mac rejects garbage");
	check(parse_mac("aa:bb:cc:dd:ee", mac) != 0, "parse_mac rejects too few octets");

	mac_to_str(mac, buf, sizeof(buf));
	check(strcmp(buf, "aa:bb:cc:dd:ee:ff") == 0, "mac_to_str round-trips");
}

/* --- arp_packet --- */

static void	test_arp_packet(void)
{
	unsigned char	frame[ARP_FRAME_LEN];
	unsigned char	eth_dst[6] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
	unsigned char	eth_src[6] = {0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
	unsigned char	sender_mac[6] = {0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
	unsigned char	target_mac[6] = {0x33, 0x33, 0x33, 0x33, 0x33, 0x33};
	struct in_addr	sender_ip;
	struct in_addr	target_ip;
	size_t		n;

	parse_ipv4("10.0.0.1", &sender_ip);
	parse_ipv4("10.0.0.2", &target_ip);

	n = build_arp_reply(frame, sizeof(frame), eth_dst, eth_src,
			sender_mac, sender_ip, target_mac, target_ip);
	check(n == ARP_FRAME_LEN, "build_arp_reply returns full frame length");
	check(memcmp(frame, eth_dst, 6) == 0, "Ethernet dst matches");
	check(memcmp(frame + 6, eth_src, 6) == 0, "Ethernet src matches");
	check(frame[12] == 0x08 && frame[13] == 0x06, "Ethertype is ARP (0x0806)");
	check(frame[14] == 0x00 && frame[15] == 0x01, "ARP htype is Ethernet (1)");
	check(frame[16] == 0x08 && frame[17] == 0x00, "ARP ptype is IPv4 (0x0800)");
	check(frame[18] == 6 && frame[19] == 4, "ARP hlen=6, plen=4");
	check(frame[20] == 0x00 && frame[21] == 0x02, "ARP oper is reply (2)");
	check(memcmp(frame + 22, sender_mac, 6) == 0, "ARP sender MAC matches");
	check(memcmp(frame + 28, &sender_ip, 4) == 0, "ARP sender IP matches");
	check(memcmp(frame + 32, target_mac, 6) == 0, "ARP target MAC matches");
	check(memcmp(frame + 38, &target_ip, 4) == 0, "ARP target IP matches");

	n = build_arp_reply(frame, 10, eth_dst, eth_src, sender_mac, sender_ip, target_mac, target_ip);
	check(n == 0, "build_arp_reply refuses an undersized buffer");
}

/* --- ftp_parse --- */

static int	g_line_count = 0;
static char	g_last_line[256];

static void	collect_line(const char *line, void *user)
{
	(void)user;
	g_line_count++;
	snprintf(g_last_line, sizeof(g_last_line), "%s", line);
}

static void	test_ftp_parse(void)
{
	char	filename[256];
	const char	*msg = "USER anonymous\r\nPASS x@y.com\r\nRETR secret_report.pdf\r\n";

	g_line_count = 0;
	ftp_extract_lines(msg, strlen(msg), collect_line, NULL);
	check(g_line_count == 3, "ftp_extract_lines splits 3 CRLF-terminated lines");
	check(strcmp(g_last_line, "RETR secret_report.pdf") == 0, "last line has no CR left over");

	check(ftp_filename_command("RETR secret_report.pdf", filename, sizeof(filename)) == 1
		&& strcmp(filename, "secret_report.pdf") == 0, "RETR extracts the filename");
	check(ftp_filename_command("stor upload.bin", filename, sizeof(filename)) == 1
		&& strcmp(filename, "upload.bin") == 0, "STOR is case-insensitive");
	check(ftp_filename_command("USER anonymous", filename, sizeof(filename)) == 0,
		"USER is not treated as a filename command");
	check(ftp_filename_command("RETRXYZ file", filename, sizeof(filename)) == 0,
		"a verb-prefixed unrelated command is not matched");
	check(ftp_filename_command("RETR", filename, sizeof(filename)) == 0,
		"RETR with no argument is rejected");
}

int	main(void)
{
	test_netutil();
	test_arp_packet();
	test_ftp_parse();
	if (g_failures == 0)
		printf("\nAll unit tests passed.\n");
	else
		printf("\n%d unit test(s) FAILED.\n", g_failures);
	return (g_failures > 0);
}
