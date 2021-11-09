#include <stdio.h>
#include <stdlib.h>
int anagrame(char *x,char *y)
{
    if(!x[0] && !y[0])return 1;
    if(strlen(x)!=strlen(y))return 0;

    char *p=strchr(y,x[0]);
    if(p==NULL)return 0;
    strcpy(p,p+1);
    return anagrame(x+1,y);
}

void citire(char *fintrare)
{
    char *w;
    w=malloc(1000);
    FILE *fin;
    fin=fopen(fintrare,"r");

    fscanf(fin,"%s",w);
    w=realloc(w,strlen(w)+1);
    char linie[1001];
    while(fgets(linie,1001,fin)!=NULL)
    {
        if(linie[strlen(linie)-1]=='\n')
            linie[strlen(linie)-1]='\0';

        char *p;
        p=strtok(linie," ?!,.:;");
        while(p)
        {
            char *y;
            y=malloc(strlen(p)+1);
            strcpy(y,p);
            if(anagrame(w,y))printf("%s\n",p);
            p=strtok(NULL," ?!,.:;");
        }
    }

    fclose(fin);

}


int main()
{
    citire("f.in");
    return 0;
}
