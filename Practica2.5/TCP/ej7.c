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
        fd_set df;

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
        //bind(sd,result->ai_addr,result->ai_addrlen);//tendriamsoq ue controlar lo de addr info la de bind y la del socket para fallos.
        // sleep(300);
        // for (struct addrinfo * i = result; i!=0;i=i->ai_next){
        //     char host[NI_MAXHOST];
        //     char serv[NI_MAXSERV];
        //     getnameinfo(i->ai_addr.i->ai_addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);//Con la or junto los flags
        //     printf('host: %s','serv: %s\n', host, serv);
        // }
        rc = connect(sd, result->ai_addr, result->ai_addrlen);//poner if de control de error
        
        

        while(1){
            char buffer[100];
            FD_ZERO(&df);
            FD_SET(sd, &df);
            FD_SET(0, &df);
            

            select(sd + 1, &df, NULL, NULL, NULL);

            if (FD_ISSET(0, &df)) {
                int rd = read(0, buffer, sizeof(buffer));
                if (buffer[0] == 'Q' && rd == 2){//si mete la q
                    printf("Conexión terminada\n");
                    return 1;
                } 
                else{
                    send(sd, buffer, rd, 0);  
                }
                
            }
            else if (FD_ISSET(sd, &df)) {
                int by = recv(sd, buffer, sizeof(buffer) - 1, 0);
                buffer[by] = '\0';
                printf("%s", buffer);
            }
		}     

    return 0;

    
}

