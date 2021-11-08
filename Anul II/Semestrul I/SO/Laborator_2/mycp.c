#include <stdio.h>

#include <string.h>

#include <unistd.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int narg, char **argv)
{

if(narg < 3)
{
fprintf(stderr , "Invalid number of arguments\n");
return -1;
}


int fd1=open(argv[1],O_RDONLY,0644);
int fd2=open(argv[2],O_WRONLY|O_CREAT,0644);

if(fd1 < 0 || fd2 < 0)
{
fprintf(stderr , "Error at opening the file\n");
return -1;
}

char buf[512];
int bread , btoread=512 , bwritten , btowrite,totalbwritten;
while((bread=read(fd1,buf,btoread))>0)
{
	totalbwritten = 0;
	while((bwritten=write(fd2,buf + totalbwritten , bread))>0)
	{
		bread-=bwritten;//cati bytes au ramas de scris
		totalbwritten += bwritten;
	}
}
close(fd1);
close(fd2);
return 0;

}
