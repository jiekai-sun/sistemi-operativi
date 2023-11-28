CFLAGS=-ansi -Wall -Wpedantic -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: es0_premortem.exe

es0_premortem.exe: es0_premortem.o
	gcc ${LFLAGS} -o es0_premortem.exe es0_premortem.o ${LIBRARIES}

es0_premortem.o: es0_premortem.c
	gcc ${CFLAGS} -c es0_premortem.c

.PHONY: clean

clean:
	-rm -f es0_premortem.o es0_premortem.exe