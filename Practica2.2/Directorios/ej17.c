#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char *argv[]){

struct stat sb;

if(argc != 2){
fprintf(stderr,"Usage: %s <pathname>\n", argv[0]);
return -1;
}

int r = stat(argv[1],&sb);
if(r = -1){
perror("Error con lstat");
}

if(S_ISDIR(sb.st_mode)){
	printf("Entradas del directorio: \n");
	DIR * dir = opendir(argv[1]);//Abrimos directorio
	struct dirent * entrada = readdir(dir);//Leemos

	//Creamos la ruta para hacer los nombres relativos
	char* nDir = strcat(argv[1],"/");
	
	do{
		char* nombre= (char*)malloc(200*sizeof(char));
		
		nombre = entrada->d_name;//Leemos nombre
		printf(" - %s",nombre);//Escribimos el nombre del archivo unicamente
		
		//Creamos un string que contenga la ruta relativa del fichero para poder hacer stat
		char* path= (char*)malloc(200*sizeof(char));
		path = strcat(path,nDir);
		path = strcat(path,entrada->d_name);

		int r = lstat(path,&sb);//Vamos a buscar el tipo de fichero que es
		
		if(S_ISDIR(sb.st_mode)){//Escribimos el simbolo correspondiente
			printf("/\n");

		}else if(S_ISREG(sb.st_mode) && (sb.st_mode & S_IXUSR || sb.st_mode & S_IXGRP ||sb.st_mode & S_IXOTH)){//Ver que el archivo puede ser ejecutado y que es de tipo regular
			printf("*\n");

		}else if(S_ISLNK(sb.st_mode)){
			printf("->");
			char* buf= (char*)malloc(sb.st_size+1);//Sacamos el nombre, lo metemos en un buffer y lo escribimos
			ssize_t l = readlink(path,buf,(sb.st_size+1));
			buf[sb.st_size] = '\0';
			printf("%s\n", buf);

		}else{
			printf("\n");
		}
		

		entrada = readdir(dir);
		nombre="";
	}while(entrada!=NULL);

}else{
perror("El argumento proporcionado no es un directorio");
}

return 0;

}