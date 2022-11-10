#include<errno.h>
#include<stdio.h>
#include<unistd.h>

int main() {
   int VErr = setuid(2);
    if(VErr == -1){
        perror("Error");
        return -1;
    }

    

   return 1;
}
