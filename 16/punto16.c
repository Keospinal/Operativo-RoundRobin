#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero1> <numero2> ... <numeroN>\n", argv[0]);
        return 1;
    }

    int count = 0;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            execl("./factorial", "factorial", argv[i], NULL);
            perror("execl");
            exit(1);
        }
    }

    int status;
    pid_t pid;

    while ((pid = wait(&status)) > 0) {
        count++;
        if (count > 1) {
            printf("Proceso hijo con PID %d finalizado\n", pid);
        }
    }

    return 0;
}
