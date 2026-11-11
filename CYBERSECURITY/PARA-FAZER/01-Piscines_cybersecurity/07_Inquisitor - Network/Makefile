NAME = inquisitor
SRC = src/inquisitor.c src/netutil.c src/arp_packet.c src/arp_poison.c \
      src/sniff_ftp.c src/ftp_parse.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2
LDFLAGS = -lpcap -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Unit tests for the modules that don't touch pcap/raw sockets (no
# root, no libpcap needed to run these).
test:
	$(CC) -Wall -Wextra -Werror -O2 tests/test_units.c \
		src/netutil.c src/arp_packet.c src/ftp_parse.c -o tests/test_units
	./tests/test_units

# Builds and runs the full 3-container MITM demo (attacker + client +
# FTP server) with docker compose, without any manual setup.
docker-test:
	docker compose -f docker/docker-compose.yml up --build --abort-on-container-exit

docker-down:
	docker compose -f docker/docker-compose.yml down -v

clean:
	rm -f $(OBJ) tests/test_units

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all test docker-test docker-down clean fclean re
