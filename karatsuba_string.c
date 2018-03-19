#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef char* string;

#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define TRUE 1
#define FALSE 0



//test si un nombre est négatif ou non
int isnegatif(const char* s)
{
	 if (s[0]=='-')
	 {
	 	return TRUE;
	 }
	 return FALSE;
}


//test si un nombre est égal à 0
int iszero(const char* s)
{
	int t = strlen(s);
	int n = isnegatif(s);
	int i = 0;
	while(i < t && s[n+i]=='0'){i++;}
	if (n+i==t)
	{
		return TRUE;
	}
	return FALSE;
}


//enlève les zéros inutiles
char* decale(const char* c)
{
	char* res;
	int l = strlen(c);
	int n = isnegatif(c);
	int i = 0;
	res = malloc(l);

	if (iszero(c)==TRUE)
	{
		res[0] = '0';
		res[1] = '\0';
		return res;
	}

	if (iszero(c)==FALSE)
	{		
		while(i<l && c[i+n]=='0'){i++;}
		if (n==TRUE)
		{
			res[0]='-';
			for (int j = 0; j < l; ++j)
			{
				char v = (j>=0)?(c[j+i+n]):(0);
				res[j+1] = v;
			}
			res[l-i] = '\0';
			return res;
		}
		if (n==FALSE)
		{
			for (int j = 0; j < l; ++j)
			{
				char v = (j>=0)?(c[j+i]):(0);
				res[j] = v;
			}
		}

	res[l-i] = '\0';	
	if (res[l-i-1]!= '0'&& res[l-i-1] != '1' && res[l-i-1] != '2'&& res[l-i-1] != '3' && res[l-i-1] != '4'&& res[l-i-1] != '5' && res[l-i-1] != '6'&& res[l-i-1] != '7' && res[l-i-1] != '8'&& res[l-i-1] != '9')
	{
		res[l-i-1] = '\0';
	}
		
		return res;
		
	}
	
	return res;		
}

//test si un nombre est égal à 1
int isUn(const char* s)
{
	char* s1 = decale(s);

	if (isnegatif(s1)==FALSE && strlen(s)==1 && s1[0]=='1')
	{
		return TRUE;
	}
	return FALSE;
}

//test si un nombre est égal à -1
int ismoinsUn(const char* s)
{
	char* s1 = decale(s);
	if (isnegatif(s1)==TRUE && s1[1]=='1' && strlen(s)==2)
	{
		return TRUE;
	}
	return FALSE;
}

//opposer d'un nombre
char* opposer(const char* s)
{
	char* res;
	int len = strlen(s);
	
	if (isnegatif(s)==TRUE)
	{	res = malloc(len+1);
		
		for (int i = 0; i < len+1; ++i)
		{
			res[len-i-1]=(len-i-1>=0)?(s[len-i-1]):(0);
		}
		res[0]='0';
		res[len]='\0';
	}

	if (isnegatif(s)==FALSE)
	{	res = malloc(len+2);
		
		for (int i = 0; i < len+1; ++i)
		{
			res[len-i]=(len-i>=0)?(s[len-i-1]):(0);
		}
		res[0]='-';
		res[len+1]='\0';
	}
	return res;
}

//valeur en int d'un chiffre
int valeurde(const char* s)
{
	char* ss = decale(s); 
	char sss = (isnegatif(ss)==TRUE)?(ss[1]-'0'):(ss[0]-'0');
	int v = sss;
	return v;
}

//compter le nombre de zéro en fin des nombres
int compterZero(const char* s)
{	
	char* ss = decale(s);
	int l = strlen(ss);
	int i = 0;
	int k = isnegatif(s);
	while(l-1>=k && ss[l-1]=='0'){
		l = l-1;
		i++;
	}
	return i ;
}

//enlever les zéros en fin des nombres
char* enleverZeroArriere(const char* s)
{
	char* ss = decale(s); 
	int l = strlen(ss);
	int k = compterZero(ss);
	for (int i = 0; i < l-k; ++i)
	{
		char sss = ss[i];
		ss[i] = sss;
	}
	ss[l-k] = '\0';
	return ss;
}

//0 : EGAL / 1 : s1 < s2 / 2 : s1 > s2
int comparaison_nombre(const char* s1,const char* s2)
{
	
	int len1 = strlen(s1);
    int len2 = strlen(s2);
    int reslen = 1 + MAX(len1,len2);
	int ss1[reslen];
	int ss2[reslen];
	ss1[reslen]='\0';
	ss2[reslen]='\0';
	int j = 0;
	for (int i = 0; i < reslen; ++i)
	{
		ss1[reslen-i-1] = (len1-i-1>=0)?(s1[len1-i-1]-'0'):(0);
		ss2[reslen-i-1] = (len2-i-1>=0)?(s2[len2-i-1]-'0'):(0);
	}
	
	
	if (isnegatif(s1)==FALSE && isnegatif(s2)==FALSE)
	{	
		while(j<reslen && ss1[j]==ss2[j]){++j;}
	    
		if (j<reslen && ss1[j]>ss2[j]){	return 2;}
		if (j<reslen && ss1[j]<ss2[j]){	return 1;}
		
		return 0;	
	}

	// S1 et s2 négatifs
	if(isnegatif(s1)==TRUE && isnegatif(s2)==TRUE )
	{
		int c = comparaison_nombre(opposer(s1),opposer(s2));
	    
		if (c==0){return 0;}// s1 = s2
		if (c==1){return 2;}// s1 > s2
		if (c==2){return 1;}// s1 < s2
		
	}

	//S1 positif et s2 négatif
	if (isnegatif(s1)==FALSE && isnegatif(s2)==TRUE){return 2;}// s1 > s2

	//s1 négatif et s2 positif
	if (isnegatif(s1)==TRUE && isnegatif(s2)==FALSE){return 1;}// s1 < s2
}
	
    
//addition de deux nombres
char* additionner(const char* s1,const char* s2)
{
    char* res;
    int i;
    char retenue = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int reslen = 1 + MAX(len1,len2);
    res = malloc(reslen+1);
    res[reslen] = '\0';

    //addition avec 0
    if (iszero(s1)==TRUE)
    {
    	for (int i = 0; i < len2; ++i)
    	{
    		res[i]=s2[i];
    	}
    	res=decale(res);
    	return res;
    }

    if (iszero(s2)==TRUE)
    {
    	for (int i = 0; i < len1; ++i)
    	{
    		res[i]=s1[i];
    	}
    	res=decale(res);
    	return res;
    }

    //addition nombres opposés
    if ((comparaison_nombre(s1,opposer(s2))==0)||(comparaison_nombre(opposer(s1),s2)==0) )
    {
    	res[0]='0';res[1]='\0';
    	return res;
    }

    //addition nombres positifs (ex: 6 + 2)
    if (isnegatif(s1)==FALSE && isnegatif(s2)==FALSE)
    {
    	for(i=0;i<reslen;i++)
	    {
	        char chiffre1 = (len1-i-1>=0)?(s1[len1-i-1]-'0'):(0);
	        char chiffre2 = (len2-i-1>=0)?(s2[len2-i-1]-'0'):(0);
	        char addition = chiffre1 + chiffre2 + retenue;
	        retenue = addition/10;
	        addition = addition%10;
	        res[reslen-i-1] = addition + '0';
	    }
	    res = decale(res);
	    return res;
    }

    //addition nombres de la forme 6 + (-2)
    if (isnegatif(s1)==FALSE && isnegatif(s2)==TRUE)
    {char addition;
    	
    	char* ss2 = opposer(s2);
    	if(comparaison_nombre(s1,ss2)==2)
    	{char addition;
    		for(i=0;i<reslen;i++)
		    {	char chiffre1 = (len1-i-1>=0)?(s1[len1-i-1]-'0'):(0);
		        char chiffre2 = (len2-i-1>=0)?(ss2[len2-i-1]-'0'):(0);

		        if (chiffre1<(chiffre2+retenue))
		        {
		        	 addition = 10 + chiffre1 - (chiffre2 + retenue);
		        	 retenue = 1;
		        }else{

		        	 addition = chiffre1 - (chiffre2 + retenue);
			        retenue = 0;
		        }
		        //printf("%d\n",addition);
		        //retenue = addition/10;
			    addition = addition%10;
			    res[reslen-i-1] = addition + '0';
		        
		    }
		    res = decale(res);
		    return res;
    	}

    	if(comparaison_nombre(s1,ss2)==1)
    	{char addition;
    		for(i=0;i<reslen;i++)
		    {	char chiffre1 = (len1-i-1>=0)?(s1[len1-i-1]-'0'):(0);
		        char chiffre2 = (len2-i-1>=0)?(ss2[len2-i-1]-'0'):(0);
		        
		        if (chiffre2<(chiffre1+retenue))
		        {
		        	addition = 10 + chiffre1 - (chiffre2 + retenue);
		        	retenue = 1;
		        }else{
		            addition = chiffre2 - (chiffre1 + retenue);
		            retenue = 0;
		        }
			        //retenue = addition/10;
			        addition = addition%10;
			        res[reslen-i-1] = addition + '0';
		  
		    }
		    res[0]='-';
		    res = decale(res);
		    return res;
    	}
    }

    	//addition nombres de la forme (-6) + 2)
    if (isnegatif(s1)==TRUE && isnegatif(s2)==FALSE)
    {   char addition;
    	char* ss1 = opposer(s1);
    	if(comparaison_nombre(ss1,s2)==2){
    		for(i=0;i<reslen;i++)
		    {	char chiffre1 = (len1-i-1>=0)?(ss1[len1-i-1]-'0'):(0);
		        char chiffre2 = (len2-i-1>=0)?(s2[len2-i-1]-'0'):(0);
		        if (chiffre1<(chiffre2+retenue))
		        {
		        	addition = 10 + chiffre1 - (chiffre2 + retenue);
		        	retenue = 1;
		        }else{
		            addition = chiffre1 - (chiffre2 + retenue);
		            retenue = 0;
		        }
			        //retenue = addition/10;
			        addition = addition%10;
			        res[reslen-i-1] = addition + '0';
		  
		        
		    }
		    res[0]='-';
		    res = decale(res);
		    return res;
    	}

    	if(comparaison_nombre(ss1,s2)==1){
    		char addition;
    		for(i=0;i<reslen;i++)
		    {	char chiffre1 = (len1-i-1>=0)?(ss1[len1-i-1]-'0'):(0);
		        char chiffre2 = (len2-i-1>=0)?(s2[len2-i-1]-'0'):(0);
		        if (chiffre2<(chiffre1+retenue))
		        {
		        	addition = 10 + chiffre2 - (chiffre1 + retenue);
		        	retenue = 1;
		        }else{
		            addition = chiffre2 - (chiffre1 + retenue);
		            retenue = 0;
		        }
			        //retenue = addition/10;
			        addition = addition%10;
			        res[reslen-i-1] = addition + '0';
		  
		    }
		    res = decale(res);
		    return res;
    	}	
    }
    	
	    


    //addition nombres de la forme (-6) + (-2)
    if (isnegatif(s1)==TRUE && isnegatif(s2)==TRUE)
    {
    	char* ss1 = opposer(s1);
    	char* ss2 = opposer(s2);
    	for(i=0;i<reslen;i++)
	    {	char chiffre1 = (len1-i-1>=0)?(ss1[len1-i-1]-'0'):(0);
	        char chiffre2 = (len2-i-1>=0)?(ss2[len2-i-1]-'0'):(0);
	        
	        char addition = chiffre1 + chiffre2 + retenue;
	        retenue = addition/10;
	        addition = addition%10;
	        res[reslen-i-1] = addition + '0';
	    }
	    res[0]='-';
	    res = decale(res);
	    //if(res == NULL){res[0]='0';res[1]='\0';}
	    return res;
    }
     
}

//multiplication par 10^n 
char* fois_10_puissance(const char* c , int n)
{
	
	char* cc;
	int len = strlen(c);
	cc = malloc(len+n);
	
	for (int i = 0; i < len+n; ++i)
	{
		 char value = (i>=0 && i<len)?(c[i]):('0'); 
		 cc[i] = value;
	}
	cc[len+n]='\0';
	return cc;
}

//soustraction de deux nombres
char* soustraire(const char* s1,const char* s2)
{
    char* res;
    int i;
    char retenue = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    int reslen = 1 + MAX(len1,len2);
    res = malloc(reslen+1);
    res[reslen] = '\0';

    //soustraction nombres &égaux
    if (comparaison_nombre(s1,s2)==0)
    {
    	res[0]='0';res[1]='\0';
    	return res;
    }

    //soustarction nombres négatifs (ex: (-6) - (-2)
    if (isnegatif(s1)==TRUE && isnegatif(s2)==TRUE)
    {	
    	return additionner(s1, opposer(s2));
    }

    //soustraction nombres positif et négatif (ex: 4 - (-8))
    if (isnegatif(s1)==FALSE && isnegatif(s2)==TRUE)
    {	
    	return additionner(s1, opposer(s2));
    }

    //soustraction nombres négatif et positif (ex: (-7) - 3)
    if (isnegatif(s1)==TRUE && isnegatif(s2)==FALSE)
    {	res = additionner(s1, opposer(s2));
    	res[0]='-';
    	return res;
    }

    //soustraction nombres positifs (ex: 5 - 2)
    if (isnegatif(s1)==FALSE && isnegatif(s2)==FALSE)
    {
    	return additionner(s1,opposer(s2));
    }    
}

//partie gauche d'un nombre
char* partie_gauche(const char* s1)
{
	char* s = decale(s1);
	int d = isnegatif(s);
	int len = (strlen(s));
	int lenn = (len%2==0)?((len/2)+d):((len/2)+1+d);
	char* ss1;
	ss1 = malloc(lenn);
	
	for (int i = 0; i < lenn; i++)
	{
		 char value = (i>=0)?(s[i]):(0); 
		 ss1[i] = value;
	}
	ss1[lenn] = '\0';
	/*if (ss1[len-lenn-1]!= '0'&& ss1[len-lenn-1] != '1' && ss1[len-lenn-1] != '2'&& ss1[len-lenn-1] != '3' && ss1[len-lenn-1] != '4'&& ss1[len-lenn-1] != '5' && ss1[len-lenn-1] != '6'&& ss1[len-lenn-1] != '7' && ss1[len-lenn-1] != '8'&& ss1[len-lenn-1] != '9')
	{
		ss1[len-lenn-1] = '\0';
	}*/
	return ss1;
}

//patie droite d'un nombre(à faire)
char* partie_droite(const char* s1)
{	
	char* s = decale(s1);
	int d = isnegatif(s);
	int len = (strlen(s));
	int lenn = (strlen(partie_gauche(s)));
	int lle = len-lenn;
	int lim = len%2;
	char* ss1;
	ss1 = malloc(lle);
	for (int i = 0; i < lle; i++)
	{
		 char value = (i>=0)?(s[lenn+i]):(0); 
		 ss1[i] = value;
	}
	/*ss1[len-lenn] = '\0';
	if (ss1[len-lenn-1]!= '0'&& ss1[len-lenn-1] != '1' && ss1[len-lenn-1] != '2'&& ss1[len-lenn-1] != '3' && ss1[len-lenn-1] != '4'&& ss1[len-lenn-1] != '5' && ss1[len-lenn-1] != '6'&& ss1[len-lenn-1] != '7' && ss1[len-lenn-1] != '8'&& ss1[len-lenn-1] != '9')
	{
		ss1[len-lenn-1] = '\0';
	}*/
	return ss1;
}

int ispuissance10(const char* s)
{
	int i = 0;
	int l = strlen(s);
	if (s[0]=='1' && isnegatif(s)==FALSE)
	{
		while(i<l && s[i+1]=='0'){i++;}
		if (i==l-1)
		{
			return TRUE;
		}
	}

	if (s[0]=='-' && s[1]=='1' && isnegatif(s)==TRUE)
	{
		while(i<l && s[i+2]=='0'){i++;}
		if (i==l-2)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int power10(const char* s)
{
	int i = 0;
	int l = strlen(s);
	if (ispuissance10(s)==TRUE && isnegatif(s)==FALSE)
	{
		return l-1;
	}

	if (ispuissance10(s)==TRUE && isnegatif(s)==TRUE)
	{
		return l-2;
	}
}

//multiplication de deux chiffres
char* multiplier(const char* p1 , const char* p2)
{
	char* c1 = decale(p1);
	char* c2 = decale(p2);
	char* produit;

	//muliplication par 0
	if ((iszero(c1)==TRUE) || (iszero(c2)==TRUE))
	{
		produit = decale(c1);
		return produit;
	}

	//multiplication par 1
	if (isUn(c1)==TRUE)
	{
		produit = decale(opposer(opposer(c2)));
		return produit;
	}

	if (isUn(c2)==TRUE)
	{
		produit = decale(opposer(opposer(c1)));
		return produit;
	}

	//multiplication avec -1
	if (ismoinsUn(c1)==TRUE)
	{
		produit = decale(opposer(c2));
		return produit;
	}

	if (ismoinsUn(c2)==TRUE)
	{
		produit = decale(opposer(c1));
		return produit;
	}

	//multiplication par puissance de 10
		//negatif
	if (isnegatif(c1)==TRUE && ispuissance10(c1)==TRUE)
	{
		return fois_10_puissance(c2,power10(c1));
	}

	if (isnegatif(c2)==TRUE && ispuissance10(c2)==TRUE)
	{
		return fois_10_puissance(c1,power10(c2));
	}
		//positif
	if (isnegatif(c1)==FALSE && ispuissance10(c1)==TRUE)
	{
		return fois_10_puissance(c2,power10(c1));
	}

	if (isnegatif(c2)==FALSE && ispuissance10(c2)==TRUE)
	{
		return fois_10_puissance(c1,power10(c2));
	}
	

	//multipliction avec des chiffres négatifs
	if ((isnegatif(c1)==FALSE && isnegatif(c2)==FALSE)||(isnegatif(c1)==TRUE && isnegatif(c2)==TRUE))
	{
		char nbr1 = c1[isnegatif(c1)]-'0';
		char nbr2 = c2[isnegatif(c2)]-'0';
		produit[0] = (nbr1*nbr2)/10+'0';
		produit[1] = (nbr1*nbr2)%10+'0';
		produit[2] = '\0';
		return produit;
	}

	if ((isnegatif(c1)==TRUE && isnegatif(c2)==FALSE)|| (isnegatif(c1)==FALSE && isnegatif(c2)==TRUE))
	{
		char nbr1 = c1[isnegatif(c1)]-'0';
		char nbr2 = c2[isnegatif(c2)]-'0';
		produit[0] = '-';
		produit[1] = (nbr1*nbr2)/10+'0';
		produit[2] = (nbr1*nbr2)%10+'0';
		produit[3] = '\0';
		return produit;
	}
}


char* karatsuba(const char* p1 , const char* p2)
{	
	char* c1 = decale(p1);
	char* c2 = decale(p2);
	char* result;
	char* ra;
	char* la;
	char* rb;
	char* lb;
	char* a0;
	char* a1;
	char* a2;
	char* u;
	char* v;
	char* x;
	char* y;
	char* z;
	char* w;
	char* q;

	int lc1 = (isnegatif(c1)==TRUE)?(strlen(c1)-1):(strlen(c1));
	int lc2 = (isnegatif(c2)==TRUE)?(strlen(c2)-1):(strlen(c2));
	int m = MAX(lc1,lc2);
	
	int z1 = compterZero(c1);
	int z2 = compterZero(c2);

	//lorsqu'au moins un des nombres est une puissance de 10
	if (ispuissance10(c1)==TRUE || ispuissance10(c2)==TRUE)
	{
		return multiplier(c1,c2);
	}
	

	//lorsqu'un des nombres est une unité
	if (strlen(c1)==1 && isnegatif(c1)==FALSE && iszero(c1)==FALSE)
	{	int i = 0;
		result = opposer(opposer(c2));
		while(i<valeurde(c1)-1){			
			result = additionner(result,c2);
			i++;
		}
		return result;
	}

	if (strlen(c2)==1 && isnegatif(c2)==FALSE && iszero(c2)==FALSE)
	{	int i = 0;
		result = opposer(opposer(c1));
		while(i<valeurde(c2)-1){			
			result = additionner(result,c1);
			i++;
		}
		return result;
	}



	//lorsque les nombres sont tous négatifs
	if (isnegatif(c1)==TRUE && isnegatif(c2)==TRUE)
	{
		return karatsuba(opposer(c1),opposer(c2));
	}

	//lorsque l'un des nombres est négatif
	if (isnegatif(c1)==FALSE && isnegatif(c2)==TRUE)
	{
		return opposer(karatsuba(c1,opposer(c2)));
	}

	if (isnegatif(c1)==TRUE && isnegatif(c2)==FALSE)
	{
		return opposer(karatsuba(opposer(c1),c2));
	}


	//l'un des nombres est égal à 0
	if (iszero(c1)==TRUE || iszero(c2)==TRUE || isUn(c1)==TRUE || isUn(c2)==TRUE || ismoinsUn(c1)==TRUE || ismoinsUn(c2)==TRUE)
	{
		return multiplier(c1,c2);
	}

	//lorsque les nombres sont des unités
	if((isnegatif(c1)==TRUE && isnegatif(c2)==TRUE && m<=2)||(m<=1)|| (isnegatif(c1)==FALSE && isnegatif(c2)==TRUE && lc2<=2 && lc1<=1)||(isnegatif(c1)==TRUE && isnegatif(c2)==FALSE && lc1<=2 && lc2<=1))
	{
		result = multiplier(c1,c2);
		result = decale(result);
		return result;
	}
	
	if (isnegatif(c1)==TRUE)
	{
		if (lc1<=2)
		{
			int k = 0;
			char* t;t[0] = k+'0';t[1]='\0';
			la = t;
			ra = c1;
		}else{
			la = partie_gauche(c1);
			ra = partie_droite(c1);
		}
		
	 }
	 if (isnegatif(c2)==TRUE)
	{
		if (lc2<=2)
		{
			int k = 0;
			char* t;t[0] = k+'0';t[1]='\0';
			lb = t;
			rb = c2;
		}else{
			lb = partie_gauche(c2);
			rb = partie_droite(c2);
		}
		
	 }

	 if (isnegatif(c1)==FALSE)
	{
		if (lc1<=1)
		{
			int k = 0;
			char* t;t[0] = k+'0';t[1]='\0';
			la = t;
			ra = c1;
		}else{
			la = partie_gauche(c1);
			ra = partie_droite(c1);
		}
		
	 }
	 if (isnegatif(c2)==FALSE)
	{
		if (lc2<=1)
		{
			int k = 0;
			char* t;t[0] = k+'0';t[1]='\0';
			lb = t;
			rb = c2;
		}else{
			lb = partie_gauche(c2);
			rb = partie_droite(c2);
		}
		
	 }
	 	printf("la= %s\n",la);
		printf("ra = %s\n",ra);
		printf("lb= %s\n",lb);
		printf("rb = %s\n",rb);


	 
	a0 = karatsuba(la,lb);
	a1 = karatsuba(soustraire(la,ra),soustraire(lb,rb));
	a2 = karatsuba(ra,rb);
	x = fois_10_puissance(a0,m);
	y = additionner(a0,a2);
	z = soustraire(y,a1);
	w = fois_10_puissance(z,m/2);
	v = additionner(x,w);
	q = additionner(v,a2);

	printf("a0 = %s\n",a0 );
	printf("a1 = %s\n",a1 );
	printf("a2 = %s\n",a2 );
	printf("x = %s\n",x );
	printf("y = %s\n",y );
	printf("z = %s\n",z );
	printf("v = %s\n",v);
	printf("w = %s\n",w );
	printf("q = %s\n",q );
	return q;
}

int main(int argc, string* argv){
	clock_t t1, t2;	
    t1 = clock();
	if(argc>2){
		
		char* val1 = decale(argv[1]);
		char* val2 = decale(argv[2]);
		char* n1 = enleverZeroArriere(val1);
		char* n2 = enleverZeroArriere(val2);
		int k1 = compterZero(val1);
		int k2 = compterZero(val2);
		printf("%d\n",k1 );
		printf("%d\n",k2 );
		//printf("%d\n",compterZero(val1) );
		//printf("%d\n",isnegatif(val1) );
		//printf("%s\n", decale(opposer(opposer(val1))));
		//printf("%d\n", iszero(val1));
		//printf("%s\n",decale(val1) );
		//printf("%s\n",enleverZeroArriere(val2) );
		//printf("%d\n", ismoinsUn(val1));
		//printf("%d\n",ispuissance10(val2) );
		//printf("(%s) + (%s) = %s\n",val1, val2, additionner(val1,val2));
		//printf("%d\n",comparaison_nombre(val1,val2));
		//printf("(%s) - (%s) = %s\n",val1, val2, soustraire(val1,val2));
		//printf("%d\n",valeurde(val1) );
		//printf("la = %s\n",partie_gauche(val1) );
		//printf("ra = %s\n",partie_droite(val1) );
		//printf("lb = %s\n",partie_gauche(val2) );
		//printf("rb = %s\n",partie_droite(val2) );
		//printf("%s\n",fois_10_puissance(val2,3) );
		//printf("(%s) * (%s) = %s\n",val1, val2,multiplier(val1,val2) );

		printf("(%s) * (%s) = %s\n",val1, val2, fois_10_puissance(karatsuba(n1,n2),k1+k2));
		
	}
	else{
		fprintf(stderr, "Pas assez d'argument !!!\n\n");
	}
	t2 = clock();
	printf("Temps d'éxécution: %f (µs) \n", (float)((t2-t1)));
}
