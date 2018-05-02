#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


/* Cette petite fonction permet en C de passer d'un caractère
 * à un entier (puisque ce que l'on rentre en nombre lors de 
 * l'exécution sont des grandes chaînes de caratères). 
 */ 
int ctoi(char c){
	return c - '0';
}



/* Retourne vrai si la string passée en paramètre est
 * bien une string de chiffres compris entre 0 et 9
 */
int isString(char * s)
{
	for(int i=0; i<strlen(s); i++){
		if(s[i] < '0' || s[i] > '9'){
			return 0;
		}
	}
	return 1;
}

void naiveMultiply(char * x, char * y, int * result)
{
	/* On vérifie si les deux strings sont bien valides
	 */
	if(!isString(x) || !isString(y)){
		fprintf(stderr, "Rentrez des chaînes de caratères valides.\n");
		exit(0);
	}

	/* On accumule la somme de tous les produits des multiplications
	 * (+1 case au cas où la somme de la dernière retenue soit > 9,
	 * auquel cas on écrira deux chiffres)
	 */
	size_t xSize = strlen(x);
	size_t ySize = strlen(y);

	for(int i = xSize - 1; i >= 0; i--){
		for(int j = ySize - 1; j >= 0; j--){
			result[i+j+1] += ctoi(y[j]) * ctoi(x[i]);
			//printf("result[%d+%d+1] = %d\n", i, j, result[i+j+1]);
		}
	}

	/* On réduit maintenant chaque case du tableau en propageant la retenue.
	 * Exemple : Mettons que l'on ait result[50] = 36, on aura result[50] = 36 % 10 = 6
	 * et la retenue pour la case précédente : result[i-1] += 36 / 10 = 3
	 */
	size_t size = xSize + ySize;

	for(int i = size; i > 0; i--){
		if(result[i] > 9){
			result[i-1] += result[i] / 10;
			result[i] %= 10;
		}
	}
}

void printArray(int * array, size_t sizeArray)
{
	/* On fait la condition à cause du problème suivant :
	 * (100 * 100) = 10000  // 3 chiffres * 3 chiffres = 5 chiffres
	 * (999 * 999) = 998001 // 3 chiffres * 3 chiffres = 6 chiffres
	 * On n'affiche pas le 0 s'il est au début du tableau.
	 */
	if(array[0] != 0)
		printf("%d", array[0]);
	for(size_t i = 1; i < sizeArray; i++){
		printf("%d", array[i]);
	}
	puts("\n");
}

/*
char * toString(int * t, size_t size) {
	char * str = malloc(sizeof(int) * size);
	for(int i=1; i<size; i++){
		str[i] = t[i] + '0';
		printf("%c", str[i]);
	}
	return str;
}
* */


int main(int argc, char ** argv)
{
	// Exécution 1 (en changeant uniquement les valeurs dans les strings ci-dessous

	char * str1 = "123456789123456789123456789123456789123456789123456789";
	char * str2 = "987654321987654321987654321987654321987654321987654321";
	size_t sizeRes = strlen(str1) + strlen(str2);
	int * res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0

	naiveMultiply(str1, str2, res);
	printf("%s * %s = \n", str1, str2);
	printArray(res, sizeRes);


	// Exécution 2 (en passant par le terminal)

	/*
	if(argc > 2 && argc < 4){
		string str1 = argv[1];
		string str2 = argv[2];
		size_t sizeRes = strlen(str1) + strlen(str2);
		int * res = calloc(sizeRes + 1, sizeof(int)); //calloc <=> malloc + initialisation du tableau à 0

		naiveMultiply(str1, str2, res);
		printf("%s * %s = ", str1, str2);
		printArray(res, sizeRes);
	}
	else{
		fprintf(stderr, "Passez uniquement 2 arguments.\n");
	}
	*/

}
