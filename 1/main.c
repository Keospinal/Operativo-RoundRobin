#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv[]) {
    int num;
    pid_t pid;

    for (num = 0; num < 3; num++) {
        pid = fork();
        if (pid != 0) {
            // Esto se ejecuta en el proceso padre
            printf("Soy el proceso de PID %d y mi padre tiene %d de PID.\n",
                   getpid(), getppid());
            break; // Sal del bucle después de la creación del hijo
        } else {
            // Esto se ejecuta en los procesos hijos
            printf("Soy el proceso de PID %d y mi padre tiene %d de PID.\n",
                   getpid(), getppid());
            exit(0); // Termina el proceso hijo después de imprimir el mensaje
        }
        srandom(getpid());
        sleep(random() % 3);
    }

    if (pid != 0) { // Solo el proceso padre imprime el mensaje final
        printf("Fin del proceso de PID %d.\n", wait(NULL));
    }

    return 0;
}
