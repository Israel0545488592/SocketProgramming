

all: client server lookup

client: net_client.c
		gcc net_client.c -o net_client

server: net_server.c
		gcc net_server.c -o net_server

lookup: nslookup.c
		gcc nslookup.c -o lookup

clean:
		rm -f lookup net_client net_server
		