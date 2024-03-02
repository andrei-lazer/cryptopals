CC = gcc

c6: c6.o helpers.o
	${CC} c6.o helpers.o -lm -o c6 

helpers.o: helpers.c helpers.h
	${CC} -c helpers.c

c6.o: c6.c 
	${CC} -c c6.c


clean:
	rm *.o c6
