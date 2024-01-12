CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

LIBRARIES=-lpthread

all: 	 consegna.exe

consegna.exe:  consegna.o DBGpthread.o 
	gcc -o consegna.exe consegna.o DBGpthread.o ${LIBRARIES}

consegna.o: consegna.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS} consegna.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c 


.PHONY:	clean

clean:
	-rm -f consegna.o DBGpthread.o consegna.exe


