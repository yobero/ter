#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//typedef enum bool{TRUE, FALSE}

typedef struct {
	int *array;
	//size_t used;
	size_t size;
	bool isNegative;
} Array;


Array subArrays(Array a, Array b);
Array sumArrays(Array a, Array b);
int biggest(Array a, Array b);

//Initialise un tableau contenant nbElement elements
Array init(size_t nbElement){
	Array a;
	a.array = calloc(nbElement,sizeof(int));
	a.size = nbElement;
	a.isNegative = false;
	return a;
}
/*
void initArray(Array *a, size_t initialSize) {
	a->array = (int *)malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
	a->isNegative = false;
}
*/


void initArrayToZero(Array *a, size_t initialSize) {
  a->array = (int *)calloc(initialSize, sizeof(int));
  //->used = 0;
	a->size = initialSize;
	a->isNegative = false;
}


void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
	//a->used = 0;
	a->size = 0;
}

void printArray(Array a){
  printf("< ");
	int i;
	if(a.isNegative == true) {
		printf("-");
	}
	for(i=0; i<a.size; i++){
		printf("%d ", a.array[i]);
	}
	puts(">");
}

// Utilisé pour convertir les strings passées en arguments par
// l'utilisateur en Array
Array initArrayInt(char *str){
	Array a;
	int i = 0;
	if(str[0] == '-'){
		a = init(strlen(str)-1);
		a.isNegative = true;
		i = 1;
	}
	else
		a = init(strlen(str));

	int j=0;
	while (i<strlen(str)) {
		a.array[j] = str[i] - '0';
		j++;	i++;
	}
	return a;
}


Array copy(Array a) {
  Array copiedArray = init(a.size);
	copiedArray.isNegative = a.isNegative;
  for(int i=0; i<a.size; i++){
      copiedArray.array[i] = a.array[i];
  }
  return copiedArray;
}

Array ajustArraySize(Array a, Array b) {

  // 1) on garde en mémoire le tableau b dans tmp
  // 2) on remet à 0 le tableau b, avec la taille de a
  // 3) on recopie depuis la fin le tableau tmp dans b
  // 4) on désalloue la mémoire de tmp
  // 5) on retourne b modifié avec du padding à 0 à l'avant du tableau


  if(a.size > b.size) {
    Array tmp = copy(b);
    b.size = a.size;
		initArrayToZero(&b, b.size);
		size_t saveBsize = b.size;

    for(int i=tmp.size - 1; i>=0; i--, b.size--) {
      b.array[b.size-1] = tmp.array[i];
    }
		b.size = saveBsize;
		b.isNegative = tmp.isNegative;
    freeArray(&tmp);
    return b;
  }
  else {
    Array tmp = copy(a);
    a.size = b.size;
		initArrayToZero(&a, a.size);
		size_t saveAsize = a.size;

		for(int i=tmp.size - 1; i>=0; i--, a.size--) {
			a.array[a.size - 1] = tmp.array[i];
		}
		a.size = saveAsize;
		a.isNegative = tmp.isNegative;
		freeArray(&tmp);
		return a;
  }
}


Array sumArrays(Array a, Array b)
{
	Array result;

	//Ajustement de la taille des tableau a et b
	if(a.size > b.size) b = ajustArraySize(a,b);
	if(a.size < b.size) a = ajustArraySize(a,b);
	//a.size==b.size
	
	//a<0 et b>=0
	if(a.isNegative == true  && b.isNegative == false){
		int big = biggest(a,b);
		
		//a>b et donc resultat négatif
		if(big==1){
			Array tmp = copy(a);
			tmp.isNegative=false;
			result = subArrays(tmp,b);
			//resultat négatif
			result.isNegative=true;
			freeArray(&tmp);
			return result;
		}
		//b>a ==> (-a)+b == b-(-a) ==> b+a
		//resultat positif
		//(-a)+b == b-a
		Array tmp = copy(a);
		tmp.isNegative=false;
		result = subArrays(b,tmp);
		freeArray(&tmp);
		return result;
	}
	//a>=0 et b<0
	//a+(-b) == a-b
	if(a.isNegative == false && b.isNegative == true){
		Array tmp = copy(b);
		tmp.isNegative==false;
		return subArrays(a,tmp);
	}
	//a<0 et b<0
	//(-a)+(-b) == -(a+b)
	if(a.isNegative == true && b.isNegative == true){
		Array tmp1 = copy(a);
		tmp1.isNegative=false;
		Array tmp2 = copy(b);
		tmp2.isNegative=false;
		result = sumArrays(tmp1,tmp2);
		result.isNegative=true;
		freeArray(&tmp1);
		freeArray(&tmp2);
		return result;
	}

	result = init(a.size+1);
	
	// CALCUL PAR ACCUMULATION
	for(int i=result.size-1; i>0; i--)
		result.array[i] = (a.array[i-1] + b.array[i-1]);
	
	// PROPAGATION DE LA RETENUE
	for(int i = result.size-1; i>=0; i--) {
		if(result.array[i] > 9) {
			result.array[i-1] += (result.array[i] / 10);
			result.array[i] %= 10;
		}
	}



/*
	// SI LE ARRAY FINAL A UN 0 AU DEBUT, ON LE RETIRE
	if(result.array[0] == 0){
		Array noFirstZero = init(result.size-1);
		for(int i=0; i<result.size-1; i++)
			noFirstZero.array[i] = result.array[i+1];
		//freeArray(&result);
		return noFirstZero;
	}
	else*/
		return result;
}

int biggest(Array a, Array b){
	size_t size = a.size;
	int i = 0;
	while(i<size) {
		if(a.array[i]  > b.array[i]) { return 1;}  // a > b
		if(a.array[i]  < b.array[i]) { return -1;} // a < b
		if(a.array[i] == b.array[i]) { i++; }
	}
	return 0; // a = b

}

int whoIsTheBiggest(Array a, Array b)
{
	/*
	si a > 0 et b > 0
		si b>a : resultat negatif
		sinon 	 resultat positif

	si a < 0 et b > 0
		resultat toujours négatif peu importe la taille

	si a > 0 et b < 0
		retourner addition(a,b)

	si a < 0 et b < 0
		-a - (-b) <=> -(a+b)
		resultat = addition(a,b);
		resultat.isNegative = true;

	*/
	size_t size = a.size; //ou b.size

	if(a.isNegative == false && b.isNegative == false){
		int i = 0;
		while(i<size) {
			if(a.array[i]  > b.array[i]) { return 1;}  // a > b
			if(a.array[i]  < b.array[i]) { return -1;} // a < b
			if(a.array[i] == b.array[i]) { i++; }
		}
		return 0; // a = b
	}

	if(a.isNegative == true && b.isNegative == false){
		return -1; // a < b
	}

	if(a.isNegative == false && b.isNegative == true) {
		return 1; // a > b
	}

	if(a.isNegative == true  && b.isNegative == true) {
		int i = 0;
		while(i<size) {
			if(a.array[i]  > b.array[i]) { return -1;}  // a < b
			if(a.array[i]  < b.array[i]) { return 1;} // a > b
			if(a.array[i] == b.array[i]) { i++; }
		}
		return 0; // a = b
	}

	return 22; // return par défaut
}

/*
Array subArrays(Array a, Array b){

	// Exemple -6 - (-4) <=> -(6+4) = -10
	if(a.isNegative == true  && b.isNegative == true) {
			Array res = sumArrays(a,b);
			res.isNegative = true;
			return res;
	}


	Array result = init(a.size); //ou b.size puisqu'ils ont la même taille

	// VERIFICATION DU PLUS GRAND NOMBRE (SIMPLE COMPARAISON EN O(taille du plus grand array))
	char biggestNumber;

	// PARCOURS DES 2 ARRAYS POUR VOIR LEQUEL DES 2 EST LE PLUS GRAND
	int i = 0;
	while(i<a.size) {
		if(a.array[i]  > b.array[i]) { biggestNumber = 'a'; break;}
		if(a.array[i]  < b.array[i]) { biggestNumber = 'b'; break;}
		if(a.array[i] == b.array[i]) { i++; }
	}
	if(i == a.size) { biggestNumber = '='; }

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
			freeArray(&result);
			Array result = init(1);
			result.isNegative = false;
			result.array[0] = 0;
			//printf("1er element=%d\n", result.array[5]);
			break;
	}
	return result;
}
*/

Array subArrays(Array a, Array b) { // a - b

	Array result;

	// AJUSTEMENT DE LA TAILLE DES TABLEAUX
	if(a.size > b.size) b = ajustArraySize(a,b);
	if(a.size < b.size) a = ajustArraySize(a,b);

	result = init(a.size); // ou b.size

	int big = biggest(a,b); // si a > b : 1   si a < b : -1 sinon 0
	//a-(-b) == a+b
	if(a.isNegative==false && b.isNegative==true){
		Array tmp = copy(b);
		tmp.isNegative=false;
		result=sumArrays(a,tmp);
		freeArray(&tmp);
		return result;
	}
	
	//(-a)-b == -(a+b)
	if(a.isNegative==true && b.isNegative==false){
		Array tmp = copy(a);
		tmp.isNegative=false;
		result=sumArrays(tmp,b);
		freeArray(&tmp);
		result.isNegative=true;
		return result;
	}
	
	//(-a)-(-b) == (-a)+b
	if(a.isNegative==true && b.isNegative==true){
		Array tmp=copy(b);
		tmp.isNegative=false;
		result=sumArrays(a,tmp);
		freeArray(&tmp);
		return result;
	}
	
	switch(big) {
		case 1:
			// a > b donc soustraction normale
			for(int i=a.size-1; i>=0; i--) {
					if(a.array[i] < b.array[i]) {
						printf("a<b\n");
						a.array[i] += 10;
						b.array[i-1] += 1;
					}
					result.array[i] = a.array[i] - b.array[i];
			}
			result.isNegative = false;
			break;

		case -1:
			// a < b
			for(int i=b.size-1; i>=0; i--) {
					if(a.array[i] > b.array[i]) {
						b.array[i] += 10;
						a.array[i-1] += 1;
					}
					result.array[i] = b.array[i] - a.array[i];
				}
				result.isNegative = true;
				break;
		case 0:
			break;
	}

	return result;
}

/* Renvoie la sous-string de s commençant à l'indice pos
 * et finissant (length) caractères plus loin :
 * substr("bonjour", 2, 3) >> "njo"
 */
Array substr(Array t, size_t depart, size_t arrivee)
{
	Array tab = init(arrivee-depart);
	int j=0;
	for (int i=depart;i<arrivee;i++){
		tab.array[j] = t.array[i];
		j++;
	}
	tab.isNegative=t.isNegative;
  return tab;
}
//rajouter adroite 0 à droite
Array aggrandissement(Array a,size_t adroite){
	Array result = init(a.size+adroite);
	//simple copie du tableau a
	for(int i=0;i<a.size;i++){
		result.array[i]=a.array[i];
	}
	//result.size >= a.size ==> result.size = a.size + adroite
	return result;
}

Array reduction(Array a){
	if(a.size>1){
		Array result;
		int compteur=0;
		for(int i=0;i<a.size;i++){
			if(a.array[i]!=0) break;
			else compteur++;
		}
		result=init(a.size-compteur);
		int j=0;
		for(int i=compteur;i<a.size;i++){
			result.array[j]=a.array[i];
			j++;
		}
		return result;
	}
	return a;
}

Array taillePaire(Array a){
	//taille impaire
	if(a.size%2==1){
		Array result = init(a.size+1);
		for(int i=1;i<a.size+1;i++){
			result.array[i]=a.array[i-1];
		}
		return result;
	}
	return a;
}

/*
Array karatsuba(Array x, Array y)
{
    size_t size = x.size;//, y.size);


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

    Array xLeft  = substr(x, 0, firstHalf); printf("xleft : %s\n", xLeft);
    Array xRight = substr(x, firstHalf, secondHalf);
    Array yLeft  = substr(y, 0, firstHalf);
    Array yRight = substr(y, firstHalf, secondHalf);

		Array p0 = karatsuba(xLeft,yLeft);
    Array p1 = karatsuba(xRight,yRight);
    Array p2 = karatsuba(sumArrays(xLeft, xRight),sumArrays(yLeft,yRight));
    Array p3 = subArrays(p2,sumArrays(p0,p1));

		return sumArrays(sumArrays(p0,p1),p3);
}
*/

/*
void strcat_c(char *str, char c){
	for(;*str;str++);
	*str++ = c;
	*str++ = 0;
}

char * randomNumber(size_t size){
	char * nb = malloc(sizeof(int)*size);
	nb[0] = (rand() % 10) + 1;
	for(int i=1; i<strlen(nb)-1; i++)
	 	strcat_c(nb, rand()%10);
	return nb;
}
*/

Array karatsuba(Array a,Array b){
	//Cas ou la taille de a et b = 1
	Array result;
	if(a.size==1 && b.size==1){
		//a.size+b.size
		result = init(2);
		int val = a.array[0]*b.array[0];
		if(val>9){
			result.array[1]=val%10;
			result.array[0]=val/10;
		}
		else{
			result.array[1]=val;
		}
		// result = copy(a);
		return result;
	}
	//dans le cas contraire
	else{
		// AJUSTEMENT DE LA TAILLE DES TABLEAUX
		if(a.size > b.size) b = ajustArraySize(a,b);
		if(a.size < b.size) a = ajustArraySize(a,b);
		//a.size==b.size
		
		//fonction qui verifie si la taille est paire
		//Si ce n'est pas le cas, elle augmente la taille de 1
		Array ap = taillePaire(a);
		Array bp = taillePaire(b);
		
		Array A = substr(a,0,a.size/2);
		Array B = substr(a,a.size/2, a.size);
		Array C = substr(b,0,b.size/2);
		Array D = substr(b,b.size/2,b.size);
		
		freeArray(&ap); freeArray(&bp);
		
		//printArray(A); printArray(B); printArray(C); printArray(D);printf("\n");
		
		Array AC = karatsuba(A,C);
		//printf("AC : "); printArray(AC);
		Array BD = karatsuba(B,D);
		//printf("BD : "); printArray(BD);
		Array y = karatsuba(subArrays(A,B),subArrays(C,D));
		Array Z = subArrays(sumArrays(AC,BD),y);
		//printf("Z : "); printArray(Z);
		
		//Liberation de la mémoire
		freeArray(&A);
		freeArray(&B);
		freeArray(&C);
		freeArray(&D);
		
		Array z = aggrandissement(Z,a.size/2);
		freeArray(&Z);
		Array r1 = sumArrays(BD,z);
		freeArray(&BD);
		freeArray(&z);
		
		Array ac = aggrandissement(AC,a.size);
		freeArray(&AC);
		Array r2 = sumArrays(r1,ac);
		freeArray(&r1);
		freeArray(&ac);
		
		result = reduction(r2);
		freeArray(&r2);
		
		return result;
		
	}
}

int main(int argc, char ** argv)
{
	char * s1 = "-300";
	char * s2 = "9";
	//char * s3 = randomNumber(5); printf(":: %s\n", s3);

	Array x = initArrayInt(argv[1]); printArray(x);
	Array y = initArrayInt(argv[2]); printArray(y);
	Array z;

	//z = subArrays(x,y); printArray(z);

	//printf("%d et %d \n", x.isNegative, y.isNegative );


	z = karatsuba(x,y); printArray(z);
}
