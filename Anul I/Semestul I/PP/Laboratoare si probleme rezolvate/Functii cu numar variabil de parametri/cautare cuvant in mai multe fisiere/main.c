#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void caut_cuv(char *cuv,char *Fiesire,...)
{
    va_list lista;
    va_start(lista,Fiesire);
    char *nume;

    FILE *fout;
    fout=fopen(Fiesire,"w");
    int nrf=1;

    while((nume=va_arg(lista,char *))!=NULL)
    {
        FILE *f;
        f=fopen(nume,"r");

        char linie[1001];
        int nr=1,ok=0;

        while(fgets(linie,1001,f)!=NULL)
        {
            if(linie[strlen(linie)-1]=='\n')
                linie[strlen(linie)-1]='\0';

            char *p;
            p=strtok(linie," ");
            while(p)
            {
                if(strcmp(cuv,p)==0)
                    {fprintf(fout,"%d %d\n",nrf,nr);ok=1;}
                p=strtok(NULL," ");
            }
            nr++;
        }
        if(ok==0)fprintf(fout,"%d Nu exista",nrf);
        nrf++;
        fclose(f);

    }
    va_end(lista);
    fclose(fout);
}
int main()
{
    caut_cuv("mama","iesire.out","f1.in","f2.in",NULL);
    return 0;
}
