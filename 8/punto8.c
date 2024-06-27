#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void crear_arbol_procesos(int profundidad_actual, int maxima_profundidad, int anchura) {
    int i;
    pid_t pid;

    if (profundidad_actual < maxima_profundidad) {
        if (profundidad_actual % 2 == 0 && profundidad_actual != 0) {
            for (i = 0; i < anchura; i++) {
                pid = fork();

                if (pid == -1) {
                    perror("Error en fork");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0) {
                    printf("Nivel %d: Soy el proceso %d y mi padre es %d\n", profundidad_actual + 1, getpid(), getppid());
                    crear_arbol_procesos(profundidad_actual + 1, maxima_profundidad, anchura);
                    exit(0);
                }
            }

            for (i = 0; i < anchura; i++) {
                wait(NULL);
            }
        } else {
            pid = fork();

            if (pid == -1) {
                perror("Error en fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                printf("Nivel %d: Soy el proceso %d y mi padre es %d\n", profundidad_actual + 1, getpid(), getppid());
                crear_arbol_procesos(profundidad_actual + 1, maxima_profundidad, anchura);
                exit(0);
            }

            wait(NULL);
        }
    }
}

int main(int argc, char *argv[]) {
    int profundidad, anchura;

    if (argc != 3) {
        printf("Uso: %s <profundidad> <anchura>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    profundidad = atoi(argv[1]);
    anchura = atoi(argv[2]);

    printf("Nivel 0: Soy el proceso %d\n", getpid());
    crear_arbol_procesos(0, profundidad, anchura);

    return 0;
}