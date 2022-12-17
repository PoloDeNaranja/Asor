#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
 
 
int main(){
 
   char buff[256];
   int max;
   int fd1 = open("./tuberia1", O_RDONLY | O_NONBLOCK); 
   int fd2 = open("./tuberia2", O_RDONLY | O_NONBLOCK);
   while(1){
        fd_set conj;
       FD_ZERO(&conj);
       FD_SET(fd1, &conj);
       FD_SET(fd2, &conj);

       if(fd1 > fd2){
           max = fd1;
       }
       else{
           max = fd2;
       }
       int rc = select(max +1,&conj,0,0,0);
       if(FD_ISSET(fd1, &conj)){
           int bytes = read(fd1, buff, 255);
           if(bytes == 0){
               close(fd1);
               fd1 = open("./tuberia1", O_RDONLY | O_NONBLOCK); 
               continue;
           }
           buff[bytes]='\0';
           printf("tuberia1:%s\n", buff);
       }
 
       if(FD_ISSET(fd2, &conj)){
           int bytes = read(fd2, buff, 255);
           if(bytes == 0){
               close(fd2);
               fd2 = open("./tuberia2", O_RDONLY | O_NONBLOCK);
               continue;
           }
           buff[bytes]='\0';
           printf("tuberia2:%s\n", buff);
       }
   }
}