#include <unistd.h>
#include <stdio.h>

int main(){

printf("Sysname : %li\n", sysconf(_SC_ARG_MAX));
printf("Sysname : %li\n", sysconf(_SC_CHILD_MAX));
printf("Sysname : %li\n", sysconf(_SC_OPEN_MAX));

return 0;
}
