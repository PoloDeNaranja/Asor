#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	
	int fd = open(argv[1], O_WRONLY);
    
	if (fd == -1) {
		perror("Error al abrir el fichero");
		return -1;
	}

	if (lockf(fd,F_TLOCK, 0) == 0) {
		printf("Fichero esta bloqueado\n");
		sleep(10);
		printf("Time: %ld\n", time(NULL));
		lockf(fd, F_ULOCK, 0);
		sleep(10);
		return 0;
	}
	else {
		perror("Fallo");
		return 1;
	}

	close(fd);
	return 0;
}