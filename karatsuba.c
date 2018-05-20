#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int *array;
	size_t size;
	bool isNegative;
} Array;

Array init(size_t nbElement){
	Array a;
	a.array = calloc(nbElement,sizeof(int));
	if(a.array==NULL){
		printf("Erreur lors de l'initialisation dans init()\n");
		exit(1);
	}
	a.size = nbElement;
	a.isNegative = false;
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

Array reduction(Array a){
	if(a.size>1){
		Array result;
		//compteur contient le nombre de 0 dans le tableau
		int compteur=0;
		for(int i=0;i<a.size;i++){
			if(a.array[i]!=0) break;
			else compteur++;
		}
		if(compteur>=a.size){ Array zero = init(1); return zero; }
		//printf("A reduction\n");
		result=init(a.size-compteur);
		//printf("B reduction\n");
		int j=0;
		for(int i=compteur;i<a.size;i++){
			result.array[j]=a.array[i];
			j++;
		}
		result.isNegative=a.isNegative;
		return result;
	}
	return copy(a);
}

Array opposer(Array a){
	Array op = reduction(a);
	op.isNegative = (a.isNegative==true)?(false):(true);
	return op;
}

void initArrayToZero(Array *a, size_t initialSize) {
  	a->array = (int *)calloc(initialSize, sizeof(int));
	a->size = initialSize;
	a->isNegative = false;
}


void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
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
	}else{
		a = init(strlen(str));
	}

	int j=0;
	while (i<strlen(str)) {
		a.array[j] = str[i] - '0';
		j++;	
		i++;
	}
	return a;
}

Array ajustArraySize(Array a, Array b) {

  // 1) on garde en mémoire le tableau a dans tmp
  // 2) on remet à 0 le tableau a, avec la taille de b
  // 3) on recopie depuis la fin le tableau tmp dans a
  // 4) on désalloue la mémoire de tmp
  // 5) on retourne a modifié avec du padding à 0 à l'avant du tableau
	//printf("I a1.size = %d et b1.size = %d\n",a1.size,b1.size);
	/*Array a = reduction(a1);
	Array b = reduction(b1);
	//printf("I a.size = %d et b.size = %d\n",a.size,b.size);

  if(a.size < b.size) {
    Array tmp = copy(a);
	  freeArray(&a);
	  	initArrayToZero(&a, b.size);
   		a.size = b.size;
		size_t saveBsize = b.size;

    for(int i=tmp.size - 1; i>=0; i--, b.size--) {
      a.array[b.size-1] = tmp.array[i];
    }
		b.size = saveBsize;
		a.isNegative = tmp.isNegative;
   		freeArray(&tmp);
    return a;
  }else {
	return copy(a);
  }*/
	if(a.size<b.size){
		int ecart = b.size-a.size;
		Array result = init(b.size);
		for(int i=0;i<a.size;i++){
			result.array[i+ecart]=a.array[i];
		}
		result.isNegative=a.isNegative;
		return result;
	}
	else return copy(a);
}

Array aggrandissement(Array a,size_t adroite){
	//printf("A reduction\n");
	//printf("taille de a : %d valeur de droite : %d\n",a.size,adroite);
	Array result = init(a.size+adroite);
	//printf("B reduction\n");
	//simple copie du tableau a
	for(int i=0;i<a.size;i++){
		result.array[i]=a.array[i];
	}
	//result.size >= a.size ==> result.size = a.size + adroite
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

Array sumArrays(Array a, Array b){
	Array a1 = ajustArraySize(a,b);
	Array b1 = ajustArraySize(b,a);
	//printf("taille de a1 : %d taille de b1 = %d\n",a1.size,b1.size);
	Array result = init(a1.size+1);

	if (a.isNegative==false && b.isNegative==false)
	{
		for (int i = 0; i < a1.size; ++i)
		{
			result.array[i+1] = a1.array[i]+b1.array[i];
		}
	}

	if (a.isNegative==true && b.isNegative==false)
	{
		if (biggest(a1,b1)==1)
		{
			for(int i=a.size-1; i>=0; i--) {
					if(a1.array[i] < b1.array[i]) {
						a1.array[i] += 10;
						b1.array[i-1] += 1;
					}
					result.array[i+1] = a1.array[i] - b1.array[i];
			}
			result.isNegative = true;
		}

		if (biggest(a1,b1)==-1)
		{
			for(int i=a1.size-1; i>=0; i--) {
					if(b1.array[i] < a1.array[i]) {
						b1.array[i] += 10;
						a1.array[i-1] += 1;
					}
					result.array[i+1] = b1.array[i] - a1.array[i];
			}
			result.isNegative = false;
		}
		
	}

	if (a.isNegative==false && b.isNegative==true){
		return sumArrays(b,a);
	}

	if (a.isNegative==true && b.isNegative==true){
		Array opA = opposer(a);
		Array opB = opposer(b);
		Array sum = sumArrays(opA,opB);
		
		Array opSum = opposer(sum);
		
		freeArray(&opA);
		freeArray(&opB);
		freeArray(&sum);
		
		return opSum;
	}


	
	for(int i = result.size-1; i>0; i--) {
		if(result.array[i] > 9) {
			result.array[i-1] += (result.array[i] / 10);
			result.array[i] %= 10;
		}
	}
	result = reduction(result);
	return result;
}

Array subArrays(Array a, Array b){
	return sumArrays(a,opposer(b));
}

//Prend la partie gauche du tableau t
Array substrl(Array t)
{
	Array tab = init(t.size/2);
	int j=0;
	for (int i=0;i<t.size/2;i++){
		tab.array[j] = t.array[i];
		j++;
	}
	tab.isNegative=t.isNegative;
  return tab;
}

//Prend la partie droite du tableau t
Array substrr(Array t)
{
	int taille = t.size-t.size/2;
	//Array tab = init(t.size-substrl(t).size);
	Array tab = init(taille);
	int j=0;
	for (int i=0;i<taille;i++){
		tab.array[j] = t.array[i+t.size/2];
		j++;
	}
	tab.isNegative=false;
  return tab;
}

Array karatsuba(Array a1,Array b1){
	//Cas ou la taille de a ou b = 1
	Array result;
	
	if(a1.size==1 || b1.size==1){
		result = init(1);
		if (a1.size==1)
		{
			int val = a1.array[0];
			//printf("taille de b1 : %d\n",b1.size);
			//printf("taille de a1 : %d valeur de a[0] = %d\n",a1.size,a1.array[0]);
			//printArray(b1);
			for (int i = 0; i < val; ++i)
			{
				//printf("val = %d i= %d taille de result = %d\n",val,i,result.size);
				Array tmp = copy(result);
				freeArray(&result);
				result = sumArrays(tmp,b1);
				freeArray(&tmp);
			}
			//printf("resultat : ");printArray(result);
			result.isNegative=(a1.isNegative==b1.isNegative)?(false):(true);
			result = reduction(result);
			//printf("taille de result : %d\n",result.size);
			return result;
		}
		else{
			if (b1.size==1)
			{
				int val = b1.array[0];
				for (int i = 0; i < val; ++i)
				{
					Array tmp = copy(result);
					freeArray(&result);
					result = sumArrays(result,a1);
					freeArray(&tmp);
				}
			result.isNegative=(a1.isNegative==b1.isNegative)?(false):(true);
			result = reduction(result);
			return result;
			}
		}
	}

	//
	//dans le cas contraire
	if(a1.size>1 && b1.size>1){
		//result = init(a1.size+b1.size);
		// AJUSTEMENT DE LA TAILLE DES TABLEAUX
		//printf("O a1.size = %d b1.size = %d\n",a1.size,b1.size);
		Array a =  ajustArraySize(a1,b1);
		Array b =  ajustArraySize(b1,a1);
		size_t s = (a1.size%2==0)?(a1.size/2):((a1.size/2)+(a1.size%2));
		bool resPos=true;
		
		//Si un des tableaux est négatif alors le resultat est forcement négatif
		//la variable resPos indique si le resultat est négatif (false) ou positif (true)
		if((a.isNegative==true && b.isNegative==false) ||
		   (a.isNegative==false && b.isNegative==true)){
				resPos = false;
				a.isNegative=false;
				b.isNegative=false;
		}

		Array A = substrl(a);
		Array B = substrr(a);
		Array C = substrl(b);
		Array D = substrr(b);
		
		freeArray(&a); freeArray(&b);
		
		
		Array AC = karatsuba(A,C);
		Array q = subArrays(A,B);
		Array w = subArrays(C,D);
		Array P = karatsuba(q,w);
		freeArray(&q);
		freeArray(&w);
		Array BD = karatsuba(B,D);
		
		freeArray(&A);
		freeArray(&B);
		freeArray(&C);
		freeArray(&D);
		
		Array ac = aggrandissement(AC,2*s);
		Array r1 = sumArrays(AC,BD);
		Array r2 = subArrays(r1,P);
		Array z = aggrandissement(r2,s);
		Array r3 = sumArrays(ac,z);
		result = sumArrays(r3,BD);
		
		freeArray(&AC);
		freeArray(&P);
		freeArray(&BD);
		freeArray(&ac);
		freeArray(&r1);
		freeArray(&r2);
		freeArray(&z);
		freeArray(&r3);
		
		//Si resPos est faux alors le resultat est négatif
		if(resPos == false)
			result.isNegative=true;
		
		return result;
		
	}
}
