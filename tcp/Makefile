CC=gcc
AR=ar
FLAGS= -Wall -g

all: net_client nslookup

net_client: net_client.o nslookup.a
	$(CC) $(FLAGS) -o net_client net_client.o nslookup.a

nslookup.a: nslookup.o
	$(AR) -rcs nslookup.a nslookup.o

net_client.o: net_client.c nslookup.h
	$(CC) $(FLAGS) -c net_client.c

nslookup.o: nslookup.c nslookup.h
	$(CC) $(FLAGS) -c nslookup.c

clean:
	rm -f net_client net_server *.o *.a