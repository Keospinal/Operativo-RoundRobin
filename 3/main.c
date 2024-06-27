#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int num;
    pid_t nuevo;
    for(num = 0; num< 2; num++){
        nuevo = fork(); //1
        if(nuevo== 0)
            break;
    }
    nuevo = fork();//2
    nuevo =  fork();//3
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
}