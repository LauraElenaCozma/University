#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int nota[13];
    float punctaj;
    char *nume;
    char *prenume;
}Student;


int litera(char c)
{
    if((c>= 'A' && c<='Z') || (c>= 'a' && c<='z')) return 1;
    return 0;
}


/*void citire(Student **v,int *n,char *numeFisier)
{
    FILE *f;

    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare fisier");
        return ;
    }
    fscanf(f,"%d",n);

    (*v)=(Student *)malloc((*n)*sizeof(Student));
    if((*v)==NULL)
    {
        printf("Eroare alocare");
        return ;
    }
    int i;
    for(i=0;i<*n;i++)
    {

           char c;
           (*v)[i].nume=NULL;
           char *aux;
           int lung=1;
           c=fgetc(f);
           while(c!=' ')
           {
               lung++;
               aux=(char *)realloc((*v)[i].nume,lung*sizeof(char));
               if(aux==NULL)
               {
                   printf("Eroare");
                   return -2;
               }

               (*v)[i].nume=aux;
               (*v)[i].nume[lung-1]='\0';
               (*v)[i].nume[lung-2]=c;
               c=fgetc(f);
           }

           (*v)[i].prenume=NULL;
           lung=1;
           c=fgetc(f);
           while(c!=' ')
           {
               lung++;
               aux=(char *)realloc((*v)[i].prenume,lung*sizeof(char));
               if(aux==NULL)
               {
                   printf("Eroare");
                   return -2;
               }

               (*v)[i].prenume=aux;
               (*v)[i].prenume[lung-1]='\0';
               (*v)[i].prenume[lung-2]=c;
               c=fgetc(f);
           }


          //printf("%s %s ",(*v)[i].nume,(*v)[i].prenume);
           int j;

           float s=0;
           for(j=0;j<12;j++)
            {
                fscanf(f,"%d",&(*v)[i].nota[j]);
                s+=(*v)[i].nota[j];
                (*v)[i].punctaj=60*(s/12.0);
                //printf(" %d ",(*v)[i].nota[j]);
            }

    }

    fclose(f);
}
 */

void citire(Student **v,int *n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
        return ;

    fscanf(f,"%d",n);

    (*v)=(Student *)malloc((*n)*sizeof(Student));


    int i;
    char nume[30],prenume[30];

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%s%s",nume,prenume);
        int j;
        float s=0;
        for(j=0;j<12;j++)
           {
               fscanf(f,"%d",&(*v)[i].nota[j]);
               s+=(*v)[i].nota[j];
           }

        s/=12.0;
        s*=60;
        (*v)[i].punctaj=s;
       int lnume=strlen(nume)+1;
       (*v)[i].nume=(char *)malloc(lnume*sizeof(char));
       int lprenume=strlen(prenume)+1;
       (*v)[i].prenume=(char *)malloc(lprenume*sizeof(char));

       strcpy((*v)[i].nume,nume);
       strcpy((*v)[i].prenume,prenume);

    }
    fclose(f);
}


void afisare(Student *v,int n,char *numeFisier)
{

    FILE *f;

    f=fopen(numeFisier,"w");

    if(f==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    int i;
    for(i=0;i<n;i++)
    {
        fprintf(f,"%s %s ",v[i].nume,v[i].prenume);
        int j;
        for(j=0;j<12;j++)
            fprintf(f,"%d ",v[i].nota[j]);
        fprintf(f,"medie=%f",v[i].punctaj);
        fprintf(f,"\n");
    }
    fprintf(f,"\n");

}

int cmpDescrescator(const char *a,const char *b)
{
    Student va=*(Student *)a;
    Student vb=*(Student *)b;

    if(va.punctaj>vb.punctaj)return -1;
    if(va.punctaj<vb.punctaj)return 1;
    if(va.nota[3]>vb.nota[3])return -1;
    if(va.nota[3]<vb.nota[3])return 1;
    return 0;
}

void sortare(Student *v,int n)
{
    qsort(v,n,sizeof(Student),cmpDescrescator);
}


void camine(Student *v,int n,char *groza,char *koga,char *constructii)
{
    FILE *f1,*f2,*f3;
    f1=fopen(groza,"w");

    if(f1==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    f2=fopen(koga,"w");

    if(f2==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    f3=fopen(constructii,"w");

    if(f3==NULL)
    {
        printf("Eroare fisier");
        return ;
    }

    int lg=15,lc=3,k=0;
    while(lg!=0 && k!=n)
    {
        fprintf(f1,"%s %s\n",v[k].nume,v[k].prenume);
        lg--;
        k++;
    }

    while(lc!=0 && k!=n)
    {
        fprintf(f2,"%s %s\n",v[k].nume,v[k].prenume);
        lc--;
        k++;
    }

    while(k!=n)
    {
        fprintf(f3,"%s %s\n",v[k].nume,v[k].prenume);
        k++;
    }

}
int main()
{
    int n;
    Student *v;
    citire(&v,&n,"student.txt");
   // sortare(v,n);
    afisare(v,n,"punctaje.txt");
    //camine(v,n,"grozavesti.txt","kogalniceanu.txt","constructii.txt");
    free(v);


    return 0;
}
