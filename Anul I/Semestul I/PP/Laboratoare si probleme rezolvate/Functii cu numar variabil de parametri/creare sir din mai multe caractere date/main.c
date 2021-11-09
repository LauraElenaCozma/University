#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char * creare_sir(char c,...)
{
    if(c=='\0')
        return NULL;
    else
    {
        va_list lista;
        va_start(lista,c);

        char *sir;
        char x;
        sir=(char *)malloc(2*sizeof(char));
        sir[0]=c;
        sir[1]='\0';

        while((x=va_arg(lista,int))!='\0')
        {
            char *aux;
            int ls = strlen(sir);
            aux=(char *)realloc(sir,ls+2);

            if(aux==NULL)
            {
                printf("Eroare realocare");
                free(sir);
                return NULL;
            }

            sir=aux;
            sir[ls]=x;
            sir[ls+1]='\0';
        }

        va_end(lista);
        return sir;
    }
}
int main()
{
    printf("%s ",creare_sir('s','a','u','n','a','\0'));
    return 0;
}
