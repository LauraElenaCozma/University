#include <stdio.h>
#include <stdlib.h>

int * citire(FILE *in,int *n)
{
    //citirea unui polinom
    int *a,i;
    fscanf(in,"%d",n);
    a=(int *)malloc((*n+1)*sizeof(int));
    for(i=0;i<=(*n);i++)
        fscanf(in,"%d",&a[i]);
    return a;
}


int valoare(int *a,int n)
{
    //calculeaza valoarea polinomului a in pct t
    int s=a[0],i,x,t;
    printf("Punctul in care calculati polinomul este:");
    scanf("%d",&t);
    x=t;
    for(i=1;i<=n;i++)
    {
        s+=a[i]*x;
        x*=t;
    }
    return s;
}

int * suma(int *gr,int *p,int *q,int n,int m)
{
    //functia calculeaza suma dintre polinoamele p si q
    (*gr)=(n>m)?n:m;
    int i,*r;
    r=(int *)malloc((*gr+1)*sizeof(int));
    if(n>m)
    {
        for(i=0;i<=n;i++)
            if(i<=m)r[i]=p[i]+q[i];
            else r[i]=p[i];

    }
    else
    {
        for(i=0;i<=m;i++)
            if(i<=n)r[i]=p[i]+q[i];
            else r[i]=q[i];
    }

    return r;

}

void afisare(int *v,int n)
{
    //afisarea unui polinom
    int i;
    for(i=0;i<=n;i++)
        /*{ //afisare tip polinom
            if(v[i]!=0)
            {
                if(v[i]<0)printf("(%d)*x^%d+",v[i],i);
                else printf("%d*x^%d+",v[i],i);
            }

        }
    if(v[n]!=0)
            {
                if(v[n]<0)printf("(%d)*x^%d",v[n],n);
                else printf("%d*x^%d",v[n],n);
            }
        */
        printf("%d ",v[i]);
        printf("\n");

}

int * produs(int *gr,int *p,int *q,int n,int m)
{
    //calculeaza produsul a 2 polinoame
    (*gr)=n+m;
    int *r,i,j;
    r=(int *)malloc((*gr+1)*sizeof(int));
    for(i=0;i<=(*gr);i++)
        r[i]=0;
    for(i=0;i<=n;i++)
        for(j=0;j<=m;j++)
         r[i+j]+=p[i]*q[j];
    return r;
}
int main()
{
    FILE *in=fopen("f.in","r");
    int *a,n,*p,*q,*r,m,gr,opt;
    printf("\nOptiunea dumnevoastra este(se va insera numarul exercitiului de la 5 la 7):");
    scanf("%d",&opt);
    switch(opt)
        {
    case 5:
           // int *a,n;
            a=citire(in,&n);
            printf("Valoarea polinomului este: %d",valoare(a,n));
            break;
    case 6:
           // int *p,*q,*r,n,m,gr;
            p=citire(in,&n);
            q=citire(in,&m);
            r=suma(&gr,p,q,n,m);
            afisare(r,gr);
            break;
    case 7:
           // int *p,*q,*r,n,m,gr;
            p=citire(in,&n);
            q=citire(in,&m);
            r=produs(&gr,p,q,n,m);
            afisare(r,gr);
            break;
        }
    return 0;
}
