#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat sb;

   if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* sym = malloc((sizeof(char)*(strlen(argv[1]))));
    char* hard = malloc((sizeof(char)*(strlen(argv[1]))));
	strcpy(sym, argv[1]);
	strcpy(hard, argv[1]);
	
    sym = strcat(sym, ".sym");
	hard = strcat(hard, ".hard");

	if (S_ISREG(sb.st_mode)) {
		printf("%s es un archivo ordinario.\n", argv[1]);

        if (symlink(argv[1],sym) == -1) {
			printf("ERROR: No se creo el enlace simbolico.\n");
		} 
        else{
            printf("Creado enlace simbolico.\n");
        } 

		if (link(argv[1],hard) == -1) {
			printf("ERROR: No se creo el enlace rigido.\n");
		} 
        else{
            printf("Creado enlace rigidco.\n");
        } 

		

	}

	

   return 0;
}