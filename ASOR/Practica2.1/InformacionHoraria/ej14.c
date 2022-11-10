#include<stdio.h>
#include<time.h>
#include <sys/time.h>



int main(){
    struct tm * time_inf;
	time_t t = time(NULL);

	time_inf = localtime(&t);

	printf("Anio: %d\n", 1900 + time_inf->tm_year);//tengo que poner 1900 si queiro que salga el 2022

	return 0;
}