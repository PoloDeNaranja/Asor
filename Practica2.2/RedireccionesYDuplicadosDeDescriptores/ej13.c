#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return -1;
  }
  int fd;
  if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1) {
		perror("Error al crear o abrir el fichero");
		return -1;
	}

	if (dup2(fd, 1) == -1)  {
		perror("Error al redirigir");
		return -1;
	}
    if (dup2(fd, 2) == -1)  {
		perror("Error al redirigir");
		return -1;
	}
    
    printf("Se ha redirigido a %s",argv[1]);
    fprintf(stderr,"Redirigir error");
    close(fd);


   
   return 0;
}