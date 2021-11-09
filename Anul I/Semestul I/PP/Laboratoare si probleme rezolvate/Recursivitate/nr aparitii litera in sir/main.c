#include <stdio.h>
#include <stdlib.h>

int aparitii(char *s,char c)
{
    if(s[0]=='\0')
        return 0;
    else
    {
        if(c==s[0])return 1+aparitii(s+1,c);
        else return aparitii(s+1,c);
    }
}

int main()
{
    printf("%d",aparitii("anaconda",'o'));
    return 0;
}
