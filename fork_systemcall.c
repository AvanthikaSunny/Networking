#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
pid_t pid;
pid = fork();
if (pid > 0)
{
// Parent process
printf("\nParent process");
printf("\nParent PID = %d\n", getpid());
}
else if (pid == 0)
{
// Child process
printf("\nChild process");
printf("\nChild PID = %d", getpid());
printf("\nParent PID = %d\n", getppid());
}
else
{
// Fork failed
perror("fork failed");
}
return 0;
}