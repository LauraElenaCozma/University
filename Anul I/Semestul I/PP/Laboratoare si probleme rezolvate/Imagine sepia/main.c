#include <stdio.h>

unsigned char minim(unsigned char x,unsigned char y)
{
    if(x<y)return x;
    return y;
}

void grayscale_image(char* nume_fisier_sursa,char* nume_fisier_destinatie)
{
   FILE *fin, *fout;
   unsigned int dim_img, latime_img, inaltime_img;
   unsigned char pRGB[3], header[54];

   printf("nume_fisier_sursa = %s \n",nume_fisier_sursa);

   fin = fopen(nume_fisier_sursa, "rb");
   if(fin == NULL)
   	{
   		printf("nu am gasit imaginea sursa din care citesc");
   		return;
   	}

   fout = fopen(nume_fisier_destinatie, "wb+");

   fseek(fin, 2, SEEK_SET);
   fread(&dim_img, sizeof(unsigned int), 1, fin);
   printf("Dimensiunea imaginii in octeti: %u\n", dim_img);

   fseek(fin, 18, SEEK_SET);
   fread(&latime_img, sizeof(unsigned int), 1, fin);
   fread(&inaltime_img, sizeof(unsigned int), 1, fin);
   printf("Dimensiunea imaginii in pixeli (latime x inaltime): %u x %u\n",latime_img, inaltime_img);

   //copiaza octet cu octet imaginea initiala in cea noua
	fseek(fin,0,SEEK_SET);
	unsigned char c;
	while(fread(&c,1,1,fin)==1)
	{
		fwrite(&c,1,1,fout);
	}
	fclose(fin);

	//calculam padding-ul pentru o linie
	int padding;
    if(latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    printf("padding = %d \n",padding);

	fseek(fout, 54, SEEK_SET);
	int i,j;
	for(i = 0; i < inaltime_img; i++)
	{
		for(j = 0; j < latime_img; j++)
		{
			//citesc culorile pixelului
			fread(pRGB, 3, 1, fout);
			//fac conversia in pixel gri
            unsigned int aux= 0.393*pRGB[2] + 0.769*pRGB[1] + 0.189*pRGB[0];
            if(aux>255)aux=255;
            pRGB[2]=(unsigned char)aux;
			aux =  0.349*pRGB[2] + 0.686*pRGB[1] + 0.168*pRGB[0];
			if(aux>255)aux=255;
            pRGB[1]=aux;
			aux =  0.272*pRGB[2] + 0.534*pRGB[1] + 0.131*pRGB[0];
			if(aux>255)aux=255;
            pRGB[0]=aux;

        	fseek(fout, -3, SEEK_CUR);
        	fwrite(pRGB, 3, 1, fout);
        	fflush(fout);
		}
		fseek(fout,padding,SEEK_CUR);
	}
	fclose(fout);
}


int main()
{
	char nume_img_sursa[] = "pepper.bmp";
	char nume_img_grayscale[] = "test_grayscale.bmp";
	grayscale_image(nume_img_sursa, nume_img_grayscale);
	return 0;
}

/*#include <stdio.h>
#include <stdlib.h>

unsigned char minim(unsigned char x,unsigned char y)
{
    if(x<y)return x;
    return y;
}

void sepia(char *intrare,char *iesire)
{
    FILE *fin,*fout;

    fin=fopen(intrare,"rb");
    fout=fopen(iesire,"wb");

    if(fin == NULL)
   	{
   		printf("nu am gasit imaginea sursa din care citesc");
   		return;
   	}

   	if(fout == NULL)
   	{
   		printf("nu am gasit imaginea sursa din care citesc");
   		return;
   	}

   	unsigned char r,g,b,r1,g1,b1;
   	unsigned int i,j,lat,lung;

   	//padding
   	fseek(fin,18,0);
   	fread(&lat,sizeof(unsigned int),1,fin);
   	fread(&lung,sizeof(unsigned int),1,fin);

   	printf("Latime imagine=%d",lat);
   	unsigned int padding=4-(3*lat)%4;
   	if(padding==4)padding=0;

    fseek(fin,0,0);
   	while(fread(&r,1,1,fin)==1)
    {
        fwrite(&r,1,1,fout);
    }

    fseek(fin,54,0);
    for(i=0;i<lung;i++)
    {
        for(j=0;j<lat;j++)
        {
            fread(&b,1,1,fin);
            fread(&g,1,1,fin);
            fread(&r,1,1,fin);
            printf("%d %d %d    ",r,g,b);
            r1=minim((unsigned char)(0.393 *r + 0.769 *g + 0.189 *b),255);
            g1=minim((unsigned char)(0.349 *r + 0.686 *g+ 0.168 *b),255);
            b1=minim((unsigned char)(0.272 *r + 0.534 *g + 0.131 *b) ,255);


            fwrite(&b1,1,1,fout);
            fwrite(&g1,1,1,fout);
            fwrite(&r1,1,1,fout);

            fflush(fout);


        }
        fseek(fin,padding,1);
        fseek(fout,padding,1);
    }

   	fclose(fin);
   	fclose(fout);
}


int main()
{
    sepia("imagine.bmp","tiger_sepia.bmp");
    return 0;
}
*/
