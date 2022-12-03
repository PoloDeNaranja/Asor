#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    const int PATH_MAX = 200;
    pid_t pid = fork();

    if(pid == 0){
        return 0;
    }
    else if(pid == -1){
        perror("Error fork");
        return -1;
    }
 else{
        chdir("/tmp");
        char path[PATH_MAX];
        pid_t r1 = getpid();
        pid_t r2 = getppid();
        pid_t r3 = getpgid(r1);
        pid_t r4 = getsid(r1);

        if (getcwd(path, PATH_MAX) == NULL) {
            perror("Fallo");
            return -1;
        }
 printf("PID: %i\n",r1);
        printf("PPID: %i\n",r2);
        printf("PGID: %i\n",r3);
        printf("SID: %i\n",r4);
        printf("Directorio actual: %s\n",path);

        return 0;
    }

    return 0;


}