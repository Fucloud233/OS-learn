#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
static void child()
{
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("I'm child! my pid is %d.\n", getpid());
    fflush(stdout);
    execve("/bin/echo", args, NULL);
    err(EXIT_FAILURE, "exec() failed");
    printf("exec() faile");
}

static void parent(pid_t pid_c)
{
    printf("I'm parent! my pid is %d and the pid of my child is %d.\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(void)
{
    pid_t ret;
    ret = fork();
    if (ret == -1)
        err(EXIT_FAILURE, "fork() failed");
    if (ret == 0)
    {
        // 这里应该调哪个函数
   	child();
     }
    else
    {
        // 这里应该调哪个函数
    	parent(ret);
    }
    // 在正常运行时，不可能运行到这里
    err(EXIT_FAILURE, "shoudln't reach here");
}
