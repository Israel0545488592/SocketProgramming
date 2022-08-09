CC=gcc
AR=ar
FLAGS= -Wall -g

web_client: web_client.o urlib.a
	$(CC) $(FLAGS) -o web_client web_client.o urlib.a

urlib.a: urlib.o
	$(AR) -rcs urlib.a urlib.o

net_client.o: web_client.c urlib.h
	$(CC) $(FLAGS) -c web_client.c

urlib.o: urlib.c urlib.h
	$(CC) $(FLAGS) -c urlib.c

clean:
	rm -f web_client *.o *.a