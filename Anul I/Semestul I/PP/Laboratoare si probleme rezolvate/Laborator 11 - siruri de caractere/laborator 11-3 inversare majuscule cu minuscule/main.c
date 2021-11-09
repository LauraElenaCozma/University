#include <stdio.h>
#include <stdlib.h>

void citire(char *fisier)
{
    char x;
    FILE *f;
    f=fopen(fisier,"r+");

    while((x=fgetc(f))!=EOF)
    {


            if(x>='a' && x<='z')
               {
                   x=x-'a'+'A';
                   fseek(f,-sizeof(char),SEEK_CUR);
                   fprintf(f,"%c",x);
                   fflush(f);
               }
            else if(x>='A' && x<='Z')
            {
                   x=x-'A'+'a';
                   fseek(f,-sizeof(char),SEEK_CUR);
                   fprintf(f,"%c",x);
                   fflush(f);
            }


    }
}


int main()
{
    citire("f.in");
    return 0;
}
