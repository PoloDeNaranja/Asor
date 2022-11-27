#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int f = open("ej5.txt", O_CREAT, 0645);
    return 0;
}