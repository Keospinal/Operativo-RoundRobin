#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s programa [argumentos...]\n", argv[0]);
        return 1;
    }

    pid_t pid;
    clock_t start, end;
    double cpu_time_used;

     // Guardamos el tiempo de inicio
    start = clock();

    pid = fork(); // Creamos un nuevo proceso
    if (pid < 0) {

        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
    } else if (pid == 0) { // Proceso hijo

        // Ejecutamos el programa indicado junto con sus argumentos
        execvp(argv[1], &argv[1]);
        // Si execvp retorna, significa que ha habido un error
        perror("Error en execvp");
        exit(1);
    } else { // Proceso padre
        // Esperamos a que el proceso hijo termine
        wait(NULL);

        end = clock(); // Guardamos el tiempo de finalización
        cpu_time_used = ((double) (end - start));
        printf("Tiempo transcurrido: %.2f nanosegundos \n", cpu_time_used);

    }

    return 0;
}