CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE 

LIBRARIES=-lpthread

all: 	tennis.exe

tennis.exe: tennis.o DBGpthread.o
	gcc -o tennis.exe tennis.o DBGpthread.o ${LIBRARIES}

tennis.o: tennis.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} tennis.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f tennis.o DBGpthread.o tennis.exe


