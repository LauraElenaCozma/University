#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
write(1,"Hello, World!",strlen("Hello, World!"));
return 0;
}
