pgm: client.o server.o
	gcc -o pgm client.o server.o

server.o: server.c server.h
	gcc -c server.c

client.o: client.c
	gcc -c client.c