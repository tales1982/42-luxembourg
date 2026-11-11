FROM debian:bookworm

RUN apt update && apt install -y \
    nginx \
    tor \
    openssh-server \
    supervisor \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/run/sshd /var/www/html /var/lib/tor/ft_onion

COPY index.html /var/www/html/index.html
COPY nginx.conf /etc/nginx/sites-available/default
COPY sshd_config /etc/ssh/sshd_config
COPY torrc /etc/tor/torrc

RUN useradd -m -s /bin/bash onionuser && \
    echo "onionuser:ft_onion42" | chpasswd && \
    printf '%s\n' \
        "############################################" \
        "#                                          #" \
        "#   Unauthorized access is prohibited.    #" \
        "#   All connections are logged.           #" \
        "#                                          #" \
        "############################################" \
        > /etc/ssh/banner && \
    chown -R debian-tor:debian-tor /var/lib/tor/ft_onion && \
    chmod 700 /var/lib/tor/ft_onion

COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

EXPOSE 80 4242

CMD ["/usr/bin/supervisord", "-n"]
