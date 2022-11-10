#include<stdio.h>
#include<sys/utsname.h>


int main(){

struct utsname buf;
int rc = uname(&buf);


    if(rc==-1){
        perror("uname()");
        return -1;
    }
printf("Sysname : %s\n", buf.sysname);
printf("Sysname : %s\n", buf.nodename);
printf("Sysname : %s\n", buf.release);
printf("Sysname : %s\n", buf.version);
printf("Sysname : %s\n", buf.machine);

return 0;
}
