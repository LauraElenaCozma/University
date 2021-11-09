#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x;
    FILE *f1,*fneg,*fpoz;
    f1=fopen("numere_intregi.txt","a+");
    if(f1==NULL)
    {
        printf("Eroare la deschidere fisier");
        return 0;
    }
    fneg=fopen("negative.bin","wb+");
    if(f1==NULL)
    {
        printf("Eroare la deschidere fisier");
        return 0;
    }
    fpoz=fopen("pozitive.bin","wb+");
    if(f1==NULL)
    {
        printf("Eroare la deschidere fisier");
        return 0;
    }
    fscanf(f1,"%d\n",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f1,"%d\n",&x);
        if(x<0)fwrite(&x,sizeof(int),1,fneg);
        else if(x>0)fwrite(&x,sizeof(int),1,fpoz);
    }
    fseek(fneg,0,0);
    while(1)
    {
        int x=fread(&n,sizeof(int),1,fneg);
        if(x==0)break;
        else fprintf(f1,"%d ",n);
    }
    fprintf(f1,"\n");
    fseek(fpoz,0,0);
    while(1)
    {
        int x=fread(&n,sizeof(int),1,fpoz);
        if(x==0)break;
        else fprintf(f1,"%d ",n);
    }
    fclose(f1);
    fclose(fneg);
    fclose(fpoz);
    return 0;
}
