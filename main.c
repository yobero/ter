#include "karatsuba.c"
#include "naive.c"

int main(int argc, char ** argv)
{
	if(argc>2){
		char * s1 = argv[1];
		char * s2 = argv[2];
		
		size_t sizeRes = strlen(s1) + strlen(s2);
		int * res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0

		naiveMultiply(s1, s2, res);
		printf("%s * %s = \n", s1, s2);
		printNaive(res, sizeRes);

		Array x = initArrayInt(s1); //printArray(x);
		Array y = initArrayInt(s2); //printArray(y);
	

		Array z = karatsuba(x,y); printArray(z);
	
}else{
		fprintf(stderr, "Pas assez d'argument !!!\n\n");
	}
}