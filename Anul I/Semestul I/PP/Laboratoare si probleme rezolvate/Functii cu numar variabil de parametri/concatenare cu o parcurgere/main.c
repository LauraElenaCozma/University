#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char * concatenare(char *primul_sir,...)
{
    if(primul_sir==NULL)
        return primul_sir;
    else
    {
        char *sir,*s;
        int ls=strlen(primul_sir);
        sir=malloc(sizeof(char)*(ls+1));

        strcpy(sir,primul_sir);

        va_list lista;
        va_start(lista,primul_sir);

        while(strcmp((s=va_arg(lista,char *)),"\0")!=0)
        {
            //nu am ajuns inca la sirul vid
            ls=strlen(sir);
            char *aux;
            aux=(char *)realloc(sir,sizeof(char)*(ls+strlen(s)+1));

            if(aux==NULL)
            {
                printf("Eroare realocare");
                free(sir);
                return NULL;
            }
            sir=aux;
            strcat(sir,s);
        }

        va_end(lista);
        return sir;
    }
}
int main()
{
    printf("%s",concatenare("oare d","e"," ce dureaza","  engleza!!","asa ","mult","\0"));
    return 0;
}
