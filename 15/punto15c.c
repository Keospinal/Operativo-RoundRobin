#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Error al crear el primer proceso hijo\n");
        return 1;
    } else if (pid1 == 0) {
        printf("Proceso hijo 1 con PID: %d\n", getpid());
        execl("./puntoa", "puntoa", argv[1], NULL);
        perror("exec");
        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0) {
        fprintf(stderr, "Error al crear el segundo proceso hijo\n");
        return 1;
    } else if (pid2 == 0) {
        printf("Proceso hijo 2 con PID: %d\n", getpid());
        execl("./puntoa", "puntoa", argv[2], NULL);
        perror("exec");
        exit(1);
    }

    printf("Proceso padre con PID: %d esperando a que los hijos terminen...\n", getpid());

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Ambos procesos hijos han terminado. El proceso padre también finaliza.\n");

    return 0;
}
