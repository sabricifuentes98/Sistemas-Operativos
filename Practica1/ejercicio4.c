#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	
	int num;
	pid_t pid;
	
	srandom(getpid()); 
	for (num = 0; num < 2; num++) { 
		pid = fork(); // Crea un proceso hijo y devuelve su PID padre o -1 en caso de error
		printf("Soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
		
		if (pid == 0) {
			break;
		}
	}
	
	pid = fork(); // Crea un proceso hijo y el padre es el proceso principal por lo que no se ejecuta el bucle
	printf("Soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid()); // Se ejecuta porque el padre es el proceso principal y no el proceso hijo que se crea en el bucle anterior
	
	if (pid == 0) { // Si el proceso es el hijo se ejecuta el bucle y se imprime el PID del proceso 
		sleep(random() % 5);
	} else { 
		for (num = 0; num < 2; num++) { 
			printf("Fin del proceso de PID %d.\n", wait(NULL)); //
		}
	}
	
	return 0;
}
