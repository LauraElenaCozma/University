#include <stdio.h>
#include <stdlib.h>

void binar2text(char *numeBinar,char *numeText)
{
    FILE *fin,*fout;

    fin=fopen(numeBinar,"rb");
    fout=fopen(numeText,"w");

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    if(fout==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    int x;
    while(fread(&x, sizeof(int),1 , fin)==1)
        fprintf(fout,"%d ",x);

    fclose(fin);
    fclose(fout);
}

void text2binar(char *numeText,char *numeBinar)
{
    FILE *fin,*fout;

    fin=fopen(numeText,"r");
    fout=fopen(numeBinar,"wb");

    if(fin==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    if(fout==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    int x;
    while(fscanf(fin,"%d",&x)==1)
        fwrite(&x,sizeof(int),1,fout);

    fclose(fin);
    fclose(fout);
}

int main()
{
    text2binar("f1.txt","f.bin");
    binar2text("f.bin","f2.txt");
    return 0;
}
