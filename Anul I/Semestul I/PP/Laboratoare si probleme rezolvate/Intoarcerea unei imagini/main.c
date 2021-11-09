#include <stdio.h>
#include <stdlib.h>

int intoarcere(FILE * fin,FILE *fout)
{
    fin=fopen("pepper.bmp","rb");

    if(fin==NULL)
        return -1;
    fout=fopen("pepper_modif.bmp","wb");

    if(fout==NULL)
        return -1;

    int i;
    unsigned char x,r,g,b;
    for(i=0;i<54;i++)
    {
        fread(&x,1,1,fin);
        fwrite(&x,1,1,fout);
    }
    fseek(fin,-1,2);
    int p=ftell(fin);
    while(p!=0)
    {
        printf("%d ",p);
        fread(&b,1,1,fin);
        fseek(fin,-2,1);
        fread(&g,1,1,fin);
        fseek(fin,-2,1);
        fread(&r,1,1,fin);
        fseek(fin,-2,1);

        write(&b,1,1,fout);
        write(&g,1,1,fout);
        write(&r,1,1,fout);

        p=ftell(fin);
    }
    fclose(fin);
    fclose(fout);
}


int main()
{
    FILE *fin,*fout;
    intoarcere(fin,fout);
    return 0;
}
