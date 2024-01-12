CFLAGS=-ansi -Wpedantic -Wall
LIBRARIES=-lpthread

all: soccorsi.exe

soccorsi.exe: soccorsi.o DBGpthread.o
	gcc -o soccorsi.exe soccorsi.o DBGpthread.o ${LIBRARIES}

soccorsi.o: soccorsi.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} soccorsi.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY: clean

clean:
	rm -f soccorsi.exe soccorsi.o DBGpthread.o
