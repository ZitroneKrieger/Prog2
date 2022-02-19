CC=gcc
CFLAGS=-Wall -g -std=c99
LD=gcc

all: KAM-spiel1 KAM-spiel2

KAM-spiel1: KAM-spiel1.c
	$(CC) $(CFLAGS) KAM-spiel1.c -o KAM-spiel1

KAM-spiel2: KAM-spiel2.o rawio.o
	$(LD) KAM-spiel2.o rawio.o -o KAM-spiel2 -lcurses

KAM-spiel2.o: KAM-spiel2.c
	$(CC) $(CFLAGS) -c KAM-spiel2.c

rawio.o: rawio/rawio.c rawio/rawio.h
	$(CC) $(CFLAGS) -c rawio/rawio.c

clean:
	rm -rf *.o
	rm -rf KAM-spiel1 KAM-spiel2

