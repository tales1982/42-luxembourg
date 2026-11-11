#ifndef SNIFF_FTP_H
# define SNIFF_FTP_H

# include <pcap.h>

/*
 * Opens `iface` for live capture with a "tcp port 21" BPF filter and
 * runs pcap_loop() until pcap_breakloop() is called (e.g. from a
 * signal handler) or an error occurs. Every FTP control-channel line
 * observed is printed; in verbose mode every line (including the
 * login exchange) is shown, otherwise only filename-bearing commands
 * (RETR/STOR/...) are. Returns the opened handle so the caller can
 * call pcap_breakloop()/pcap_close() on it, or NULL on failure.
 */
pcap_t	*sniff_ftp_open(const char *iface, char *errbuf);
int	sniff_ftp_run(pcap_t *handle, int verbose);

#endif
