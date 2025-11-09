#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
int fd = open("Makefile", O_RDONLY);
	
printf("the number of file is : %i ", fd);
}
