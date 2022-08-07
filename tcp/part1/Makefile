CC=gcc
FLAGS= -Wall -g

all: net_client net_server nslookup

net_client: net_client.c
	$(CC) $(FLAGS) net_client.c -o net_client

net_server: net_server.c
	$(CC) $(FLAGS) net_server.c -o net_server

nslookup: nslookup.c
	$(CC) $(FLAGS) nslookup.c -o nslookup

clean:
	rm -f net_client net_server nslookup