#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char nume[21];
    char prenume[21];
    float nota;


}Student;

int creare(FILE *f,int n)
{
    f=fopen("f.bin","wb");

    if(f==NULL)
        return -1;

    int i;
    Student s;
    for(i=1;i<=n;i++)
        {
            scanf("%d%s%s%f",&s.id,s.nume,s.prenume,&s.nota);
            fwrite(&s,sizeof(Student),1,f);
        }
    fclose(f);
}

void afisare(FILE *fb,FILE *ft)
{
    fb=fopen("f.bin","rb");

    if(fb==NULL)
            return -1;

    ft=fopen("f.in","w");

    if(ft==NULL)
            return -1;


    Student s;
    while(fread(&s,sizeof(Student),1,fb)==1)
    {
        printf("%d %s %s %f",s.id,s.nume,s.prenume,s.nota);
        printf("\n");
    }


    fclose(fb);
    fclose(ft);
}


int modificare(FILE *f,int id_cautat,float nota_noua)
{
    f=fopen("f.bin","rb+");

    if(f==NULL)
        return -1;


    Student s;
    while(fread(&s,sizeof(Student),1,f)==1)
    {
        if(s.id==id_cautat)
        {
            fseek(f,(-1)*sizeof(float),1);
            fwrite(&nota_noua,sizeof(float),1,f);
            fclose(f);
            return ;
        }
    }

    fclose(f);
}

void copiere(FILE *f1,FILE *f2)
{
    f1=fopen("f.bin","rb");
    f2=fopen("aux.bin","wb");
    Student s;
    while(fread(&s,sizeof(Student),1,f1)==1)
        fwrite(&s,sizeof(Student),1,f2);

    fclose(f1);
    fclose(f2);
}


void adaugare(FILE * f,Student s)
{
    f=fopen("f.bin","ab");
    fwrite(&s,sizeof(Student),1,f);
    fclose(f);
}
int main()
{
    FILE *fb,*ft;
    int n;
    scanf("%d",&n);
    creare(fb,n);
    afisare(fb,ft);
    modificare(fb,2,9);
    /*Student s;
    scanf("%d%s%s%f",&s.id,s.nume,s.prenume,&s.nota);
    adaugare(fb,s);*/
    afisare(fb,ft);
    return 0;
}
