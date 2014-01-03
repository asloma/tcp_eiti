CC=gcc
CFLAGS=-c -Wall

all: tcp_server

tcp_server: main.o listen_module.o  parser_module.o communication_module.o execute_module.o 
	$(CC)  main.o listen_module.o communication_module.o parser_module.o  execute_module.o -o tcp_server

main.o: main.c
	$(CC) $(CFLAGS) main.c

communication_module.o: communication_module.c communication_module.h
	$(CC) $(CFLAGS) communication_module.c communication_module.h

listen_module.o: listen_module.c listen_module.h
	$(CC) $(CFLAGS) listen_module.c listen_module.h

execute_module.o: execute_module.c execute_module.h
	$(CC) $(CFLAGS) execute_module.c execute_module.h

parser_module.o: parser_module.c parser_module.h
	$(CC) $(CFLAGS) parser_module.c parser_module.h

clean:
	rm -rf *o tcp_server
