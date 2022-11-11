#include <unistd.h>
#include <stdio.h>

int main(){

printf("Sysname : %li\n", pathconf("ej7.c",_PC_LINK_MAX));
printf("Sysname : %li\n", pathconf("ej7.c",_PC_PATH_MAX));
printf("Sysname : %li\n", pathconf("ej7.c",_PC_NAME_MAX));


return 0;
}
