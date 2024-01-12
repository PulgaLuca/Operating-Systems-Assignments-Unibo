CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE 

LIBRARIES=-lpthread

all: 	negoziopazzo.exe

negoziopazzo.exe: negoziopazzo.o DBGpthread.o
	gcc -o negoziopazzo.exe negoziopazzo.o DBGpthread.o ${LIBRARIES}

negoziopazzo.o: negoziopazzo.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} negoziopazzo.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	rm -f negoziopazzo.o DBGpthread.o negoziopazzo.exe


