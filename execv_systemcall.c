// E1.c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
printf("We are in E1\n");
printf("PID = %d\n", getpid());
char *args[] = {"e2", "Hello", "ss", "fff", NULL};
execv("./e2", args);
// This will execute ONLY if execv fails
perror("execv failed");
return 0;
}
// E2.c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
printf("\nWe are in E2\n");
printf("PID = %d\n", getpid());
printf("Arguments received:\n");
for (int i = 0; i < argc; i++)
{
printf("argv[%d] = %s\n", i, argv[i]);
}
return 0;
}