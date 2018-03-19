#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
	int *array;
	size_t used;
	size_t size;
	bool isNegative;
} Array;

void initArray(Array *a, size_t initialSize) {
	a->array = (int *)malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
	a->isNegative = false;
}

void initArrayToZero(Array *a, size_t initialSize) {
  a->array = (int *)calloc(initialSize, sizeof(int));
  a->used = 0;
	a->size = initialSize;
	a->isNegative = false;
}

void insertArray(Array *a, int element) {
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (int *)realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used++] = element;
}

void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

void printArray(Array a){
  printf("< ");
	int i;
	if(a.isNegative == 1) {
		printf("-");
	}
	for(i=0; i<a.size; i++){
		printf("%d ", a.array[i]);
	}
	puts(">");
}

// Utilisé pour convertir les strings passées en arguments par
// l'utilisateur en Array
void initArrayInt(Array *a, char *str){
	size_t strSize = strlen(str);
	initArray(a, strSize);
	int i;
	for(i=0; i<strSize; i++){
		insertArray(a, str[i] - '0');
	}
}


Array copy(Array a) {
  Array copiedArray;
  initArray(&copiedArray, a.size);
	copiedArray.isNegative = a.isNegative;
  for(int i=0; i<a.size; i++){
      copiedArray.array[i] = a.array[i];
  }
  return copiedArray;
}

/* Exemple :
* string a = "123456";
* string b =    "789";
* ajustStringLength(a,b);
* On aura b = "000789";
*/
Array ajustArraySize(Array a, Array b) {

  // 1) on garde en mémoire le tableau b dans tmp
  // 2) on remet à 0 le tableau b, avec la taille de a
  // 3) on recopie depuis la fin le tableau tmp dans b
  // 4) on désalloue la mémoire de tmp
  // 5) on retourne b modifié avec du padding à 0 à l'avant du tableau

  if(a.size > b.size) {
    Array tmp;
    initArray(&tmp, a.size);
    tmp = copy(b);
    b.size = a.size;
		initArrayToZero(&b, b.size);
		size_t saveBsize = b.size;

    for(int i=tmp.size - 1; i>=0; i--, b.size--) {
      b.array[b.size-1] = tmp.array[i];
    }
		b.size = saveBsize;
    freeArray(&tmp);
    return b;
  }
  else {
    Array tmp;
    initArray(&tmp, b.size);
    tmp = copy(a);
    a.size = b.size;
		initArrayToZero(&a, a.size);
		size_t saveAsize = a.size;

		for(int i=tmp.size - 1; i>=0; i--, a.size--) {
			a.array[a.size - 1] = tmp.array[i];
		}
		a.size = saveAsize;
		freeArray(&tmp);
		return a;
  }
}


// SI BUG CHANGER PAR DES PARAMETRES SANS POINTEURS (JUSTE PAR COPIES)
Array sumArrays(Array a, Array b)
{
	// a : 456
	// b :  44
	// r : 580

	// AJUSTEMENT DE LA TAILLE DES TABLEAUX
	if(a.size > b.size) b = ajustArraySize(a,b);
	if(a.size < b.size) a = ajustArraySize(a,b);

  Array result;
	initArray(&result, max(a.size, b.size));

	// CALCUL PAR ACCUMULATION
	size_t initialSizeResult = result.size; // Va permettre de redonner à size sa valeur initiale, à mesure que k va s'incrémenter dans la boucle for
	size_t initialSizeAandB = a.size; //les deux tailles sont égales

	for(int i=result.size-1; i>=0; i--){
		result.array[i] = (a.array[a.size - 1] + b.array[b.size - 1]);
		a.size--; b.size--;
	}
	result.size = initialSizeResult;
	a.size = b.size = initialSizeAandB;

	// PROPAGATION DE LA RETENUE
	for(int i = result.size-1; i>0; i--) {
		if(result.array[i] > 9) {
			result.array[i-1] += (result.array[i] / 10);
			result.array[i] %= 10;
		}
	}

	// POUR 65 + 40 ON A 10 5, ON CHANGE ALORS EN 1 0 5
	if(result.array[0] > 9){
		Array resizedArray;
		initArray(&resizedArray, result.size+1); //si on a 15 on veut 1 et 5 dans deux cases différentes
		resizedArray.array[0] = result.array[0] / 10;
		resizedArray.array[1] = result.array[0] % 10;
		for(int i=2; i<resizedArray.size-1; i++){
			resizedArray.array[i] = result.array[i-1];
		}
		freeArray(&result);
		return resizedArray;
	}
	else{
		return result;
	}

/*
	// IL SE PEUT QUE LE ARRAY FINAL AIT UN 0 AU DEBUT : ON LE RETIRE
	if(result.array[0] == 0){
		Array noFirstZero;
		initArray(&noFirstZero, result.size);
		for(int i=0; i<result.size-1; i++){
			noFirstZero.array[i] = result.array[i+1];
		}
		freeArray(&result);
		return noFirstZero;
	}
	else
		return result;
		*/
}

int whoIsTheBiggest(Array a, Array b)
{
	if(a.size > b.size) b = ajustArraySize(a,b);
	if(a.size < b.size) a = ajustArraySize(a,b);
	printf("in big function, aSize = %d\n", a.size);
	printf("in big function, bSize = %d\n", b.size);

	size_t size = max(a.size, b.size);
	int i = 0;

	while(i<size) {
		if(a.array[i]  > b.array[i]) { return 1;}
		if(a.array[i]  < b.array[i]) { return 0;}
		if(a.array[i] == b.array[i]) { i++; }
	}
	return (i == size) ? 61 : 0; //61 est le signe '=' en ASCII
}

Array subArrays(Array a, Array b)
{
	Array result;
	initArray(&result, max(a.size, b.size));

	/*
	int big = whoIsTheBiggest(a,b);
	if(big == 1) // a>b : a-b
	if(big == 0) // a<b : b-a puis negatif


	 * déterminons lequel des arrays est le plus grand en valeur :
	 * 35 - 9 =  26
	 * 9 - 35 = -26

	 si(a>b){
			soustraction normale
		}
		si(a<b){
			- (soustraction normale)
			on rajoute le signe - >> result.isNegative = true;
		}
		*/

		// AJUSTEMENT DE LA TAILLE DES TABLEAUX
		if(a.size > b.size) b = ajustArraySize(a,b);
		if(a.size < b.size) a = ajustArraySize(a,b);

		size_t size = max(a.size, b.size);
		int i = 0;

		// VERIFICATION DU PLUS GRAND NOMBRE (SIMPLE COMPARAISON EN O(taille du plus grand array))
		char biggestNumber;

		// PARCOURS DES 2 ARRAYS POUR VOIR LEQUEL DES 2 EST LE PLUS GRAND
		while(i<size) {
			if(a.array[i]  > b.array[i]) { biggestNumber = 'a'; break;}
			if(a.array[i]  < b.array[i]) { biggestNumber = 'b'; break;}
			if(a.array[i] == b.array[i]) { i++; }
		}
		if(i == size) { biggestNumber = '='; }

		// SOUSTRACTION
		switch(biggestNumber){
			case 'a' :
				puts("a + grand");
				result.isNegative = false;
				for(int i=a.size-1; i>=0; i--) {
					if(a.array[i] < b.array[i]) {
						a.array[i] += 10;
						b.array[i-1] += 1;
					}
					result.array[i] = a.array[i] - b.array[i];
				}
				break;

			case 'b' :
				puts("b + grand");
				result.isNegative = true;
				for(int i=b.size-1; i>=0; i--) {
					if(a.array[i] > b.array[i]) {
						b.array[i] += 10;
						a.array[i-1] += 1;
					}
					result.array[i] = b.array[i] - a.array[i];
				}
				break;

			case '=' :
				puts("a = b");
				result.isNegative = false;
				result.array[0] = 0;
				break;
		}

		//AJUSTER TAILLE RESULTAT : POUR 123 - 124 = -001 >> -1
		//ON SUPPRIME LES 0 DU DÉBUT

		i = 0;
		int newSize = 0;
		while(result.array[i] == 0){
			i++;
			newSize++;
		}
		printf("newSize = %d\n", newSize);
		int indiceR = 0;
		Array r;
		initArray(&r,newSize);

		i = 0;
		while(i < result.size -1){
			if(result.array[i] == 0){
				i++;
			}
			else{
				r.array[indiceR] = result.array[i];
				indiceR++;
			}
		}

		return result;
}

/* Renvoie la sous-string de s commençant à l'indice pos
 * et finissant (length) caractères plus loin :
 * substr("bonjour", 2, 3) >> "njo"
 */
Array substr(Array s, size_t pos, size_t length)
{
	if(pos == s.size) return s;
	if(pos >  length) exit(0);
	if(length+pos > s.size) exit(0);

	Array sub;
	initArrayToZero(&sub, length);
	for(size_t i=0; i<length; i++, pos++){
		sub.array[i] = s.array[pos];
	}
	return sub;
}

/********* KARATSUBA ***********/

/*
Array karatsuba(Array x, Array y)
{
    size_t size = max(x.size, y.size);

		if(x.size > y.size) y = ajustArraySize(x,y);
		if(x.size < y.size) x = ajustArraySize(x,y);

    // Cas de base
    if(size == 0){
		Array resultZero;
		initArrayToZero(&resultZero, 1); //taille de 1 avec uniquement 0 dans le tableau
		return resultZero;
	}
	if(size == 1){
		int mul = (x.array[0]-'0') * (y.array[0]-'0'); //ex : 23 (n'excède pas 9*9 = 81
		Array multi;
		initArrayToZero(&multi, size);
		multi.array[0] = mul / 10; // = 2
		multi.array[1] = mul % 10; // = 3
		return multi;
	}

    size_t firstHalf = size/2;   // First half of string, floor(n/2)
    size_t secondHalf = (size-firstHalf); // Second half of string, ceil(n/2)

    Array xLeft  = substr(x, 0, firstHalf);
    Array xRight = substr(x, firstHalf, secondHalf);
    Array yLeft  = substr(y, 0, firstHalf);
    Array yRight = substr(y, firstHalf, secondHalf);

		Array p0 = karatsuba(xLeft,yLeft);
    Array p1 = karatsuba(xRight,yRight);
    Array p2 = karatsuba(sumArrays(xLeft, xRight),sumArrays(yLeft,yRight));
    Array p3 = subArrays(p2,sumArrays(p0,p1));


		Array result = sumArrays(sumArrays(p0,p1),p3);
    // Combinaison des 3 produits
    //return P1*(1<<(2*secondHalf)) + (P3 - P1 - P2)*(1<<secondHalf) + P2; //_______SEGMENTATION FAULT
	return result;
}
*/


int main(int argc, char ** argv)
{
  char str1[50] = "-1";
  char str2[50] = "-9";

  Array a, b;
  initArrayInt(&a, str1);
  initArrayInt(&b, str2);

  printf("a : "); printArray(a);
  printf("b : "); printArray(b);

	Array x = sumArrays(a,b);
	printf("x : "); printArray(x);

	/*
	Array su = substr(a, 4, 0);
	printArray(su);
	*/
}
