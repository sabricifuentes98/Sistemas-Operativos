#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main( int argc, char *argv[] ) {

    int fd1, fd2;
    char buffer[1000];
    size_t nbytes = 1000;
    int bytes_leidos;

    if((fd1 = open ("test", O_RDONLY, 444)) == -1) { //abre el archivo en modo lectura y permisos 444 
        perror("Error al abrir el archivo");
    } else {
        bytes_leidos = read(fd1, buffer, nbytes); //lee el archivo y lo guarda en buffer 
    }

    close(fd1); //cierra el archivo

    if((fd2 = open ("open", O_RDWR | O_CREAT, 111)) == -1) { //abre el archivo en modo lectura y permisos 444, crea el archivo si no existe 
        perror("Error al abrir el archivo");
    } else {
        write(fd2, buffer, bytes_leidos); //escribe el archivo en el archivo creado
    }

    return 0;
}
