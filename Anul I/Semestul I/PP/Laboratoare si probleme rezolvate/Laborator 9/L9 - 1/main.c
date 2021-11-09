#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int varsta,salariu;
    char *nume;
    char cnp[14];
}Angajat;
/*
void citire(Angajat **v,int *n,char *numeFisier)
{
    FILE *f=fopen(numeFisier,"r");

    if(f==NULL)
      {
          printf("1 Eroare");return ;
      }
    (*v)=malloc(sizeof(Angajat));

    if(*v==NULL)
        { printf("2 Eroare");return ;}
    (*n)=0;
    char c;
    while(fscanf(f,"%s",(*v)[(*n)].cnp)==1)
    {
       /* char c;
        int lung=0;
        (*v)[*n].nume=NULL;

        while((c=fgetc(f))!=' ')
        {
            printf(" --%c-- ",c);
            lung++;
            char *aux;
            aux=(char *)realloc((*v)[*n].nume,(lung+1)*sizeof(char));
            if(aux!=NULL)
                (*v)[*n].nume=aux;
            else
            {
                printf("eroare");
                return ;
            }
            (*v)[*n].nume[lung]='\0';
            (*v)[*n].nume[lung-1]=c;
        }

        printf("%s  %s\n",(*v)[*n].cnp,(*v)[*n].nume);

        (*v)[*n].nume=malloc(40*sizeof(char));
        if((*v)[*n].nume==NULL)
        {
            { printf("3 Eroare");return ;}
        }
        fscanf(f,"%s %d %d",(*v)[(*n)].nume,&(*v)[(*n)].varsta,&(*v)[(*n)].salariu);
        int lung=strlen((*v)[(*n)].nume);
       printf("Lung %d\n",lung);
        char *aux3;
        aux3=realloc((*v)[(*n)].nume,lung*sizeof(char));
        if(aux3!=NULL)
            (*v)[(*n)].nume=aux3;
       // printf("%s %s %d %d\n",(*v)[(*n)].cnp,(*v)[(*n)].nume,(*v)[(*n)].varsta,(*v)[(*n)].salariu);
        (*n)++;
        char *aux2;
        aux2=(Angajat *)realloc((*v),((*n)+1)*sizeof(Angajat));
        if(aux2!=NULL)
            (*v)=aux2;
        else printf("4 Eroare");

    }
    fclose(f);
}


void toBinar(Angajat *v,int n,char *numeBinar)
{
    FILE *f=fopen(numeBinar,"wb");

    int i;
    for(i=0;i<n;i++)
    {
        //printf("%s %s %d %d\n",v[i].cnp,v[i].nume,v[i].varsta,v[i].salariu);
        fwrite(v[i].cnp,14*sizeof(char),1,f);
        int lung=strlen(v[i].nume);
        printf("\n--%d--\n",lung);
        fwrite(&lung,sizeof(int),1,f);
        fwrite(v[i].nume,lung*sizeof(char ),1,f);
        fwrite(&v[i].varsta,sizeof(int),1,f);
        fwrite(&v[i].salariu,sizeof(int),1,f);
    }

    fclose(f);
}

void binar2text(char *numeBinar)
{
    FILE *f=fopen(numeBinar,"rb");
    char cnp[14];
    while(fread(cnp,14*sizeof(char),1,f)==1)
    {
        char*nume;
        int salariu,varsta,lung;
       // printf("\n%d   ",cnp);
        fread(&lung,sizeof(int),1,f);
        printf("\n%d   ",lung);
        nume=(char *)malloc(lung*sizeof(char));
        fread(nume,lung*sizeof(char),1,f);
        printf("\n%s   ",nume);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);
        printf("%s %s %d %d \n",cnp,nume,varsta,salariu);
    }
    fclose(f);
}


void caut_cnp(char *binar,char cnp_cautat[])
{
    FILE *f=fopen(binar,"rb");
    char cnp[14];
    int ok=0;
    while(fread(cnp,14*sizeof(char),1,f)==1)
    {
        char*nume;
        int salariu,varsta,lung;
        fread(&lung,sizeof(int),1,f);
        nume=(char *)malloc(lung*sizeof(char));
        fread(nume,lung*sizeof(char),1,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);
        if(stricmp(cnp,cnp_cautat)==0)
        {
            ok=1;
            printf("%s %s %d %d \n",cnp,nume,varsta,salariu);
            break;
        }


    }
    if(ok==0)printf("Nu exista");
    fclose(f);
}
*/


void citire(Angajat **v,int *n,char *nume)
{
    FILE *f;
    f=fopen(nume,"r");

    if(f==NULL)
    {
        printf("Eroare");
        return ;
    }

    (*v)=NULL;
    (*n)=0;//inital avem 0 elemente in vector

    char cnp1[14];
    while(fscanf(f,"%s ",cnp1)!=EOF)
    {
        (*n)++;
        Angajat *aux;
        aux=(Angajat *)realloc((*v),(*n)*sizeof(Angajat));

        if(aux!=NULL)
            (*v)=aux;
        else printf("Eroare");

        strcpy((*v)[(*n)-1].cnp,cnp1);


        (*v)[(*n)-1].nume=(char *)malloc(50*sizeof(char));
        fscanf(f,"%s %d %d",(*v)[(*n)-1].nume,&(*v)[(*n)-1].varsta,&(*v)[(*n)-1].salariu);

        //printf("%s %s %d %d\n",(*v)[(*n)-1].cnp,(*v)[(*n)-1].nume,(*v)[(*n)-1].varsta,(*v)[(*n)-1].salariu);
        int lung=strlen((*v)[(*n)-1].nume);
        char *aux1;
        aux1=(char *)realloc((*v)[(*n)-1].nume,(lung+1)*sizeof(char));

        if(aux1!=NULL)
            (*v)[(*n)-1].nume=aux1;
    }

    fclose(f);
}


void toBinar(Angajat *v,int n,char *nume)
{
   FILE *f=fopen(nume,"wb");

   if(f==NULL)
    return ;
   int i;
   for(i=0;i<n;i++)
   {
       fwrite(v[i].cnp,14*sizeof(char),1,f);
       int lung=strlen(v[i].nume);
       fwrite(&lung,sizeof(int),1,f);
       fwrite(v[i].nume,(lung+1)*sizeof(char),1,f);
       fwrite(&v[i].varsta,sizeof(int),1,f);
       fwrite(&v[i].salariu,sizeof(int),1,f);
   }
   fclose(f);
}

void binar2text(char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"rb");

    if(f==NULL){printf("Eroare");return;}

    int lung,salariu,varsta;
    char cnp[14],*nume;

    while(fread(cnp,14*sizeof(char),1,f)==1)
    {
        //printf("%s ",cnp);
        fread(&lung,sizeof(int),1,f);
        //printf("%d ",lung);

        nume=(char *)malloc((lung+1)*sizeof(char));
        fread(nume,(lung+1)*sizeof(char),1,f);
        //printf("%s \n",nume);
        fread(&varsta,sizeof(int),1,f);
        //printf("%d ",varsta);
        fread(&salariu,sizeof(int),1,f);
        //printf("%d \n",salariu);
        printf("%s %s %d %d\n",cnp,nume,varsta,salariu);
    }

    fclose(f);
}


void cunosc_cnp(char *numeFisier,char cnp_cautat[])
{
    FILE *f;
    f=fopen(numeFisier,"rb");

    if(f==NULL){printf("Eroare");return;}

    int lung,salariu,varsta,ok=0;
    char cnp[14],*nume;

    while(fread(cnp,14*sizeof(char),1,f)==1)
    {
        fread(&lung,sizeof(int),1,f);
        nume=(char *)malloc((lung+1)*sizeof(char));
        fread(nume,(lung+1)*sizeof(char),1,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);
        if(strcmp(cnp_cautat,cnp)==0)
           {
               ok=1;
               printf("%s %s %d %d\n",cnp,nume,varsta,salariu);
               break;
           }
    }
    if(ok==0)printf("Nu exista");
    fclose(f);
}


void adaug_angajat(char *numeFisier,Angajat *a)
{
    FILE *f;
    f=fopen(numeFisier,"ab");

    if(f==NULL){printf("Eroare");return;}
    (*a).nume=(char *)malloc(50*sizeof(char));
    scanf("%s %s %d %d",(*a).cnp,(*a).nume,&(*a).varsta,&(*a).salariu);
    fwrite((*a).cnp,14*sizeof(char),1,f);
    int lung=strlen((*a).nume);
    fwrite(&lung,sizeof(int),1,f);
    fwrite((*a).nume,(lung+1)*sizeof(char),1,f);
    fwrite(&(*a).varsta,sizeof(int),1,f);
    fwrite(&(*a).salariu,sizeof(int),1,f);

    fclose(f);
}

void stergere(char *numeFisier,char cnps[])
{
    FILE *f;
    f=fopen(numeFisier,"rb");
    FILE *faux;
    faux=fopen("tmp_auxiliar.bin","wb");

    if(f==NULL){printf("Eroare");return;}

    int lung,salariu,varsta,ok=0;
    char cnp[14],*nume;

    while(fread(cnp,14*sizeof(char),1,f)==1)
    {

        fread(&lung,sizeof(int),1,f);
        nume=(char *)malloc((lung+1)*sizeof(char));
        fread(nume,(lung+1)*sizeof(char),1,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);
        if(strcmp(cnps,cnp)!=0)
           {

               fwrite(cnp,14*sizeof(char),1,faux);
               fwrite(&lung,sizeof(int),1,faux);
               fwrite(nume,(lung+1)*sizeof(char),1,faux);
               fwrite(&varsta,sizeof(int),1,faux);
               fwrite(&salariu,sizeof(int),1,faux);
               //printf("%s %s %d %d\n",cnp,nume,varsta,salariu);

           }
        else ok=1;
    }
    if(ok==0)printf("Nu exista\n");
    fclose(faux);
    fclose(f);

    remove(numeFisier);
    rename("tmp_auxiliar.bin",numeFisier);



}


void afisare(Angajat *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %s %d %d\n",v[i].cnp,v[i].nume,v[i].varsta,v[i].salariu);
}

int main()
{
    Angajat *v,a;
    int n;
    citire(&v,&n,"angajati.in");

    afisare(v,n);
    printf("\n\n");
    toBinar(v,n,"angajati.bin");
   // binar2text("angajati.bin");
    //printf("\n\n\n");
    //cunosc_cnp("angajati.bin","2398564398756");

    //adaug_angajat("angajati.bin",&a);
    //binar2text("angajati.bin");
    //printf("\n\n\n");

    stergere("angajati.bin","9214864298464");
    binar2text("angajati.bin");


    int i;
    for(i=0;i<n;i++)
    free(v[i].nume);
    free(v);
    return 0;
}
