all: naiveMultiply

run: all
	./naiveMultiply

naiveMultiply.o: naiveMultiply.c naiveMultiply.h
	gcc -Wall -c naiveMultiply.c

naiveMultiply: naiveMultiply.o
	gcc -Wall naiveMultiply.o -o naiveMultiply -lm

clean:
	rm *.o
	rm sed
