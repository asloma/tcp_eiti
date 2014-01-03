CC=gcc
CFLAGS=-c -Wall

all: tcp_client

tcp_client: client.o 
	$(CC)  client.o -o tcp_client

client.o: client.c client.h
	$(CC) $(CFLAGS) client.c client.h

clean:
	rm -rf *o tcp_server
