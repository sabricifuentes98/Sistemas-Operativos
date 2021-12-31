#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) {
	int fd, bytes_escritos;
	char buffer[100];
	mode_t modo= S_IRWXU; //modo r,w y x para el propietario
	
	strcpy(buffer, "Esto es un ejemplo\n");
	if ((fd = open ("ejemplo", O_RDWR | O_CREAT, modo)) == -1)
	//Abre el fichero ejemplo o lo crea si no existe
	perror ("Error al abrir o crear el fichero");
	else 
	   bytes_escritos = write (fd, buffer, strlen(buffer));
	   //Escribe buffer de tamaño sizeof(buffer) en fd
	exit(0);
}
