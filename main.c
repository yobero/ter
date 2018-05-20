#include <time.h>
#include <gmp.h>

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
			case 3 :{
				//i montre le nombre de chiffre
				int val;
				int* res;
				Array x;
				Array y;
				Array z;
				for(int i=1;i<10010;i+=1000){
				//for(int i=1;i<35;i+=1){
					char* s1 = calloc(i,sizeof(int));
					char* s2 = calloc(i,sizeof(int));
					//creation aleatoire d'un nombre de i chiffre
					for(int k=0;k<i;k++){
						val=rand()%10;
						s1[k]=val+'0';
						val=rand()%10;
						s2[k]=val+'0';
					}
					//algo naif
					size_t sizeRes = strlen(s1) + strlen(s2);
					res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0
					debut = clock();
					naiveMultiply(s1, s2, res);
					double naive = ((double)clock()-debut)/CLOCKS_PER_SEC;
					free(res);

					x = initArrayInt(s1);
					y = initArrayInt(s2);
					free(s1);
					free(s2);
					debut = clock();
					z = karatsuba(x,y);
					double karat = ((double)clock()-debut)/CLOCKS_PER_SEC;

					printf("%d %f %f\n",i,naive,karat);
	
					freeArray(&x);
					freeArray(&y);
					freeArray(&z);
					
					s1=NULL;
					s2=NULL;
				}
				break;
			}
				
		}
	
}else{
		fprintf(stderr, "Pas assez d'argument !!!\n\n");
	}
}
