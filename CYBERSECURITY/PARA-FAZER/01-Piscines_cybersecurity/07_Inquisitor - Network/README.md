# inquisitor

Full-duplex ARP poisoning between two IPv4 hosts, with live FTP
control-channel sniffing (filenames by default, full traffic including
login with `-v`/`--verbose`). Restores both ARP tables on `CTRL+C`.

## Build

```bash
make            # builds ./inquisitor (needs libpcap-dev)
make test       # unit tests for the modules that don't need pcap/root
```

## Usage

```bash
sudo ./inquisitor [-v|--verbose] <IP-src> <MAC-src> <IP-target> <MAC-target>
```

- IPv4 only (rejects IPv6/malformed input outright).
- Needs `CAP_NET_RAW`/`CAP_NET_ADMIN` (raw sockets via libpcap) — run as
  root or in a container with those capabilities.
- Auto-detects the network interface (first non-loopback UP interface;
  override with `INQUISITOR_IFACE=eth1`).
- Every ~2s it sends ARP replies telling `IP-src` that `IP-target` is
  at our MAC, and telling `IP-target` that `IP-src` is at our MAC
  (`src/arp_poison.c`). Best-effort enables `/proc/sys/net/ipv4/ip_forward`
  so traffic keeps flowing through us instead of just breaking.
- Concurrently sniffs `tcp port 21` (`src/sniff_ftp.c`) and prints
  every `RETR`/`STOR`/`STOU`/`APPE`/`DELE`/`RNFR`/`RNTO`/... command's
  filename as it's seen; `-v` also prints every other control-channel
  line, including `USER`/`PASS`.
- `CTRL+C` stops both the poisoning loop and the capture, then sends
  corrective ARP replies restoring the genuine MAC↔IP mappings on both
  sides before exiting.

## Why a container/VM, and how the test environment works

Raw sockets need elevated privileges, so per the subject this has to
run in a container or VM. `docker/docker-compose.yml` builds a
complete, self-contained MITM demo with three services on one bridge
network with **static IPs and MAC addresses** (so `inquisitor`'s 4
arguments can be hardcoded rather than discovered at runtime):

| Service | IP | MAC | Role |
|---|---|---|---|
| `ftp-server` | 172.28.0.10 | 02:42:ac:1c:00:0a | vsftpd, one test file |
| `client` | 172.28.0.20 | 02:42:ac:1c:00:14 | curl-based FTP session (RETR + STOR) |
| `inquisitor` | 172.28.0.30 | — | this tool, `cap_add: [NET_ADMIN, NET_RAW]` |

```bash
make docker-test   # builds and runs all three, torn down when client finishes
make docker-down   # cleanup
```

`client` waits a few seconds for the poisoning to establish, then logs
into `ftp-server` and does a `RETR secret_report.pdf` followed by a
`STOR upload_me.txt`. Since compose runs with `--abort-on-container-exit`,
the whole demo stops once the client's script finishes — by then
`inquisitor`'s log should show both commands.

## Tests

```bash
make test
```

Runs `tests/test_units.c`: 28 assertions covering IPv4/MAC parsing and
validation, the exact byte layout of the crafted ARP frame (Ethernet
header, htype/ptype/hlen/plen/oper, sender/target fields — checked
byte-by-byte against the real ARP wire format), and FTP line-splitting
plus filename-command extraction (RETR/STOR/case-insensitivity/rejecting
non-filename commands like `USER`). None of this needs root or libpcap,
so it runs anywhere.

The parts that do need root/libpcap/a real network (actually sending
ARP frames, actually capturing FTP traffic) are exercised by
`make docker-test` above, and were additionally checked with
`-fsyntax-only` against the real `pcap.h` API shape during development.

## Design notes

- **Interface/MAC discovery** (`src/netutil.c`) avoids hardcoding an
  interface name, since it differs between a bare VM (`eth0`) and
  Docker (also usually `eth0`, but overridable via `INQUISITOR_IFACE`).
- **ARP frame building** (`src/arp_packet.c`) is a pure, pcap-free
  function — the same code path is used for both poisoning (sender MAC
  = us) and restoring (sender MAC = the real owner), which is also why
  it's exhaustively unit-tested at the byte level.
- **FTP parsing** (`src/ftp_parse.c`) only looks at the control channel
  (port 21): every command a client issues, including `RETR`/`STOR`,
  travels there regardless of active/passive data-connection mode, so
  there's no need to track dynamically-negotiated data ports to see
  filenames or the login exchange.
