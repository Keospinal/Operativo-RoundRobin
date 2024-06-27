#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execlp("xload", "xload", NULL);
        perror("Error al ejecutar xload");
        exit(EXIT_FAILURE);
    } else {
        printf("Se ha iniciado xload.\n");
    }

    execlp("kcalc", "kcalc", NULL);
    perror("Error al ejecutar kcalc");
    exit(EXIT_FAILURE);

    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("xload ha terminado.\n");
    } else {
        printf("xload ha terminado de forma anormal.\n");
    }

    printf("kcalc ha terminado.\n");

    return 0;
}
