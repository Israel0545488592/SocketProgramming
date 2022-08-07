CC = gcc
AR = ar
FLAGS = -Wall -g

all: recive send

recive: recv_udp.c
	$(CC) $(FLAGS) recv_udp.c -o recive

send: send_udp.c
	$(CC) $(FLAGS) send_udp.c -o send

clean:
	rm -f send recive