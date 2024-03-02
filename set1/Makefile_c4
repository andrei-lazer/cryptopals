CC = gcc

c4: c4.o helpers.o
	${CC} c4.o helpers.o -lm -o c4 

helpers.o: helpers.c helpers.h
	${CC} -c helpers.c

c4.o: c4.c 
	${CC} -c c4.c


clean:
	rm *.o c4
