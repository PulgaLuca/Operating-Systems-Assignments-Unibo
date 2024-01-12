CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: uno.exe

uno.exe: uno.o DBGpthread.o
	gcc -o uno.exe uno.o DBGpthread.o ${LIBRARIES}

uno.o: uno.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} uno.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY: clean

clean: 
	rm -f uno.exe uno.o DBGpthread.o
