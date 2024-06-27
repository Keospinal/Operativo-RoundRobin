#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long int factorial(int n) {
    long long int resultado = 1;
    for (int num = 2; num <= n; num++) {
        resultado *= num;
        printf("Factorial de %d, resultado parcial %lld\n", n, resultado);
        sleep(random() % 3);
    }
    return resultado;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    long long int res = factorial(n);

    printf("El factorial de %d es %lld\n", n, res);

    return 0;
}
