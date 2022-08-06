CC=gcc
AR=ar
FLAGS= -Wall -g

all: source gateway sink

source: source.o print_socket.a
	$(CC) $(FLAGS) -o source source.o print_socket.a

gateway: gateway.o print_socket.a
	$(CC) $(FLAGS) -o gateway gateway.o print_socket.a

sink: sink.o print_socket.a
	$(CC) $(FLAGS) -o sink sink.o print_socket.a

gateway.o: gateway.c print_socket.h
	$(CC) $(FLAGS) -c gateway.c

sink.o: sink.c print_socket.h
	$(CC) $(FLAGS) -c sink.c

print_socket.a: print_socket.o
	$(AR) -rcs print_socket.a print_socket.o

print_socket.o: print_socket.c print_socket.h
	$(CC) $(FLAGS) -c print_socket.c

clean:
	rm -f source gateway sink *.o *.a