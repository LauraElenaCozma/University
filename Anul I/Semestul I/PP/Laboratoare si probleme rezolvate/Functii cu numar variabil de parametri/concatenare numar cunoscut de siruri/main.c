#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
char * concatenare1(int n,...)
{
    va_list lista1,lista2;
    va_start(lista1,n);
    va_copy(lista2,lista1);

    int i,ls=0;
    char *s,*sir;
    for(i=0;i<n;i++)
    {
        s=va_arg(lista1,char *);
        ls+=strlen(s);
    }

    va_end(lista1);
    if(ls==0)return NULL;

    else
    {
        sir=(char *)malloc(ls+1);
        sir[0]=NULL;
        va_start(lista2,n);

        for(i=0;i<n;i++)
        {
            s=va_arg(lista2,char *);
            strcat(sir,s);
        }
        va_end(lista2);
        return sir;
        free(sir);
    }

}


void concatenare2(char **sir,int n,...)
{
    va_list lista1,lista2;
    va_start(lista1,n);
    va_copy(lista2,lista1);

    int i,ls=0;
    char *s;
    for(i=0;i<n;i++)
    {
        s=va_arg(lista1,char *);
        ls+=strlen(s);
    }

    va_end(lista1);
    if(ls==0)return NULL;

    else
    {
        (*sir)=(char *)malloc(ls+1);
        (*sir)[0]=NULL;
        va_start(lista2,n);

        for(i=0;i<n;i++)
        {
            s=va_arg(lista2,char *);
            strcat((*sir),s);
        }
        va_end(lista2);
    }

}
int main()
{
    char *sir;
    printf("%s\n",concatenare1(3,"bunica ","face ","bors"));
    concatenare2(&sir,4,"bunica ","e ","minunata"," super");
    printf("%s ",sir);
    free(sir);
    return 0;
}
