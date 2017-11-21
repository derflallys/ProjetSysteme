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
int getheight(char  * file)
{
    int fd = open(file,O_RDONLY);
    int height;
    int r;
    int l ;
    if (fd!=-1)
    {
        l=lseek(fd,sizeof(int),SEEK_SET);
        if (l==-1)
        {
            perror("Erreur lseek \n");
            exit(0);
        }
        r= read(fd,&height, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture \n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu \n");
            exit(0);
        }
        close(fd);
        return height;

    }
    else
    {
        close(fd);
        return 0;
    }
}

int getnbobjects(char  * file )
{
    int fd = open(file,O_RDONLY);
    int nbobjects;
    int r;
    int l ;
    if (fd!=-1)
    {
        l=lseek(fd,2*sizeof(int),SEEK_SET);
        if (l==-1)
        {
            perror("Erreur lseek \n");
            exit(0);
        }
        r= read(fd,&nbobjects, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture \n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu \n");
            exit(0);
        }
        close(fd);
        return nbobjects;

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
               exit(0);
           }
           printf("%d \n",w);
       }
       if(strcmp(option,"--getheight")==0)
       {
           int h = getheight(file);
           if(h==0)
           {
               perror("Erreur de lecture du fichier");
               exit(0);
           }
           printf("%d \n",h);

       }
        else {
           if (strcmp(option, "--getobjects") == 0) {
               int nb = getnbobjects(file);
               if (nb == 0) {
                   perror("Erreur de lecture du fichier");
                   exit(0);
               }
               printf("%d \n", nb);
           } else {
               if (strcmp(option, "--getinfo") == 0) {
                   int nb = getnbobjects(file);
                   int w = getwidth(file);
                   int h = getheight(file);
                   if (nb == 0 || w == 0 || h == 0) {
                       perror("Erreur de lecture du fichier");
                       exit(0);
                   }
                   printf("width: %d height: %d nbObjects: %d\n", w, h, nb);
               }
               else
               {
                   printf("Voici les options : \n");
                   printf("--getwidth \n");
                   printf("--getheight \n");
                   printf("--getinfo \n");
               }
           }
       }
    }
    if(argc==4)
    {
        char  * file = argv[1];
        char * option =argv[2];
        int hORw = atoi(argv[3]);
        if(strcmp(option,"--setwidth")==0)
        {
            int width = getwidth(file);
            if(width<hORw)
            {
                int fd = open(file,O_WRONLY,0666);
                if(fd!=-1)
                {
                    int w = write(fd,&hORw,sizeof(int));
                    if(w==-1)
                    {
                        perror("Erreur de ecriture du fichier");
                        exit(0);
                    }
                    if(w==0)
                    {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    lseek(fd,3*sizeof(int),SEEK_SET);
                    int nbelmts,r;
                    r=read(fd,&nbelmts,sizeof(int));
                    if(r==-1)
                    {
                        perror("Erreur de lecture \n");
                        exit(0);
                    }
                    if(r==0)
                    {
                        perror("Zero caractere lu \n");
                        exit(0);
                    }
                    for (int i = 0; i <nbelmts ; ++i) {

                        int x,y,obj,r;
                        r=read(fd,&obj,sizeof(int));
                        if(r==-1)
                        {
                            perror("Erreur de lecture \n");
                            exit(0);
                        }
                        if(r==0)
                        {
                            perror("Zero caractere lu \n");
                            exit(0);
                        }
                        r=read(fd,&x,sizeof(int));
                        if(r==-1)
                        {
                            perror("Erreur de lecture \n");
                            exit(0);
                        }
                        if(r==0)
                        {
                            perror("Zero caractere lu \n");
                            exit(0);
                        }
                        r=read(fd,&y,sizeof(int));
                        if(r==-1)
                        {
                            perror("Erreur de lecture \n");
                            exit(0);
                        }
                        if(r==0)
                        {
                            perror("Zero caractere lu \n");
                            exit(0);
                        }
                        for (int j = 0; j < getheight(file); ++j) {
                            if(obj==1 && x==width && y==i)
                            {

                            }
                        }


                    }
                    close(fd);

                }

            }
        }

    }




}