#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
    int cont1, cont2;
    pid_t pid;
    printf("Soy el padre %d\n", getpid());
    for (cont2 = 0; cont2 < 2; cont2++)
    {
        for (cont1 = 0; cont1 < 2; cont1++)
        {
            pid = fork();
            if (pid == 0)
            {
            printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
                break;
            }
            wait(NULL);
        }
        if (pid != 0)
            break;
    }
    
    return 0;
}