karatsuba.o : karatsuba.c
	gcc -Wall -c karatsuba.c
	
main.o : main.c karatsuba.o
	gcc -Wall -c main.c
	
compile2 : main.o
	gcc -Wall karatsuba.o main.o -o multi
	
compile : main.c karatsuba.c
	gcc -Wall main.c -o multi -lm
	
run : compile
	./multi 12345678987654321123456789098765433 12345678987654321123456789098765433 0
	
naive : compile
	./multi 12 12 1
	
kara: compile
	./multi 692 217 2
	
plot: compile
	./multi 0 0 3 > result
	Rscript script.R
	eog plot.jpg
	
clean :
	rm ./multi
	rm *.o
