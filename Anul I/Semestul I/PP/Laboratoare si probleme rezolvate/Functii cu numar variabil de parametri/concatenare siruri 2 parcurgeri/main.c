#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char * concatenare(char *sir,...)
{
    //if(sir==NULL)
     //   return NULL;
    va_list lista;
    va_start(lista,sir);

    char *sir_nou,*s;
    int lungime_sir=strlen(sir);

    while(strcmp((s=va_arg(lista,char *)),"\0")!=0)
        lungime_sir+=strlen(s);


   va_end(lista);


    sir_nou=(char *)malloc((lungime_sir+1)*sizeof(char));
    strcpy(sir_nou,sir);
   // va_list lista1;
    va_start(lista,sir);

    while(strcmp((s=va_arg(lista,char *)),"\0")!=0)
        strcat(sir_nou,s);
    return sir_nou;
    va_end(lista);

}


int main()
{
    printf("%s",concatenare("ana","e","buna la","  engleza!!","\0"));
    return 0;
}
