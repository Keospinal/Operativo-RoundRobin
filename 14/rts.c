#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    bool fin = false;
    char nombreprog[50], esperar[5];
    pid_t pid;

    while (!fin)
    {
        printf("Programa:");
        scanf("%s", nombreprog);
        if (strcmp(nombreprog, "salir") != 0)
        {
            printf("Esperar? S/N: ");
            scanf("%s", esperar);

            pid = fork();
            if (pid==0)
            {
                char ruta[100] = "./"; 
                strcat(ruta, nombreprog); 
                char *args[] = {ruta, NULL};
		        execvp(ruta, args); 
                perror("execvp");
            }else
            {
                switch (toupper(esperar[0]))
                {
                case 'S':
                    wait(NULL);
                    break;

                case 'N':
                    break;

                default:
                    puts("opcion invalida");
                }
            }
        }
        else
            fin = true;
    }
    return 0;
}