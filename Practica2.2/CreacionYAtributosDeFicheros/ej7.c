#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    mode_t mascara = umask(027);
    int f = open("ej6.txt", O_CREAT, 0645);
    return 0;
}