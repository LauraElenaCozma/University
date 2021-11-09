#include <stdio.h>
#include <stdlib.h>

/*
2. Scrieți un program care conține declarațiile
char a=-12, b=’a’;
unsigned char c=12, d=-12, e=’x’;
și apoi afișează liniile de mai jos:
-12  a  97  61// valoarea lui a, valoarea lui b, codul caracterului memorat in b in baza 10 si in baza 16
12  244  x 120// valoarea lui c, numarul corespunzator lui d, valoarea lui e, codul caracterului memorat in e in baza 10

*/
int main()
{
    char a=-12,b='a';
    unsigned char c=12, d=-12, e='x';
    printf("%d %c %d %d\n",a,b,b,3*a+b);  //97 e codul ascii a lui a; 61=97-2*12
    printf("%d %d %c %d",c,d,e,e);
    /*12=valoarea numerica a lui c
    244= deoarece e de tipul unsigned char si d e negativ, se trece in cealalta parte
    120=codul ascii a lui x*/
    return 0;
}
