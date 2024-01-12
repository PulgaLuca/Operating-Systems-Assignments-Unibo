CFLAGS=-ansi -Wpedantic -Wall
LIBRARIES=-lpthread

all: formicai.exe

formicai.exe: formicai.o DBGpthread.o
	gcc -o formicai.exe formicai.o DBGpthread.o ${LIBRARIES}

formicai.o:	formicai.c ./DBGpthread.h ./printerror.h
	gcc -c ${CFLAGS} formicai.c

DBGpthread.o: ./DBGpthread.c ./printerror.h
	gcc -c ${CFLAGS} ./DBGpthread.c

.PHONY: clean

clean:	
	rm -f formicai.exe formicai.o DBGpthread.o
