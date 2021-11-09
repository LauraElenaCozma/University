#include <stdio.h>
#include <stdlib.h>
///nu e cine stie ce, nu mai am cgef sa modific greseaka

void citire(char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");
    FILE * f1=tmpfile();
    if(f==NULL)
    {
        printf("Eroare deschidere fisier");
        return 0;
    }

    char c1,c2,c;
    fscanf(f,"%c %c",&c1,&c2);
    printf("%c %c",c1,c2);

    while((c=fgetc(f))!=EOF)
    {
        if(c==c1)
           fprintf(f1,"%c",c2);
        else fprintf(f1,"%c",c);
        printf("%c",c);

    }
    freopen(numeFisier,"w",f);
    while((c=fgetc(f1))!=EOF)
    {
        printf("%c",c);
        fprintf(f,"%c",c);
    }
    fclose(f1);
    fclose(f);
}



int main()
{
    citire("f.in");
    return 0;
}
