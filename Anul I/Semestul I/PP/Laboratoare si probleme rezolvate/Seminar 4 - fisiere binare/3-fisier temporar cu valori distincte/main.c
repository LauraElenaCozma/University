#include <stdio.h>
#include <stdlib.h>



void distinct(int *n,char *numeText)
{
    FILE *ft;
    ft=tmpfile();

    scanf("%d",n);

    int i,x;
    scanf("%d",&x);
    fwrite(&x,sizeof(int),1,ft);

    for(i=1;i<*n;i++)
    {
        scanf("%d",&x);

        fseek(ft,0,0);
        int ok=1;
        int y;
        while(ok==1 && fread(&y,sizeof(int),1,ft)==1)
        {
            if(x==y)ok=0;
        }

        if(ok)//nu s-a gasit nr in fisier
        {
            fwrite(&x,sizeof(int),1,ft);
        }

    }


    //fflush(ft);
    fseek(ft,0,0);

    FILE *fout;
    fout=fopen(numeText,"w");

    if(fout==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }


    while(fread(&x, sizeof(int),1 , ft)==1)
        fprintf(fout,"%d ",x);

    fclose(fout);
    fclose(ft);
}

int main()
{
    int n;
    distinct(&n,"f.in");
    return 0;
}
