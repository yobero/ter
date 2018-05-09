#include <time.h>

#include "karatsuba.c"
#include "naive.c"

int main(int argc, char ** argv)
{
	clock_t debut;
	if(argc>2){
		switch(argv[3][0]-48){
			case 0 :{
			char * s1 = argv[1];
			char * s2 = argv[2];
		
			size_t sizeRes = strlen(s1) + strlen(s2);
			int * res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0
			
			debut = clock();
			naiveMultiply(s1, s2, res);
			printf("%s * %s = \n", s1, s2);
			printf ("Temps algo naive : %f\n", (double)(clock () - debut) / CLOCKS_PER_SEC);
			printNaive(res, sizeRes);

			debut=clock();
			Array x = initArrayInt(s1); //printArray(x);
			Array y = initArrayInt(s2); //printArray(y);
	
			Array z = karatsuba(x,y);
			printf ("Temps kara : %f\n", (double)(clock () - debut) / CLOCKS_PER_SEC);
			printArray(z);
			break; }
			case 1 :{
			char * s1 = argv[1];
			char * s2 = argv[2];
		
			size_t sizeRes = strlen(s1) + strlen(s2);
			int * res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0

			naiveMultiply(s1, s2, res);
			printf("%s * %s = \n", s1, s2);
			printNaive(res, sizeRes);
			break;}
			case 2:{
			char * s1 = argv[1];
			char * s2 = argv[2];

			Array x = initArrayInt(s1); //printArray(x);
			Array y = initArrayInt(s2); //printArray(y);
	
			Array z = karatsuba(x,y); printArray(z);
			break;}
				
		}
	
}else{
		fprintf(stderr, "Pas assez d'argument !!!\n\n");
	}
}