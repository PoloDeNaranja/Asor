#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include <string.h>

int main() {
   int VErr = setuid(2);
    if(VErr == -1){
        printf("Error (%d): %s\n", VErr, strerror(VErr));
        return -1;
    }
   return 1;
}
