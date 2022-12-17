#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
    int fd;
    if(argc!= 2){
        printf("Error: Numero de argumentos incorrecto");
    }

    // char* tub = ("/tuberia")
    // mkfifo(tub, 0777);
    // mkfifo -m 0777 tuberia
    fd = open("./tuberia", O_WRONLY);// abrir terminal con el mkfifo
    write(fd, argv[1], strlen(argv[1])+1);
    close(fd);

    return 0;
}