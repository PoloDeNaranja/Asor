#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main(){
    struct rlimit *rlim;
    pid_t r1 = getpid();
    pid_t r2 = getppid();
    pid_t r3 = getpgid(r1);
    pid_t r4 = getsid(r1);
    int k = getrlimit(RLIMIT_NOFILE, rlim);
    long int r = rlim->rlim_max;


    printf("PID: %i\n",r1);
    printf("PPID: %i\n",r2);
    printf("PGID: %i\n",r3);
    printf("SID: %i\n",r4);
    printf("Numero maximo de ficheros que puede abrir: %li\n",r);
    printf("Directorio actual: %s\n",get_current_dir_name());
    return 0;
}