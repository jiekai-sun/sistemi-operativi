CFLAGS=-ansi -Wall -Wpedantic -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: es0000_strutture.exe

es0000_strutture.exe: es0000_strutture.o
	gcc ${LFLAGS} -o es0000_strutture.exe es0000_strutture.o ${LIBRARIES}

es0000_strutture.o: es0000_strutture.c
	gcc ${CFLAGS} -c es0000_strutture.c

.PHONY: clean

clean:
	-rm -f  es0000_strutture.exe es0000_strutture.o