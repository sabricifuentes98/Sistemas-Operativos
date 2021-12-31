#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLON 1000

pthread_t thread, threadmain;
pthread_attr_t attr;

void *cuenta (void *arg) {
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    char *nombre = (char *) arg;

    fd = open (nombre, O_RDONLY);
    while((leidos = read (fd, cadena, MAXLON)) != 0){
        for(pos = 0; pos < leidos; pos++) {
            if((cadena[pos] == 'a') || (cadena[pos] == 'A')) {
                cont++;
            }
        }
    }
    printf("Fichero %s:%d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    threadmain = pthread_self(); //Devuelve el id del thread que lo invoca
    pthread_attr_init(&attr); //Inicializa el id del thread que lo invoca

    pthread_create(&thread, &attr, cuenta, "ejemplo.txt"); //Crea un thread para ejecutar una funcion determinada
    pthread_join(thread, NULL); //Espera hasta que termine el thread que se ha invocado
   
    pthread_exit(NULL);
}


