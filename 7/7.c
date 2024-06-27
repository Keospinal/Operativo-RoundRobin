#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i, j;
    pid_t pid, nuevo, nuevo1;
    time_t ini, fin;

    ini = time(NULL);

    for (i = 0; i < 2; i++) {
        pid = getpid();
        for (j = 0; j < i + 2; j++) {
            nuevo = fork();
            if (nuevo == 0) {
                break;
            }
            nuevo1 = fork();
            if (nuevo1 == 0) {
                execlp("xload", "xload", NULL);
                exit(0);
            }
        }
        if (pid != getpid()) {
            execlp("kcalc", "kcalc", NULL);
            exit(0);
        }
    }

    while (wait(NULL) > 0);
    

    fin = time(NULL);
    printf("Tiempo total de ejecución: %ld segundos\n", (long)(fin - ini));

    return 0;
}