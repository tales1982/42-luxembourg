# ft_onion

> A Tor hidden service running a static web page served by Nginx, with SSH access on port 4242.

---

## How to run

```bash
docker compose up --build
```

The container will print the `.onion` address in the logs once Tor finishes bootstrapping (~30 seconds).

To connect via SSH (inside the Tor network):
```bash
ssh -p 4242 onionuser@<address>.onion
```

---

## Architecture

```
┌─────────────────────────────────────────┐
│              Docker Container           │
│                                         │
│  supervisord (PID 1)                    │
│    ├── nginx  → 127.0.0.1:80           │
│    ├── sshd   → 0.0.0.0:4242           │
│    └── tor    → connects to Tor network │
│                   ↕                     │
│         HiddenService:80  → nginx       │
│         HiddenService:4242 → sshd       │
└─────────────────────────────────────────┘
```

No ports are published to the host. All access is through the Tor network via the `.onion` address.

---

## Technical choices

### Docker

The subject requires the server to run without opening ports on the host machine or configuring firewall rules. Docker achieves this naturally: using `EXPOSE` in the Dockerfile documents the ports but does not publish them. The `docker-compose.yml` deliberately has no `ports:` mapping, so nothing is reachable from the outside except through Tor.

A Docker image also makes the project fully reproducible and self-contained — the evaluator only needs to run `docker compose up`.

### Nginx

Required by the subject. Configured to listen only on `127.0.0.1:80` (loopback) so it is unreachable directly from outside the container. The Tor process forwards traffic from the `.onion` address to this local socket.

**Security headers added:**
- `server_tokens off` — hides the Nginx version from responses
- `X-Frame-Options: SAMEORIGIN` — prevents clickjacking
- `X-Content-Type-Options: nosniff` — prevents MIME-type sniffing
- `X-XSS-Protection: 1; mode=block` — legacy XSS filter for older browsers
- `Referrer-Policy: no-referrer` — no referrer information is leaked
- `Content-Security-Policy` — restricts resource origins to self only

### Tor (`torrc`)

```
DataDirectory /var/lib/tor
SocksPort 0
HiddenServiceDir /var/lib/tor/ft_onion/
HiddenServicePort 80 127.0.0.1:80
HiddenServicePort 4242 127.0.0.1:4242
```

- `DataDirectory /var/lib/tor` — set explicitly so Tor does not try to fall back to `~/.tor`, which fails when running as a non-root user under supervisord (which inherits root's HOME).
- `SocksPort 0` — disables the SOCKS proxy. This container acts only as a hidden service, not as a Tor client for outbound connections. Disabling the SOCKS port removes an unnecessary attack surface.
- `HiddenServicePort 80` and `HiddenServicePort 4242` — map the `.onion` ports to the internal services.

Tor runs as the `debian-tor` system user (set via supervisord's `user=debian-tor`) so it can write to `/var/lib/tor`, which is owned by that user.

### SSH (`sshd_config`)

Port changed to **4242** as required. All hardening below targets the bonus part:

| Directive | Value | Reason |
|---|---|---|
| `PermitRootLogin` | `no` | Root must never be accessible via SSH |
| `PermitEmptyPasswords` | `no` | Prevents empty-password accounts from being used |
| `MaxAuthTries` | `3` | Limits brute-force attempts per connection |
| `MaxSessions` | `2` | Limits simultaneous sessions |
| `LoginGraceTime` | `30` | Closes unauthenticated connections after 30 seconds |
| `AllowUsers` | `onionuser` | Whitelist: only this user can log in |
| `X11Forwarding` | `no` | No GUI forwarding needed; reduces attack surface |
| `AllowTcpForwarding` | `no` | Prevents using SSH as a tunnel |
| `AllowAgentForwarding` | `no` | Prevents SSH agent from being forwarded |
| `PermitTunnel` | `no` | No VPN-style tunneling |
| `GatewayPorts` | `no` | No remote port forwarding |
| `PermitUserEnvironment` | `no` | Prevents environment injection via `~/.ssh/environment` |
| `ClientAliveInterval` | `300` | Sends keepalive after 5 minutes of inactivity |
| `ClientAliveCountMax` | `2` | Disconnects after 2 missed keepalives (10 min idle max) |
| `LogLevel` | `VERBOSE` | Logs fingerprint of public keys used for authentication |
| `Banner` | `/etc/ssh/banner` | Displays a warning before authentication |

**Cryptographic restrictions** — only modern algorithms are allowed:

- `Ciphers`: `chacha20-poly1305`, `aes256-gcm`, `aes128-gcm` — all authenticated encryption; older ciphers like AES-CBC are excluded.
- `MACs`: `hmac-sha2-512-etm`, `hmac-sha2-256-etm` — encrypt-then-MAC only; legacy `hmac-md5` and `hmac-sha1` are excluded.
- `KexAlgorithms`: `curve25519-sha256`, `diffie-hellman-group18-sha512`, `diffie-hellman-group16-sha512` — elliptic curve preferred; weak DH groups excluded.

### Supervisord

Running three long-lived processes (nginx, sshd, tor) inside a single Docker container requires a process supervisor. Without it, only one process can be PID 1, and the others would have no parent to reap them if they exit. Supervisord handles:
- Starting all three services on container boot
- Restarting any service that crashes (`autorestart=true`)
- Running Tor as `debian-tor` while nginx and sshd run as root

---

## Files

| File | Purpose |
|---|---|
| `index.html` | Static page served by Nginx |
| `nginx.conf` | Nginx virtual host — listens on loopback only, security headers |
| `sshd_config` | SSH hardened configuration |
| `torrc` | Tor hidden service configuration |
| `supervisord.conf` | Process manager — starts nginx, sshd, tor |
| `Dockerfile` | Builds the container image |
| `docker-compose.yml` | Runs the container without publishing ports to the host |
