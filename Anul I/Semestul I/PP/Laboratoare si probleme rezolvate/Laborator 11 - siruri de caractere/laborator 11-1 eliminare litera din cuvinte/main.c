#include <stdio.h>
#include <stdlib.h>

void citire(char *fisier)
{
    char c,x;
    FILE *f,*fout;
    f=fopen(fisier,"r");
    fout=fopen(fisier,"a");

    c=fgetc(f);


    while((x=fgetc(f))!=EOF)
    {
        if(x!=c)
            fprintf(fout,"%c",x);
    }
}


int main()
{
    citire("f.in");
    return 0;
}
