FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        libpcap-dev \
        iproute2 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /inquisitor
COPY Makefile ./
COPY src ./src

RUN make

ENTRYPOINT ["./inquisitor"]
