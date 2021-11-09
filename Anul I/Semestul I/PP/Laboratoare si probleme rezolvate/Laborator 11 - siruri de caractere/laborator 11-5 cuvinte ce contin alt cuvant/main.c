#include <stdio.h>
#include <stdlib.h>

void citire(char *fisier)
{
    char s[100],cuv[100];
    FILE *f;
    f=fopen(fisier,"r");

   if(f==NULL)
    return 0;

    scanf("%s",s);

    while(fscanf(f,"%s",cuv)==1)
    {
        if(strstr(cuv,s)!=NULL)
            printf("%s ",cuv);
    }

    fclose(f);
}


int main()
{
    citire("f.in");
    return 0;
}
