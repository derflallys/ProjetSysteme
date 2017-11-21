#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "error.h"
int getwidth(char * file )
{
    int fd = open(file,O_RDONLY);
    int width;
    int r;
    if (fd!=-1)
    {
          r= read(fd,&width, sizeof(int));
          if(r==-1)
          {
              perror("Erreur de lecture \n");
              EXIT_FAILURE;
          }
          if(r==0)
          {
              perror("Zero caractere lu \n");
              EXIT_FAILURE;
          }
            close(fd);
          return width;

    }
    else
    {
        close(fd);
        return 0;
    }
}




int main(int argc,char ** argv)
{
    if(argc<3)
    {
        perror("Veillez mettre les arguments");
        EXIT_FAILURE;
    }
    if(argc==3)
    {
        char  * file = argv[1];
        char * option =argv[2];

       if(strcmp(option,"--getwidth")==0)
       {
           int w = getwidth(file);
           if(w==0)
           {
               perror("Erreur de lecture du fichier");
               EXIT_FAILURE;
           }
           printf("%d \n",w);
       }
       if(strcmp(option,"--getheight")==0)
       {
           printf("height \n");

       }
       if(strcmp(option,"--getobjects")==0)
       {
           printf("objects \n");
       }
       if(strcmp(option,"--getinfo")==0)
       {
           printf("info \n");
       }

    }




}