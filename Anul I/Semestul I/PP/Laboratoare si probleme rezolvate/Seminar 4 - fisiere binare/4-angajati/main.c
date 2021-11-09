#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int varsta;
    int salariu;
    char cnp[14];
    char *nume;

}Angajat;
///NU MERGE

/*void citire(char *numeBin,int *n,Angajat **v)
{
    FILE *f;
    f=fopen(numeBin,"wb");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    scanf("%d",n);
    //fflush(stdin);
    (*v)=(Angajat *)malloc((*n)*sizeof(Angajat));

    int i;
    for(i=0;i<(*n);i++)
        {
            scanf("%d%d%s%s",&(*v+i)->varsta,&(*v+i)->salariu,(*v+i)->cnp,(*(*v+i)).nume);
            printf("\n    %s\n",(*v+i)->nume);
          /*  fwrite(&(*v+i)->varsta,sizeof(int),1,f);
            fwrite(&(*v+i)->salariu,sizeof(int),1,f);
            fwrite(&(*v+i)->cnp,sizeof((*v+i)->cnp),1,f);
            int dim=strlen(*((*v+i)->nume))+1;
            //fwrite(&dim,sizeof(int),1,f);
            //fwrite(&(*v+i)->nume,dim,1,f);

        }

    fclose(f);
}*/


void citire(char *numeBin,int *n,Angajat v[])
{
    FILE *f;
    f=fopen(numeBin,"wb");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }

    scanf("%d",n);
    //fflush(stdin);


    int i;
    for(i=0;i<(*n);i++)
        {
            scanf("%d%d",&v[i].varsta,&v[i].salariu);
            //fflush(stdin);

            scanf("%s%s",&v[i].cnp,v[i].nume);
            printf("\n    %s\n",*(v[i].nume));
          /*  fwrite(&(*v+i)->varsta,sizeof(int),1,f);
            fwrite(&(*v+i)->salariu,sizeof(int),1,f);
            fwrite(&(*v+i)->cnp,sizeof((*v+i)->cnp),1,f);
            int dim=strlen(*((*v+i)->nume))+1;
            //fwrite(&dim,sizeof(int),1,f);
            //fwrite(&(*v+i)->nume,dim,1,f);*/

        }

    fclose(f);
}

int main()
{
    Angajat v[100];
    int n;
    citire("angajat.bin",&n,v);
    return 0;
}
