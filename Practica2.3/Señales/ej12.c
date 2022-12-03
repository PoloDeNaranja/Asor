#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int N_SIGINT=0;
int N_SIGTSTP=0;

void handler(int signal){
	

  //printf("\nInside handler function\n");
	if(signal == SIGINT){
		N_SIGINT++;
	}
	else if (signal == SIGTSTP){
		N_SIGTSTP++;
	}
	
}


int main(int argc, char * argv[]){


	signal(SIGINT,handler);
	signal(SIGTSTP,handler);

	
	while(N_SIGINT+N_SIGTSTP <10){
	//sleep(1);
	//printf("\nInside normal function\n");
	}
	printf("SIGINT= %i\nSIGTSTP= %i",N_SIGINT,N_SIGTSTP);

	return 0;
}
