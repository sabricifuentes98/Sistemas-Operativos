#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int fd;
    char buffer[1000]; 
    size_t numBytes = 1000; 
    int bytesRead;

    if((fd = open("test", O_RDONLY, 444)) == -1) {
        perror("Error al abrir el archivo");
    } else {
        bytesRead = read(fd, buffer, numBytes);
    }

    printf("\n");
    for(int i = 100; i <= 110; i++) { 
        printf("%c", buffer[i]); 
    }
    printf("\n");
    
    close(fd);
    exit(0);
}
