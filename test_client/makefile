CC=gcc
CFLAGS=-c -Wall

all: tcp_client

tcp_client: client.o 
	$(CC)  client.o -lm -o tcp_client

client.o: client.c client.h
	$(CC) $(CFLAGS) -lm client.c client.h

clean:
	rm -rf *o tcp_client
