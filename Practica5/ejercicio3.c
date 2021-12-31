#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int total = 0, longitud = 0, *nodos_i = NULL;

void anyade (int nodo_i) {
    if(longitud % 10 == 0) {
        nodos_i = (int *) realloc (nodos_i, (longitud + 10) * sizeof (int));
    }
    nodos_i[longitud] = nodo_i; 
    longitud++;
}

bool esta(int nodo_i) {
    int num;
    for(num = 0; num < longitud; num++) {
        if(nodos_i[num] == nodo_i) {
            return true;
        }
    }
    return false;
}

void recorre (char *nombredir) {
    DIR *dir;
    struct dirent *entrada;
    struct stat datos;
    char *ruta;

    dir = opendir(nombredir);

    if(dir == NULL) {
        printf("Error al abrir el directorio %s\n", nombredir);
        return;
    }

    entrada =  readdir(dir);

    while(entrada != NULL) {
        if(strcmp (entrada -> d_name, ".") && strcmp (entrada -> d_name, "..")) {
            ruta = malloc(strlen(nombredir) + strlen(entrada -> d_name) + 2);
            sprintf (ruta, "%s/%s", nombredir, entrada -> d_name);
            lstat(ruta, &datos);

            if(S_ISDIR (datos.st_mode)) {
                recorre(ruta); //llamada recursiva
            }

            total += datos.st_size;

            if(datos.st_nlink > 1) {
                if(esta (datos.st_ino) == false) {
                    anyade(datos.st_ino);
                }else {
                    total -= datos.st_size; 
                }
            }
            free(ruta);
        }
        entrada = readdir(dir);
    }
    closedir(dir);
}

int main (int argc, char *argv[]) {

    recorre("/home/sabrina/Documentos/Practica5");
    printf("Total en bytes: %d\n", total);
    return 0;
}
