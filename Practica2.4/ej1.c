#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  
    struct addrinfo* info,* i;
    char host[512];
    if(argc!= 2){
        printf("Error: Numero de argumentos incorrecto");
    }
    getaddrinfo(argv[1],NULL,NULL,&info);

    for(i=info;i!=NULL;i=i->ai_next){
        getnameinfo(i->ai_addr,i->ai_addrlen,host,256,NULL,0,NI_NUMERICHOST);
        printf(" %s \t %d \t %d \n", host, i->ai_family, i->ai_socktype);
    }
    return 0;
}