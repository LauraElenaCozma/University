#include <stdio.h>
#include <stdlib.h>
int prelucrare(FILE * f)
{
    f=fopen("f.in","r");

    if(f==NULL)
        return -1;

    char c1,c2;
    c1=fgetc(f);
    if(c1!=EOF)//fisierul nu e vid
    {
        while((c2=fgetc(f))!=EOF)
        {
            if(c1=='/' && c2=='/')
            {
                c2=fgetc(f);
                while(c2!='\n' && c2!=EOF) //cat timp nu am ajuns la final de rand sau la sfarsit de fisier
                    c2=fgetc(f);
            }
            else if(c1=='/' && c2=='*')
            {
               while(!(c1=='*' && c2=='/'))
               {
                   c1=c2;
                   c2=fgetc(f);
               }
               //aici ne oprim cand c1 va fi steluta si c2 / asa ca trebuie sa sarim peste si sa ii mai facem o citire lui c2 ca la atribuire c1 sa primeasca urmatorul caracter de dupa comentaariu
               c2=fgetc(f);
            }
                 else
                     printf("%c",c1);
            c1=c2;
        }
    }

    fclose(f);
}
int main()
{
    FILE *f;
    prelucrare(f);
    return 0;
}
