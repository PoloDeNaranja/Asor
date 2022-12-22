#include<sys/types.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
// ./udp :: 1 7777
// [<origen conexion>]: <datos>
// [<origen conexion>]: <datos>
// [<origen conexion>]: <datos>


int main(int argc, char *argv[]){
        struct addrinfo hints;
        struct addrinfo *result;

        if(argc != 3){
        printf("Error: Numero de argumentos incorrecto");
        }
        memset(&hints,0,sizeof(struct addrinfo)); //Poner toda la estrutura a 0 apra luego inicializar los que quiero
        // familia es si es ipv6 o ipv4
        hints.ai_flags = AI_PASSIVE;//Poner la dir 0000 o la estrella cuando hacia un ss
        hints.ai_family= AF_UNSPEC;//Puede hablar ambas direcciones a la vez si pone ipv6 habla solo ipvs6
        hints.ai_socktype=SOCK_DGRAM; // Esto es para udp
        
        int rc = getaddrinfo(argv[1],argv[2],&hints,&result);
        if(rc!=0){
            printf("[getaddrinfo]: %s\n",gai_strerror(rc));
            return -1;
        }        

        int sd = socket(result-> ai_family, result->ai_socktype,0);//si quiero usar tcp ya con cambiar el sockdgram vale sin tener que cambiar 200 cosas asi esta todo el codifgo generico
        //bind(sd,result->ai_addr,result->aix_addrlen);//tendriamsoq ue controlar lo de addr info la de bind y la del socket para fallos.
        // sleep(300);
        // for (struct addrinfo * i = result; i!=0;i=i->ai_next){
        //     char host[NI_MAXHOST];
        //     char serv[NI_MAXSERV];
        //     getnameinfo(i->ai_addr.i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);//Con la or junto los flags
        //     printf('host: %s','serv: %s\n', host, serv);
        // }

        freeaddrinfo(result);
        char buffer[100];
        char host[NI_MAXHOST];    
        char serv[NI_MAXSERV];
        struct sockaddr_storage cliente; //usar ipv6 como ipv4 creo
        socklen_t clientelen = sizeof(cliente); 
        sendto(sd, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);
        printf("%s\n", argv[3]);

        if (*argv[3] == 't' || *argv[3] == 'd'){
            char b[100];
            ssize_t by = recvfrom(sd, b, 99, 0, (struct sockaddr *) &cliente, &clientelen);
            b[by] = '\0';
            printf("%s\n", b);
        }


  
    return 0;

}
//uso netcat -u que es udp y con ipv6 pongo -6 la dir dd me quiero coenctar que es localhost y le puerto : nc -u -6 ::1 7777 puedo usar tmb el nc -u 192.168.0.1 3000

