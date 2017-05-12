CC = gcc
CFLAGS = -g
.SUFFIXES: .c 
all: master slave

master:
	rm oss 
	$(CC) -o oss  master.c
slave: 
	rm slave
	$(CC) -o slave  client.c
clean:
	/bin/rm -f *.o master slave

