#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char * prefix(char * primul_sir,...)
{

    if(primul_sir==NULL)
        return NULL;

    va_list lista;
    va_start(lista,primul_sir);

    char *prefix,*s;
    prefix=(char *)malloc(strlen(primul_sir)+1);
    strcpy(prefix,primul_sir);

    int nr=strlen(prefix);

    while((s=va_arg(lista,char *))!=NULL)
    {
        while(nr!=0 && strstr(s,prefix)!=s)
            prefix[--nr]='\0';
        if(nr==0)
        {
            free(prefix);
            va_end(lista);
            return NULL;
        }

    }
    va_end(lista);
    return prefix;

}


int main()
{
    printf("%s",prefix("anita","anisort","nnibela",NULL));
    return 0;
}
