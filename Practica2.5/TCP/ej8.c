
#include<sys/types.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<stdlib.h>



int main(int argc, char *argv[]){
        struct addrinfo hints;
        struct addrinfo *result;

        if(argc!= 3){
        printf("Error: Numero de argumentos incorrecto");
        }
        memset(&hints,0,sizeof(struct addrinfo)); //Poner toda la estrutura a 0 apra luego inicializar los que quiero
        // familia es si es ipv6 o ipv4
        // hints.ai_flags = AI_PASSIVE;//Poner la dir 0000 o la estrella cuando hacia un ss
        hints.ai_family= AF_UNSPEC;//Puede hablar ambas direcciones a la vez si pone ipv6 habla solo ipvs6
        hints.ai_socktype=SOCK_STREAM; // Esto es para TCP
        
        int rc = getaddrinfo(argv[1],argv[2],&hints,&result);
        if(rc!=0){
            printf("[getaddrinfo]: %s\n",gai_strerror(rc));
            return -1;
        }        

        int sd = socket(result-> ai_family, result->ai_socktype,0);//si quiero usar tcp ya con cambiar el sockdgram vale sin tener que cambiar 200 cosas asi esta todo el codifgo generico
        bind(sd,result->ai_addr,result->ai_addrlen);//tendriamsoq ue controlar lo de addr info la de bind y la del socket para fallos.
        listen(sd,10);
        // sleep(300);
        // for (struct addrinfo * i = result; i!=0;i=i->ai_next){
        //     char host[NI_MAXHOST];
        //     char serv[NI_MAXSERV];
        //     getnameinfo(i->ai_addr.i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);//Con la or junto los flags
        //     printf('host: %s','serv: %s\n', host, serv);
        // }


        
        char buffer[100];
        char buffer2[100];//en lugar de host y serv
        struct sockaddr_storage cliente; //usar ipv6 como ipv4 creo
        socklen_t clientelen = sizeof(cliente);
        while(1){
            int csd = accept(sd,(struct sockaddr *) &cliente, &clientelen);
            int pid = getpid();
            if (fork() == 0) {
                while (1) {
                    getnameinfo((struct sockaddr *)&cliente, clientelen, buffer2, sizeof(buffer2), NULL, 0  , NI_NUMERICHOST);//no quiero servidro
                    printf("Estamos en %i  desde %s\n", getpid(),buffer2);
                    ssize_t bytes = recv(csd, buffer, 99, 0);
                    buffer[bytes] = '\0';

                    if ((buffer[0] == 'Q') && (bytes == 2)) {
                    printf("Conexión terminada\n");
                    break;
                    }
                    send(csd, buffer, bytes, 0);
                }
            }
        }
        
    return 0;           
}


 

