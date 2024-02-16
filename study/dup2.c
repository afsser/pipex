#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(int argc, char **argv)
{
	int fd;
	int	i;
	int	j;

	fd = open("dup2example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	i = 0;
	j = 1;
	while (i++ < argc - 1)
		printf("%s\n", argv[j++]);
	return (0);
}