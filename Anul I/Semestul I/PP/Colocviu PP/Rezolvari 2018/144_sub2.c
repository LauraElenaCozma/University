#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//subpunct a
typedef struct
{
    long long int cnp;
    char *nume,*prenume;
    int varsta,vechime;
    float salariu;
}Angajat;
//subpunct b
int aflu_cifra(long long int x,int nr)
{//aflu cifra de pe pozitia nr
    nr=13-nr;
    while(nr!=1)
    {
        x/=10;
        nr--;
    }
    return x%10;
}

void actualizare(Angajat *a)
{
    (*a).vechime++; //creste vechimea angajatului cu un an
    //calculeaza varsta
    int v=0;
    int cif0=aflu_cifra((*a).cnp,0);
    int cif1=aflu_cifra((*a).cnp,1);
    int cif2=aflu_cifra((*a).cnp,2);
    if(cif0==1 || cif0==2)
    {
        v=19*100;
        v+=(cif1*10);
        v+=cif2;
    }
    else if(cif0==5 || cif0==6)
    {
         v=20*100;
         v+=(cif1*10);
         v+=cif2;
    }
   v=2018-v;
   (*a).varsta=v;

   //cresterea salariului
   if(v>=18 && v<=30)
       (*a).salariu=(105.0)/100*(*a).salariu;
   else if(v>=31 && v<=50  && (*a).vechime<=15)
            (*a).salariu=(115.0)/100*(*a).salariu;
        else if((*a).vechime>=20)
            (*a).salariu=(125.0)/100*(*a).salariu;

}
//subpunct c
int cnp_valid(long long cnp)
{
    char v[]="279146358279";

    int i,s=0;
    for(i=0;i<=11;i++)
    {
        int cifi=aflu_cifra(cnp,i);
        s+=(cifi*(v[i]-'0'));
    }
    int r=s%11;
    if(r==10)r=1;
    int cif12=aflu_cifra(cnp,12);
    if(r==cif12)return 1;
    return 0;
}

//subpunct d
void eliminare(Angajat **v,int *n)
{
    int i;
    for(i=0;i<*n;i++)
        if(!cnp_valid((*v)[i].cnp))
    {
        int j;
        for(j=(*n)-1;j>i;j--)
            (*v)[j-1]=(*v)[j];
        i--;
        (*n)--;
    }
    Angajat *aux;
    aux=(Angajat *)realloc((*v),(*n)*sizeof(Angajat));
    if(aux==NULL)
        return ;
    (*v)=aux;
}

void citire(char *numeFisier,Angajat **v,int *n)
{
    //functie care citeste elementele unui vector de timp structura Angajat
    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)return ;
    fscanf(f,"%d",n);
    (*v)=(Angajat *)malloc((*n)*sizeof(Angajat));
    if((*v)==NULL)
    {
        printf("Eroare alocare spatiu");
        return ;
    }

    int i;
    for(i=0;i<*n;i++)
    {
        (*v)[i].nume=malloc(30*sizeof(char));
        (*v)[i].prenume=malloc(30*sizeof(char));
        fscanf(f,"%lld %s %s",&(*v)[i].cnp,(*v)[i].nume,(*v)[i].prenume);

        int lungn=strlen((*v)[i].nume);
        int lungp=strlen((*v)[i].prenume);

        //realocam spatiu pentru nume si prenume in functie de lungimea celor citite pentru a nu ocupa memorie in plus
        char *aux;
        aux=(char *)realloc((*v)[i].nume,(lungn+2)*sizeof(char));
        if(aux==NULL)
            {
        printf("Eroare alocare spatiu");
        return ;
            }
        (*v)[i].nume=aux;
        aux=(char *)realloc((*v)[i].prenume,(lungp+2)*sizeof(char));
        if(aux==NULL)
           {
            printf("Eroare alocare spatiu");
            return ;
            }
        (*v)[i].prenume=aux;
        fscanf(f,"%d%f%d",&(*v)[i].varsta,&(*v)[i].salariu,&(*v)[i].vechime);


    }

    fclose(f);
}


void afisare(Angajat *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%lld %s %s %d %.2f %d\n",v[i].cnp,v[i].nume,v[i].prenume,v[i].varsta,v[i].salariu,v[i].vechime);
    printf("\n\n");

}

int cmpCrescator(const void *a,const void *b)
{
    Angajat va=*(Angajat *)a;
    Angajat vb=*(Angajat *)b;
    if(va.varsta<vb.varsta)return -1;
    if(va.varsta>vb.varsta)return 1;
    //daca varstele sunt egale
    if(va.salariu>vb.salariu)return -1;
    if(va.salariu<vb.salariu)return 1;
    return 0;
}

void sortare(Angajat *v,int n)
{
    qsort(v,n,sizeof(Angajat),cmpCrescator);
}
int main()
{
    Angajat *v;
    int n;
    citire("angajati.txt",&v,&n);

    eliminare(&v,&n);

    int i;
    for(i=0;i<n;i++)
        actualizare(&v[i]);

    sortare(v,n);
    afisare(v,n);

   for(i=0;i<n;i++)
   {
       free(v[i].nume);
       free(v[i].prenume);
   }
   free(v);

    return 0;
}
