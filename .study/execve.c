#include <unistd.h>
#include <stdio.h>
 
int main()
{
	char *args[3];
 
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);  // INTERROMPE O PROCESSO AO EXECUTAR
	printf("This line will not be executed.\n");
 
	return (0);
}