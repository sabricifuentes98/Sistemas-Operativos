#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t thread1, thread2, thmain;
pthread_attr_t attr;
sem_t semProductor, semConsumidor;

int buffer[12];

void *productor(void *arg)
{
    for (int i = 0; i < 12; i++)
    {
        sem_wait(&semProductor);
        if (buffer[i] == 0)
        {
            buffer[i] = i + 1;
            int data = buffer[i];
            printf("Dato producido: %d\n", data);
            for (int i = 0; i < 12; i++)
            {
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semConsumidor);
        sleep(random() % 3);
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg)
{
    for (int i = 12; i > 0; i--)
    {
        sem_wait(&semConsumidor);
        if (buffer[i] != 0)
        {
            int data = buffer[i];
            buffer[i] = 0;
            printf("Dato consumido: %d\n", data);
            for (int i = 0; i < 12; i++)
            {
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }
        sem_post(&semProductor);
        sleep(random() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    thmain = pthread_self();

    pthread_attr_init(&attr);
    sem_init(&semProductor, 0, 12);
    sem_init(&semConsumidor, 0, 0);

    pthread_create(&thread1, &attr, productor, NULL);
    pthread_create(&thread2, &attr, consumidor, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semProductor);
    sem_destroy(&semConsumidor);
    pthread_exit(NULL);
}
