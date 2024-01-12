CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: guadoZambesi.exe

guadoZambesi.exe: guadoZambesi.o DBGpthread.o
	gcc -o guadoZambesi.exe guadoZambesi.o DBGpthread.o ${LIBRARIES}

guadoZambesi.o: guadoZambesi.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} guadoZambesi.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY: clean

clean:
	rm -f guadoZambesi.exe guadoZambesi.o DBGpthread.o
