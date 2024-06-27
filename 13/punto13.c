#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h> // Incluir la cabecera string.h

void writeCharByChar(const char *str) {
    while (*str != '\0') {
        putchar(*str);
        fflush(stdout); // Limpiar el búfer de salida para que el carácter se imprima inmediatamente
        usleep(rand() % 1000000); // Introducir un retardo aleatorio en microsegundos (hasta 1 segundo)
        str++;
    }
}

int main() {
    char str1[100], str2[100];
    pid_t pid1, pid2;
    
    // Solicitar al usuario que introduzca las cadenas
    printf("Introduce la primera cadena: ");
    fgets(str1, sizeof(str1), stdin);
    printf("Introduce la segunda cadena: ");
    fgets(str2, sizeof(str2), stdin);
    
    // Eliminar el carácter de nueva línea del final de las cadenas
    if (str1[strlen(str1) - 1] == '\n')
        str1[strlen(str1) - 1] = '\0';
    if (str2[strlen(str2) - 1] == '\n')
        str2[strlen(str2) - 1] = '\0';

    // Crear el primer proceso hijo
    pid1 = fork();
    
    if (pid1 < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Proceso hijo 1: escribir la primera cadena
        writeCharByChar(str1);
        exit(EXIT_SUCCESS);
    } else {
        // Proceso padre
        
        // Esperar a que termine el primer proceso hijo
        wait(NULL);

        // Crear el segundo proceso hijo
        pid2 = fork();
        
        if (pid2 < 0) {
            // Error al crear el proceso hijo
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Proceso hijo 2: escribir la segunda cadena
            writeCharByChar(str2);
            exit(EXIT_SUCCESS);
        } else {
            // Proceso padre
            
            // Esperar a que termine el segundo proceso hijo
            wait(NULL);
        }
    }

    return 0;
}