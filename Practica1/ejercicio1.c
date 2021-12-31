#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    int fd, bytes_escritos, bytes_leidos; /* descriptor de fichero */
    char buffer[100];
    mode_t modo = S_IRWXU; /* modo de r, w y x para el propietario */

    strcpy(buffer, "Esto es un ejemplo\n");
    if ((fd = open("ejemplo", O_RDWR | O_CREAT, modo)) == -1)
        /* abre el fichero ejemplo en modo lectura/escritura o lo crea si no existe */
        perror("Error al abrir o crear el fichero");
    /* muestra un mensaje de error si no puede abrir/crear el fichero */
    else
    {
        bytes_escritos = write(fd, buffer, strlen(buffer));
        /* Colocamos puntero en la posicion 0 y leemos */
        lseek(fd, 0, SEEK_SET);
        bytes_leidos = read(fd, buffer, strlen(buffer));
        printf("Mensaje: %sBytes escritos: %d, Bytes leidos: %d\n", buffer, bytes_escritos, bytes_leidos);
    }
    exit(0);
}
