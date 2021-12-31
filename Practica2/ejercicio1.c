#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t thread1, thread2, thmain; 
pthread_attr_t attr;               

void *func(void *arg)
{
    int factorial1 = 1;
    int numero;
    
    printf("Escriba un numero enteros\n");
    scanf("%d", &numero);
    
    for (int num = 1; num <= numero; num++)
       factorial1 *= num;
    
    printf("El factorial de %d es %d\n", numero, factorial1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self(); //Devuelve id 

    pthread_attr_init(&attr);

	//Creacion de threads
    pthread_create(&thread1, &attr, func, (void *)argv[1]);
    pthread_create(&thread2, &attr, func, (void *)argv[2]);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_exit(NULL);
}
