#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t childpid1, childpid2;
    double array[20];

    childpid1 = fork();
    if (childpid1 == -1)
    {
        perror("Fork no pudo crear el hijo1");
        exit(1);
    }
    else if (childpid1 == 0)
    {
        printf("Soy el hijo1 con PID %d y voy a calcular el cuadrado de los pares \n", getpid());
        for (int i = 0; i < 20; i++)
            if (i % 2 == 0)
            {
                array[i] = pow(i, 2);
                printf("%d: %.f, ", i, array[i]);
            }
    }
    else
    {
        childpid2 = fork();
        if (childpid2 == -1)
        {
            perror("Fork no pudo crear el hijo2");
            exit(1);
        }
        else if (childpid2 == 0)
        {
            printf("Soy el hijo2 con PID %d y voy a calcular el cuadrado de los impares \n", getpid());
            for (int i = 0; i < 20; i++)
                if (i % 2 != 0)
                {
                    array[i] = pow(i, 2);
                    printf("%d: %.f, ", i, array[i]);
                }
        }
        else
        {
            printf("Soy el padre con PID %d y voy a esperar a mis hijos \n", getpid());
            childpid2 = wait(0);
            childpid1 = wait(0);
        }
    }
    exit(0);
}
