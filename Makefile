CC=gcc
CFLAGS=-g

all: avgbot

mm-client.o: mm-client.c mm-client.h

avgbot.o: avgbot.cpp mm-client.h
avgbot: mm-client.o avgbot.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f *.o

fresh: clean all

