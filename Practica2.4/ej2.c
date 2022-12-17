#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char* argv[]){


    int p_h[2];
    int h_p[2];
    pipe(p_h); 
    pipe(h_p);
    char res = 'l',resHijo = 'l';

    int pid = fork();
    if (pid==0){//Hijo
        close(h_p[0]);
        close(p_h[1]); 

        int i;
        for(i=0;i<10;i++){
            char msgHijo[256];
            int b = read(p_h[0],msgHijo,255);
            msgHijo[b]='\0';
            printf("HIJO-> Salida: %s\n",msgHijo);
            resHijo = 'l';
            if(i==9){
                resHijo = 'q';
            }
            write(h_p[1],&resHijo,1);

        }
    }else{
        close(p_h[0]); 
        close(h_p[1]);

        while(res != 'q'){
            char msg[256];
            printf("PADRE-> Escribe un mensaje para que lo lea el padre (max 255 caracteres):\n");
            int b = read(0, msg, 255);
            msg[b] = '\0';
            write(p_h[1], msg, 255);
            read(h_p[0], &res, 1);
        }

    }

    wait();
    return 0;
}