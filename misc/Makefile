# Makefile per joinable e detached

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: 	joinable.exe detached.exe cancel.exe

joinable.exe: joinable.o
	gcc ${LFLAGS} -o joinable.exe joinable.o ${LIBRARIES}

joinable.o: joinable.c
	gcc ${CFLAGS} -c joinable.c

detached.exe: detached.o
	gcc ${LFLAGS} -o detached.exe detached.o ${LIBRARIES}

detached.o: detached.c
	gcc ${CFLAGS} -c detached.c

cancel.exe: cancel.o
	gcc ${LFLAGS} -o cancel.exe cancel.o ${LIBRARIES}

cancel.o: cancel.c
	gcc ${CFLAGS} -c cancel.c


.PHONY:	clean

clean:
	rm -f joinable.o joinable.exe detached.o detached.exe cancel.o cancel.exe 

