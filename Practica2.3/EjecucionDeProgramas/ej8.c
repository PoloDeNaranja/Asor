#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
 #include <fcntl.h>

int main(int argc, char *argv[]){

  if (argc < 2) {
   printf("Faltan valores");
    return -1;
  }
pid_t pid = fork();

  if(pid == -1){
    perror("Error");
      return -1;
  }
 else if (pid == 0){
    pid_t mi_sid = setsid();
    int fd = open("/tmp/daemon.out",O_CREAT | O_RDWR, 0654);
    int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0654);
    int fdnull = open("/dev/null", O_CREAT | O_RDWR, 0654);
    int fd0 = dup2(fdnull, 0);
    int fd1 = dup2(fderr, 1);
    int fd2 = dup2(fd,2);
    if (execvp(argv[1], argv + 1) == -1) { // esto es lo cambiado del ej 7 que no iba en la vm
        printf("No lo has metido bien");
        return -1;
    }
 }
  else{
    printf("PID: %i\n",getpid());
    printf("PPID: %i\n",getppid());
    printf("SID: %i\n",getsid(getpid()));
    printf("PGID: %i\n",getpgid(getpid()));
  }

  return 0;
}