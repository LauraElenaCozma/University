#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fout;
    fout=fopen("f.bin","w+b");
    if(fout==NULL)
    {
        printf("Eroare la deschidere");
        return 0;
    }
    int n,v[100];
    scanf("%d",&n);
    int i;
    for(i=0;i<n;i++)
        scanf("%d",&v[i]);
    fwrite(&n,sizeof(int),1,fout);
    fwrite(&v[0],sizeof(int),n,fout);
   // fwrite(&n,sizeof(int),1,fout);
    fseek(fout,0,0);
    while(1)
    {
        int x=fread(&n,sizeof(int),1,fout);
        if(x==0)break;
        printf("%d ",n);
    }
    return 0;
}
