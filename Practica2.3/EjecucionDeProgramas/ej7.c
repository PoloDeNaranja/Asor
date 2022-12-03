#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc,char *argv[]){
 if (argc != 3){
        perror ("Error, poner un argumento(0 para system y 1 para execvp), luego poner el programa a ejecutar");
        return -1;
    }
  if(atoi(argv[1])==0){
        printf ("argv[1]=0, system\n");
        int r = system(argv[2]);
        printf("El comando terminó de ejecutarse");
    }else if (atoi(argv[1])==1){
        printf ("argv[1]=1, execvp\n");
        
        int r = execv(argv[2],NULL);
        printf("El comando terminó de ejecutarse");
  }else{
        perror ("Error, poner un argumento(0 para system y 1 para execvp, luego poner el programa a ejecutar)");
        return -1;
    }

    return 0;
}