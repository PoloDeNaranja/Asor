#include<sys/types.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/select.h>
#include<stdlib.h>



int main(int argc, char *argv[]){
        struct addrinfo hints;
        struct addrinfo *result;
        int aux=-1;
        fd_set df;

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
        bind(sd,result->ai_addr,result->ai_addrlen);//tendriamsoq ue controlar lo de addr info la de bind y la del socket para fallos.
        // sleep(300);
        // for (struct addrinfo * i = result; i!=0;i=i->ai_next){
        //     char host[NI_MAXHOST];
        //     char serv[NI_MAXSERV];
        //     getnameinfo(i->ai_addr.i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);//Con la or junto los flags
        //     printf('host: %s','serv: %s\n', host, serv);
        // }

        freeaddrinfo(result);

        while(1){
            char buffer[100];
            char host[NI_MAXHOST];    
            char serv[NI_MAXSERV];
            struct sockaddr_storage cliente; //usar ipv6 como ipv4 creo
            socklen_t clientelen = sizeof(cliente);
            while(aux==-1){
                FD_ZERO(&df); //Vaco
                FD_SET(sd, &df); //Descriptor socket
                FD_SET(0, &df); // Descriotir entrada est
                aux = select(sd+1, &df, NULL, NULL, NULL);//salir
            }
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            size_t max;
            char b[100]; 

            if (FD_ISSET(sd,&df)){//estructura if else  en fucnion del parametro mostrar una fecha o una hora
                ssize_t bytes = recvfrom(sd, buffer, 99, 0, (struct sockaddr *) &cliente, &clientelen);//hasta el final
                getnameinfo((struct sockaddr *) &cliente, clientelen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
                printf("[%li:%s] %s", bytes, host, serv);
                buffer[bytes] = '\0';

                if (buffer[0] == 't'){
                    size_t by = strftime(b, max, "%I:%M:%S %p", tm);
                    b[by] = '\0';

                    sendto(sd, b, by, 0, (struct sockaddr *) &cliente, clientelen);

                }else if (buffer[0] =='d'){
                    size_t by = strftime(b, max, "%Y-%m-%d", tm);
                    b[by] = '\0';
                    sendto(sd, b, by, 0, (struct sockaddr *) &cliente, clientelen);
                } 
                else if (buffer[0] =='q'){
                    printf("Espera que esta acabando");
                    exit(0);
                }
                else{
                    printf("Fallo");
                }

            } 

            else {
                read(0, buffer, 2);
                printf("Terminal %i bytes\n",2);
                buffer[99] = '\0';

                if (buffer[0] == 't'){
                size_t by = strftime(b, max, "%I:%M:%S %p", tm);
                        b[by] = '\0';
                        sendto(sd, b, by, 0, (struct sockaddr *) &cliente, clientelen);

                }
                else if (buffer[0] =='d'){
                    size_t by = strftime(b, max, "%Y-%m-%d", tm);
                    b[by] = '\0';
                    sendto(sd, b, by, 0, (struct sockaddr *) &cliente, clientelen);
                }
                else if (buffer[0] =='q'){
                    printf("Espera que esta acabando");
                    exit(0);
                }
                else{
                    printf("Fallo");
                }

            }

        }


    return 0;

}


