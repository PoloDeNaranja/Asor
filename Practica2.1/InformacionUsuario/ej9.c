#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>



int main() {

	printf("UID Real: %d\n", getuid());
	printf("UID efecivo: %d\n", geteuid());
	return 0;

}