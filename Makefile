karatsuba.o : karatsuba.c
	gcc -Wall -c karatsuba.c
	
main.o : main.c karatsuba.o
	gcc -Wall -c main.c
	
compile2 : main.o
	gcc -Wall karatsuba.o main.o -o multi
	
compile : main.c karatsuba.c
	gcc -Wall main.c -o multi -lm
	
run : compile
	./multi 12 12 0
	
naive : compile
	./multi 12 12 1
	
kara: compile
	./multi 12 12 2
	
clean :
	rm ./multi
	rm *.o