#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE *fin,*fout;

    fin=fopen("tiger.bmp","rb");

    if(fin==NULL)
        return 0;

    fout=fopen("tiger_modified.bmp","wb");

    if(fout==NULL)
        return 0;

    short int x,b,g,r;
    int i;

    for(i=0;i<54;i++)
    {
        fread(&x,1,1,fin);
        fwrite(&x,1,1,fout);
    }

    while(1)
    {

        fread(&b,1,1,fin);
        fread(&g,1,1,fin);
        fread(&r,1,1,fin);

        b=255-b;
        g=255-g;
        r=255-r;

        fwrite(&b,1,1,fout);
        fwrite(&g,1,1,fout);
        fwrite(&r,1,1,fout);

        fflush(fout);

        if(feof(fin))break;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
