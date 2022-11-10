#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>



int main(){
    struct passwd * paswd_inf;
    paswd_inf = getpwuid(getuid());
    
   printf("Username: %d\n", passwd_inf->pw_name);
   printf("Home: %d\n", passwd_inf->pw_dir);
   printf("Descripcion:%d\n",passwd_inf->pw_gecos);
   return 0;

}