#include<stdio.h>
#include<time.h>
#include <locale.h>

int main(){
    struct tm * time_inf;
	time_t t = time(NULL);
    char buf[100];

	time_inf = localtime(&t);
    setlocale(LC_ALL, "");//region

	strftime(buf,100,"%A, %d de %B de %Y, %H:%M",time_inf);// A dia semana d dia b mes Y anio h y m hora y minutos

    printf("%s\n",buf);

	return 0;
}