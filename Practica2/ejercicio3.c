#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t thread1, thread2, thmain;
pthread_attr_t attr;
int globalvar=0;

void *incremento1(void *);
void *incremento2(void *);

void *incremento2(void *args){
    pthread_mutex_t* mutex = args; //se guarda el parametro mutex.
    pthread_mutex_lock(mutex); //protege la sección crítica

    printf("Empieza el hilo 1 -> ");
    for(int i=0; i < 4; i++){
        globalvar ++;
        printf("%d, ", globalvar);
    }
    printf("-> Thread 1 terminado.\n");

    pthread_mutex_unlock(mutex); //Libera la protección
    pthread_exit(NULL); 
}

void *incremento1(void *args){
    pthread_mutex_t* mutex = args; //se guarda el parametro mutex.
    pthread_mutex_lock(mutex); //protege la sección crítica

    printf("Empieza el hilo 2 -> ");
    for(int i=0; i < 4; i++){
        globalvar++;
        printf("%d, ", globalvar);
    }
    printf("-> Thread 2 terminado.\n");

    pthread_mutex_unlock(mutex); //Libera la protección
    pthread_exit(NULL); 
}

int main(void){

    thmain = pthread_self(); 
    pthread_attr_init(&attr);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, &attr, incremento1, &mutex); 
    pthread_create(&thread2, &attr, incremento2, &mutex); 

    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 

    printf("Fin del programa\n.");

     exit(0);
}
