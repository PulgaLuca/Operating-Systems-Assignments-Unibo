CFLAGS=-ansi -Wpedantic -Wall
LIBRARIES=-lpthread

all: piattello.exe

piattello.exe: piattello.o DBGpthread.o
	gcc -o piattello.exe piattello.o DBGpthread.o ${LIBRARIES}

piattello.o: piattello.c ./DBGpthread.h ./printerror.h
	gcc -c ${CFLAGS} piattello.c -I./

DBGpthread.o:	./DBGpthread.c ./printerror.h
	gcc -c ${CFLAGS} DBGpthread.c -I./

.PHONY: clean

clean:
