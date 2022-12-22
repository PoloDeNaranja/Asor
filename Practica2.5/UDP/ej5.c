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
#include<wait.h>


int main (int argc, char*argv[]) {

    struct addrinfo hints;
    struct addrinfo *result;

    if (argc != 3) {
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

    freeaddrinfo(result);

  
  
    char buffer[100];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    struct sockaddr_storage cliente; //usar ipv6 como ipv4 creo
    socklen_t clientelen = sizeof(cliente);
    int i = 0;
    int state;
    for (i = 0; i < 100; i++){
        pid_t pid = fork();
        pid_t r1 = getpid();

        if (pid == 0) {
            while(1){
                ssize_t bytes = recvfrom(sd, buffer, 99, 0, (struct sockaddr *) &cliente, &clientelen);
                buffer[bytes] = '\0';

                getnameinfo((struct sockaddr *) &cliente, clientelen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

                printf("[%li:%s] %s %i\n", bytes, host, serv, r1);

                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                size_t max;
                char b[100];

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
        else{
            pid = wait(&state);
        }
    }
    

  
  return 0;
}