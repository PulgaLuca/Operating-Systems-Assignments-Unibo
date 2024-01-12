CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE

LIBRARIES=-lpthread

all: 	 striscepedonali.exe

striscepedonali.exe:  striscepedonali.o DBGpthread.o 
	gcc -o striscepedonali.exe striscepedonali.o DBGpthread.o ${LIBRARIES}

striscepedonali.o: striscepedonali.c DBGpthread.h printerror.h
	gcc -c ${CFLAGS}  striscepedonali.c 

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c  


.PHONY:	clean

clean:
	-rm -f striscepedonali.o DBGpthread.o striscepedonali.exe


