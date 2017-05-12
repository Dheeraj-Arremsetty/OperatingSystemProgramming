CC = gcc
CFLAGS = -g
.SUFFIXES: .c 
all: master slave

master: 
	$(CC) -o master  master.c
slave: 
	$(CC) -o client  client.c
clean:
	/bin/rm -f *.o master slave

