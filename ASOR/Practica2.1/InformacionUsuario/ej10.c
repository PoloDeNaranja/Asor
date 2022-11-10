#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <pwd.h>


int main(){
    struct passwd * paswd_inf;
    paswd_inf = getpwuid(getuid());
    
   printf("Username: %s\n", paswd_inf->pw_name);
   printf("Home: %s\n", paswd_inf->pw_dir);
   printf("Descripcion: %s\n",paswd_inf->pw_gecos);
   return 0;

}