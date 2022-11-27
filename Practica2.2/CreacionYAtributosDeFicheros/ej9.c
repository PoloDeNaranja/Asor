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

   printf("File type:                ");

   printf("MAJOR: %li\n", (long) major(sb.st_dev));
   printf("MINOR: %li\n", (long) minor(sb.st_dev));

   
   printf("I-node number:            %ld\n", (long) sb.st_ino);

  
  if(S_ISDIR(sb.st_mode)){
        printf("%s es un directorio\n",argv[1]);
  }
  else if(S_ISLNK(sb.st_mode)){
        printf("%s es un enlace simbolico\n",argv[1]);
  }
  else if(S_ISREG(sb.st_mode)){
        printf("%s es un fichero ordinario\n",argv[1]);
  }

   
    printf("Last file access:         %s", ctime(&sb.st_atime));
    

   return 0;
}