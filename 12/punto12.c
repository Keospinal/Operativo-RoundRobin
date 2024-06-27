#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2;
    time_t start_time, end_time;
    double kcalc_time, xload_time, parent_time;

    start_time = time(NULL);

    pid1 = fork();
    if (pid1 == 0) {
        execlp("kcalc", "kcalc", NULL);
        perror("Error al iniciar kcalc");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == 0) {
        execlp("xload", "xload", NULL);
        perror("Error al iniciar xload");
        exit(EXIT_FAILURE);
    }

    int status;
    pid_t pid_terminado;
    while ((pid_terminado = wait(&status)) > 0) {
        end_time = time(NULL);
        if (pid_terminado == pid1) {
            kcalc_time = difftime(end_time, start_time);
            printf("El proceso kcalc ha terminado. Tiempo de ejecución: %f segundos\n", kcalc_time);
        } else if (pid_terminado == pid2) {
            xload_time = difftime(end_time, start_time);
            printf("El proceso xload ha terminado. Tiempo de ejecución: %f segundos\n", xload_time);
        }
    }

    parent_time = difftime(time(NULL), start_time);
    printf("Tiempo de ejecución del proceso padre: %f segundos\n", parent_time);

    return 0;
}
