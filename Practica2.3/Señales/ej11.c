#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char * argv[]){
    sigset_t val; // valor ini
    sigset_t valpend; // valor que he de recibir y mirar si esta

    if (argc!=2){
        printf("Faltan valores");
        return -1;
    }

    char *segs = getenv("SLEEP_SECS");
    sigemptyset(&val);
    sigaddset(&val, SIGINT);
    sigaddset(&val, SIGTSTP);
    sigprocmask(SIG_BLOCK, &val, NULL);
    printf("A dormir %s\n", segs);
    sleep(atoi(segs));

    sigpending(&valpend);

    if (sigismember(&valpend, SIGINT) == 1) {
		printf("Se recibio SIGINT\n");
        sigdelset(&val,SIGINT);
	}
    else{
        printf("No se recibio SIGINT\n");
    }
	if (sigismember(&valpend, SIGTSTP) == 1) {
		printf("Se ha recibido SIGTSTP\n");
		sigdelset(&val, SIGTSTP);
		
	}
    else{
        printf("No se recibio SIGTSTP\n");
    }

    sigprocmask(SIG_UNBLOCK, &val, NULL);//desbloqueo

    return 0;
}