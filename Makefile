CC=g++
CFLAGS=-g 

all: avgbot

mm-client.o: mm-client.cpp mm-client.h
	${CC} ${CFLAGS} -c mm-client.cpp -o mm-client.o

avgbot.o: avgbot.cpp mm-client.h
	${CC} ${CFLAGS} -c avgbot.cpp -o avgbot.o
avgbot: mm-client.o avgbot.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f *.o

fresh: clean all

