#include <stdio.h>
#include <stdlib.h>

void conversie(FILE *fin,FILE *fout)
{
    fin=fopen("f.bin","rb+");
    fout=fopen
}

int main()
{
    FILE *f;
    f=fopen("f.bin","wb+");
    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return 0;

    }
    else
    {
        int m,i,x;
        srand(time(nullptr));
        scanf("%d",&m);
        for(i=1;i<=m;i++)
        {
            x=rand()%(2*n+1);
            x-=n;
            fwrite(&x,sizeof(int),1,f);
        }
    }

    fclose(f);
    return 0;
}
