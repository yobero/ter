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

Array init(size_t nbElement){
	Array a;
	a.array = calloc(nbElement,sizeof(int));
	a.size = nbElement;
	a.isNegative = false;
	return a;
}

Array reduction(Array a){
	if(a.size>1){
		Array result;
		int compteur=0;
		for(int i=0;i<a.size;i++){
			if(a.array[i]!=0) break;
			else compteur++;
		}
		if(compteur==a.size){ Array zero = init(1);return zero; }
		result=init(a.size-compteur);
		int j=0;
		for(int i=compteur;i<a.size;i++){
			result.array[j]=a.array[i];
			j++;
		}
		result.isNegative=a.isNegative;
		return result;
	}
	return a;
}

Array opposer(Array a){
	Array op = reduction(a);
	op.isNegative = (a.isNegative==true)?(false):(true);
	return op;
}

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

Array copy(Array a) {
  Array copiedArray = init(a.size);
	copiedArray.isNegative = a.isNegative;
  for(int i=0; i<a.size; i++){
      copiedArray.array[i] = a.array[i];
  }
  return copiedArray;
}

Array ajustArraySize(Array a1, Array b1) {

  // 1) on garde en mémoire le tableau a dans tmp
  // 2) on remet à 0 le tableau a, avec la taille de b
  // 3) on recopie depuis la fin le tableau tmp dans a
  // 4) on désalloue la mémoire de tmp
  // 5) on retourne a modifié avec du padding à 0 à l'avant du tableau
	Array a = reduction(a1);
	Array b = reduction(b1);

  if(a.size < b.size) {
    Array tmp = copy(a);
    a.size = b.size;
		initArrayToZero(&a, a.size);
		size_t saveBsize = b.size;

    for(int i=tmp.size - 1; i>=0; i--, b.size--) {
      a.array[b.size-1] = tmp.array[i];
    }
		b.size = saveBsize;
		a.isNegative = tmp.isNegative;
    freeArray(&tmp);
    return a;
  }else {
	return a;
  }
}

Array aggrandissement(Array a,size_t adroite){
	Array result = init(a.size+adroite);
	//simple copie du tableau a
	//result.isNegative=a.isNegative;
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

int whoIsTheBiggest(Array a1, Array b1){
	Array a = ajustArraySize(a1,b1);
	Array b = ajustArraySize(b1,a1);

	if(a.isNegative == false && b.isNegative == false){
		return biggest(a,b);
	}

	if(a.isNegative == true && b.isNegative == false){
		return -1; // a < b
	}

	if(a.isNegative == false && b.isNegative == true) {
		return 1; // a > b
	}

	if(a.isNegative == true  && b.isNegative == true) {
		return biggest(a,b);
	}

	return 22; // return par défaut
}

Array sumArrays(Array a, Array b){
	Array a1 = ajustArraySize(a,b);
	Array b1 = ajustArraySize(b,a);
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
		return opposer(sumArrays(opposer(a),opposer(b)));
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

Array substrr(Array t)
{
	Array tab = init(t.size-substrl(t).size);
	int j=0;
	for (int i=0;i<t.size-substrl(t).size;i++){
		tab.array[j] = t.array[i+substrl(t).size];
		j++;
	}
	tab.isNegative=false;
  return tab;
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

Array karatsuba(Array a1,Array b1){
	//Cas ou la taille de a ou b = 1
	Array result = init(a1.size+b1.size);
	
	if(a1.size==1 || b1.size==1){
		if (a1.size==1)
		{
			int val = a1.array[0];
			for (int i = 0; i < val; ++i)
			{
				result = sumArrays(result,b1);
			}
		result.isNegative=(a1.isNegative==b1.isNegative)?(false):(true);
		result = reduction(result);
		return result;
		}

		if (b1.size==1)
		{
			int val = b1.array[0];
			for (int i = 0; i < val; ++i)
			{
				result = sumArrays(result,a1);
			}
		result.isNegative=(a1.isNegative==b1.isNegative)?(false):(true);
		result = reduction(result);
		return result;
		}

		
	}

	//
	//dans le cas contraire
	if(a1.size>1 && b1.size>1){
		// AJUSTEMENT DE LA TAIL123456789123456789123LE DES TABLEAUX
			//Tester la paritée de la taille des nombres
		 //Array a = reduction(a1);
		 //Array b = reduction(b1);
		//Array a =  ajustArraySize(a1,b1);
		//Array b =  ajustArraySize(b1,a1);
		//printf("a1.size = %d b1.size = %d ",a.size,b.size);
		 size_t s = (a1.size%2==0)?(a1.size/2):((a1.size/2)+(a1.size%2));
		bool resPos=true;
		
		if((a1.isNegative==true && b1.isNegative==false) ||
		   (a1.isNegative==false && b1.isNegative==true)){
				resPos = false;
				a1.isNegative=false;
				b1.isNegative=false;
		}

		Array A = substrl(a1);
		//printf("A : ");printArray(A);
		Array B = substrr(a1);
		//printf("B : ");printArray(B);
		Array C = substrl(b1);
		//printf("C : ");printArray(C);
		Array D = substrr(b1);
		//printf("D : ");printArray(D);
		
		Array AC = karatsuba(A,C);
		//printf("AC : ");printArray(AC);
		Array q = subArrays(A,B);
		Array w = subArrays(C,D);
		//printf("a-b : ");printArray(q);
		//printf("c-d : ");printArray(w);
		Array P = karatsuba(q,w);
		freeArray(&q);
		freeArray(&w);
		//printf("P : ");printArray(P);
		Array BD = karatsuba(B,D);
		//printf("BD : ");printArray(BD);
		
		freeArray(&A);
		freeArray(&B);
		freeArray(&C);
		freeArray(&D);
		
		//printf("AC : &&");printArray(ac);
		Array ac = aggrandissement(AC,2*s);
		//printf("ac : &&");printArray(ac);
		Array r1 = sumArrays(AC,BD);
		Array r2 = subArrays(r1,P);
		//printf("r2 : &&");printArray(r2);
		Array z = aggrandissement(r2,s);
		//printf("z : &&&");printArray(z);
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
		//printf("res : ");printArray(result);
		
		if(resPos == false)
			result.isNegative=true;
		
		return result;
		
	}
}
