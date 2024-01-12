CFLAGS=-ansi -Wpedantic -Wall
LIBRARIES=-lpthread

all: piantarepalisemplice.exe

piantarepalisemplice.exe: piantarepalisemplice.o DBGpthread.o
	gcc -o piantarepalisemplice.exe piantarepalisemplice.o DBGpthread.o ${LIBRARIES}

piantarepalisemplice.o: piantarepalisemplice.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} piantarepalisemplice.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c ${CFLAGS} DBGpthread.c

.PHONY: clean

clean: 
	rm -f piantarepalisemplice.o piantarepalisemplice.exe DBGpthread.o
