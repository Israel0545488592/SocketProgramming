CC = gcc
AR = ar
FLAGS = -Wall -g

all: gateway source

gateway: gateway.c
	$(CC) $(FLAGS) gateway.c -o gateway

send: source.c
	$(CC) $(FLAGS) source.c -o source

clean:
	rm -f source gateway