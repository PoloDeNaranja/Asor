#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

char* PATH ="";

void sig_handler(int signum){
 	remove(PATH);
}
void sig_handlerUsr(int signum){
 	sigset_t mask;
	sigemptyset(&mask);
 	sigaddset(&mask, SIGALRM);
	sigsuspend(&mask);

}

int main(int argc, char * argv[]){

	PATH = argv[0];
	signal(SIGALRM,sig_handler);

	if (argc!=2){
        printf("Faltan valores");
        return -1;
   	}
	
	signal(SIGUSR1,sig_handlerUsr);
	
	int a = alarm(atoi(argv[1]));

	sleep(atoi(argv[1])+1);
	return 0;
}