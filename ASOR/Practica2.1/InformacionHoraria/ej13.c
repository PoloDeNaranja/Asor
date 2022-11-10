
#include<stdio.h>
#include<time.h>
#include <sys/time.h>

int main(){

    struct timeval t_ini;
    struct timeval t_fin;
    int max = 100000;
    int i = 0;
    gettimeofday(&t_ini, NULL);
    while(i<max){
        i++;
    }
    gettimeofday(&t_fin, NULL);
    printf("Tiempo microsegundos: %li\n", t_fin.tv_usec - t_ini.tv_usec);//resta es el timepo total uq etarda en ahcer lo del bucle
    return 0;
}