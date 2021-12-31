#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT_LIMIT 12

pthread_t thread1, thread2, threadmain;
pthread_attr_t attr;
pthread_mutex_t my_lock;
pthread_cond_t bufferLleno, bufferVacio;

int buffer[COUNT_LIMIT];

void *productor(void *arg); 
void *consumidor(void *arg);


void *productor(void *arg) { 
    
    for(int i = 0; i < COUNT_LIMIT; i++) { 
        pthread_mutex_lock(&my_lock); 

        while(buffer[i] == COUNT_LIMIT) { // Si el buffer está lleno
            pthread_cond_wait(&bufferLleno, &my_lock); 
        }

        buffer[i] = i + 1; 
        int data = buffer[i]; // Guardamos el valor del buffer
        printf("Productor: %d\n", data); 

        for(int i = 0; i < COUNT_LIMIT; i++) { // Si el buffer está vacío
            printf("%d ", buffer[i]); 
        }
        printf("\n");

        pthread_cond_signal(&bufferVacio); // Liberamos el buffer
        pthread_mutex_unlock(&my_lock); 
        sleep(rand() % 2);
    }
    pthread_exit(NULL);
}

void *consumidor (void *argc) {
    for(int i = 0; i < COUNT_LIMIT; i++) { // Mientras no se haya consumido todo el buffer
        pthread_mutex_lock(&my_lock); 

        while(buffer[i] == 0) { // Si el buffer está vacío
            pthread_cond_wait(&bufferVacio, &my_lock); // Esperamos a que el buffer no esté vacío
        }

        int data = buffer[i];
        buffer[i] = 0;
        printf("Consumidor: %d\n", data);

        for(int i = 0; i < COUNT_LIMIT; i++) { // Si el buffer está lleno
            printf("%d ", buffer[i]); 
        }
        printf("\n");

        pthread_cond_signal(&bufferLleno); // Liberamos el buffer 
        pthread_mutex_unlock(&my_lock); 
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    threadmain = pthread_self(); // Obtenemos el identificador del hilo principal

    pthread_attr_init(&attr); 
    pthread_mutex_init(&my_lock, NULL); 

    // Inicializamos las condiciones
    pthread_cond_init(&bufferLleno, NULL); 
    pthread_cond_init(&bufferVacio, NULL);

    // Creamos el hilo productor y el consumidor
    pthread_create(&thread1, &attr, productor, NULL); 
    pthread_create(&thread2, &attr, consumidor, NULL);

    // Esperamos a que los hilos terminen
    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 

    pthread_mutex_destroy(&my_lock); 

    // Destruimos las condiciones 
    pthread_cond_destroy(&bufferLleno); 
    pthread_cond_destroy(&bufferVacio);
    
    pthread_exit(NULL); //
}
