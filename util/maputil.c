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
              perror("Erreur de lecture width\n");
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
            perror("Erreur de lecture height\n");
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
            perror("Erreur de lecture nbobject \n");
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
int getnbelmts(char  * file )
{
    int fd = open(file,O_RDONLY);
    int nbelmts;
    int r;
    int l ;
    if (fd!=-1)
    {
        l=lseek(fd,3*sizeof(int),SEEK_SET);
        if (l==-1)
        {
            perror("Erreur lseek \n");
            exit(0);
        }
        r= read(fd,&nbelmts, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture nbelmts\n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu \n");
            exit(0);
        }
        close(fd);
        return nbelmts;

    }
    else
    {
        close(fd);
        return 0;
    }
}

void createCopy(char * filesrc,char * filedest,int position,char * option)
{
    int fd = open(filesrc,O_RDONLY);
    int fdbackup;
    if(strcmp(option,"trunc")==0)
        fdbackup = open(filedest,O_CREAT|O_WRONLY|O_TRUNC,0666);
    else
        if (strcmp(option,"append")==0)
            fdbackup = open(filedest,O_CREAT|O_WRONLY|O_APPEND,0666);
        else
            fdbackup = open(filedest,O_CREAT|O_WRONLY,0666);

    int r,w;
    int intbuf;
    char buff;
    int nbobjects;
    if(position==0)
    {
        lseek(fd,position,SEEK_SET);
        //width
        r= read(fd,&intbuf, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture width\n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu width \n");
            exit(0);
        }
        int w = write(fdbackup,&intbuf,sizeof(int));
        if(w==-1)
        {
            perror("Erreur de ecriture du fichier width");
            exit(0);
        }
        if(w==0)
        {
            perror("Zero caractere Ecrit");
            exit(0);
        }
        //height
        r= read(fd,&intbuf, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture height\n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu height\n");
            exit(0);
        }
        w = write(fdbackup,&intbuf,sizeof(int));
        if(w==-1)
        {
            perror("Erreur de ecriture du fichier height");
            exit(0);
        }
        if(w==0)
        {
            perror("Zero caractere Ecrit");
            exit(0);
        }
        //nbobjects
        r= read(fd,&intbuf, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture nbobj\n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu nbobj\n");
            exit(0);
        }
        nbobjects= intbuf;
        w = write(fdbackup,&intbuf,sizeof(int));
        if(w==-1)
        {
            perror("Erreur de ecriture du fichier nbobjects");
            exit(0);
        }
        if(w==0)
        {
            perror("Zero caractere Ecrit");
            exit(0);
        }
        //nbelmts
        r= read(fd,&intbuf, sizeof(int));
        if(r==-1)
        {
            perror("Erreur de lecture nbelmts\n");
            exit(0);
        }
        if(r==0)
        {
            perror("Zero caractere lu nbelmts\n");
            exit(0);
        }
        w = write(fdbackup,&intbuf,sizeof(int));
        if(w==-1)
        {
            perror("Erreur de ecriture du fichier nbelmts");
            exit(0);
        }
        if(w==0)
        {
            perror("Zero caractere Ecrit");
            exit(0);
        }
        int nbelmts = intbuf;
        for (int i = 0; i <nbelmts ; ++i) {
            //obj
            r= read(fd,&intbuf, sizeof(int));
            if(r==-1)
            {
                perror("Erreur de lecture obj dans save\n");
                exit(0);
            }
            if(r==0)
            {
                perror("Zero caractere lu obj\n");
                exit(0);
            }
            w = write(fdbackup,&intbuf,sizeof(int));
            if(w==-1)
            {
                perror("Erreur de ecriture du fichier obj dans save");
                exit(0);
            }
            if(w==0)
            {
                perror("Zero caractere Ecrit");
                exit(0);
            }
            //x
            r= read(fd,&intbuf, sizeof(int));
            if(r==-1)
            {
                perror("Erreur de lecture x\n");
                exit(0);
            }
            if(r==0)
            {
                perror("Zero caractere lu x\n");
                exit(0);
            }
            w = write(fdbackup,&intbuf,sizeof(int));
            if(w==-1)
            {
                perror("Erreur de ecriture du fichier x");
                exit(0);
            }
            if(w==0)
            {
                perror("Zero caractere Ecrit");
                exit(0);
            }
            //y
            r= read(fd,&intbuf, sizeof(int));
            if(r==-1)
            {
                perror("Erreur de lecture y\n");
                exit(0);
            }
            if(r==0)
            {
                perror("Zero caractere lu y\n");
                exit(0);
            }
            w = write(fdbackup,&intbuf,sizeof(int));
            if(w==-1)
            {
                perror("Erreur de ecriture du fichier y");
                exit(0);
            }
            if(w==0)
            {
                perror("Zero caractere Ecrit");
                exit(0);
            }
        }
        //fin nbelemts
    }

    if(position!=0)
    {
        lseek(fd,position,SEEK_SET);
    }
    //object caract

    for(int i= 0 ; i<nbobjects;++i)
    {

        char * filename ;
        //printf("%d\n",i);
        //frame
        r=read(fd,&buff,sizeof(unsigned));
        if (r == -1) {
            perror("Erreur de lecture frame dans save back \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu frame dans save back\n");
            exit(0);
        }
        w = write(fdbackup, &buff, sizeof(unsigned));
        if (w == -1) {
            perror("Erreur de ecriture du fichier frame");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }

        //solid
        r=read(fd,&buff,sizeof(unsigned));
        if (r == -1) {
            perror("Erreur de lecture solid \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu solid\n");
            exit(0);
        }
        w = write(fdbackup, &buff, sizeof(unsigned));
        if (w == -1) {
            perror("Erreur de ecriture du fichier solid");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }

        //dest
        r=read(fd,&buff,sizeof(unsigned));
        if (r == -1) {
            perror("Erreur de lecture dest \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu dest \n");
            exit(0);
        }
        w = write(fdbackup, &buff, sizeof(unsigned));
        if (w == -1) {
            perror("Erreur de ecriture du fichier dest");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }

        //collect
        r=read(fd,&buff,sizeof(unsigned));
        if (r == -1) {
            perror("Erreur de lecture collect \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu collect\n");
            exit(0);
        }
        w = write(fdbackup, &buff, sizeof(unsigned));
        if (w == -1) {
            perror("Erreur de ecriture du fichier collect");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }
        //gener
        r=read(fd,&buff,sizeof(unsigned));
        if (r == -1) {
            perror("Erreur de lecture gener \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu gener\n");
            exit(0);
        }
        w = write(fdbackup, &buff, sizeof(unsigned));
        if (w == -1) {
            perror("Erreur de ecriture du fichier genr");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }

        //lname
        int lname;
        r=read(fd,&lname,sizeof(int));
        if (r == -1) {
            perror("Erreur de lecture lname\n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu lname\n");
            exit(0);
        }
        w = write(fdbackup, &lname, sizeof(int));
        if (w == -1) {
            perror("Erreur de ecriture du fichier lname");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit");
            exit(0);
        }

        //name
        //J'alloue de la memoire à filename avec le nombre de caractere de la chaine lie dans le fichier  avec malloc
        filename = malloc(lname);
        if(filename==NULL)
        {
            fprintf(stderr,"Erreur malloc \n");
            EXIT_FAILURE;
        }
        r=read(fd,filename,lname);
        if (r == -1) {
            perror("Erreur de lecture file \n");
            exit(0);
        }
        if (r == 0) {
            perror("Zero caractere lu file \n");
            exit(0);
        }
        filename[lname]='\0';
        //ensuite j'achete le caractere de fin de chaine

        w = write(fdbackup, filename, lname);
        if (w == -1) {
            perror("Erreur de ecriture du fichier file \n");
            exit(0);
        }
        if (w == 0) {
            perror("Zero caractere Ecrit file\n");
            exit(0);
        }
        //printf("%s \n",filename);

        //je libere l'espace allouer recemment
        free(filename);
    }
    close(fd);
    close(fdbackup);

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
                   int nbelmts = getnbelmts(file);
                   if (nb == 0 || w == 0 || h == 0 || nbelmts==0) {
                       perror("Erreur de lecture du fichier");
                       exit(0);
                   }
                   printf("width: %d height: %d nbObjects: %d nbelements: %d \n", w, h, nb,nbelmts);
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
    if(argc==4) {
        char *file = argv[1];
        char *option = argv[2];
        int hORw = atoi(argv[3]);
        int width = getwidth(file);
        int height = getheight(file);
        int nbelmtssave = getnbelmts(file);
        int nbobjets = getnbobjects(file);
        if (strcmp(option, "--setwidth") == 0) {

            if (width < hORw) {
                //creer un backup du fichier save.map
                char *filebackup = "backup.map";
                createCopy(file, filebackup, 0, "trunc");
                int fd = open(file, O_WRONLY | O_TRUNC, 0666);
                int fdBackup;
                int r, w;
                int intbuff;
                if (fd != -1) {
                    w = write(fd, &hORw, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier hOrw");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &height, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier height save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &nbobjets, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier objects save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    int newnbelemts = nbelmtssave + hORw - width;
                    w = write(fd, &newnbelemts, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier new nbelemts save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }

                    fdBackup = open(filebackup, O_RDONLY);
                    int vue;
                    int x, y, obj;
                    if (fdBackup != -1) {
                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);

                        for (int i = 0; i < nbelmtssave; ++i) {


                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }

                            //changement des coordonnes du mur pour les mettre à la fin
                            w = write(fd, &obj, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            vue = 0;
                            for (int j = 0; j < height; ++j) {

                                if (obj == 1 && x == width - 1 && y == j) {

                                    x = hORw - 1;

                                    //x
                                    w = write(fd, &x, sizeof(int));
                                    if (w == -1) {
                                        perror("Erreur de ecriture du fichier x save");
                                        exit(0);
                                    }
                                    if (w == 0) {
                                        perror("Zero caractere Ecrit");
                                        exit(0);
                                    }
                                    vue = 1;
                                    break;
                                }
                            }
                            if (vue == 0) {
                                w = write(fd, &x, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier x save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }
                            }
                            w = write(fd, &y, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier y save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                        }
                        //fin save old elements
                        //completion du sols
                        for (int l = width; l < hORw; ++l) {
                            //obj
                            obj = 0;
                            w = write(fd, &obj, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            x = l;
                            w = write(fd, &x, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            y = height - 1;
                            w = write(fd, &y, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }

                        }
                        close(fd);
                        close(fdBackup);
                        //fin add ground
                        //ajout des caracteristique des objects
                        int pos = 4*sizeof(int)+nbelmtssave*(3*sizeof(int));
                        createCopy(filebackup, file, pos, "append");
                    }

                }

            } else {
                //si la nouvelle valeur est inferieur à l'ancienne valeur
                char *filebackup = "backup.map";
                createCopy(file, filebackup, 0, "trunc");
                int fd = open(file, O_WRONLY | O_TRUNC, 0666);
                int fdBackup;
                int r, w;
                int intbuff;
                if (fd != -1) {
                    w = write(fd, &hORw, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier hOrw");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &height, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier height save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &nbobjets, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier objects save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    int x, y, obj;
                    fdBackup = open(filebackup, O_RDONLY);
                    int vue;

                    if (fdBackup != -1) {
                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);
                        int nbelemtsDelete = 0;
                        for (int i = 0; i < nbelmtssave; ++i) {
                            // printf("i: %d \n", i);

                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj  backup\n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }

                            for (int j = hORw; j < width; ++j) {
                                if (x == j && obj!=1) {
                                    nbelemtsDelete++;
                                    break;
                                }
                            }
                        }

                        int newnbelemts = nbelmtssave - nbelemtsDelete;
                        printf("new :%d", newnbelemts);
                        w = write(fd, &newnbelemts, sizeof(int));
                        if (w == -1) {
                            perror("Erreur de ecriture du fichier new nbelemts save");
                            exit(0);
                        }
                        if (w == 0) {
                            perror("Zero caractere Ecrit");
                            exit(0);
                        }


                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);

                        for (int i = 0; i < nbelmtssave; ++i) {
                            // printf("i: %d \n", i);

                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj  backup\n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            int in = 0;
                            for (int j = hORw; j < width; ++j) {
                                if (x == j) {
                                    in = 1;
                                    break;
                                }
                            }

                            if (in != 1) {
                                //changement des coordonnes du mur pour les mettre à la fin
                                w = write(fd, &obj, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier obj save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }
                                w = write(fd, &x, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier x save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }
                                w = write(fd, &y, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier y save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }

                            }
                            else
                            {
                                if(obj==1)
                                {
                                    w = write(fd, &obj, sizeof(int));
                                    if (w == -1) {
                                        perror("Erreur de ecriture du fichier obj save");
                                        exit(0);
                                    }
                                    if (w == 0) {
                                        perror("Zero caractere Ecrit");
                                        exit(0);
                                    }
                                    x=hORw-1;
                                    w = write(fd, &x, sizeof(int));
                                    if (w == -1) {
                                        perror("Erreur de ecriture du fichier x save");
                                        exit(0);
                                    }
                                    if (w == 0) {
                                        perror("Zero caractere Ecrit");
                                        exit(0);
                                    }
                                    w = write(fd, &y, sizeof(int));
                                    if (w == -1) {
                                        perror("Erreur de ecriture du fichier y save");
                                        exit(0);
                                    }
                                    if (w == 0) {
                                        perror("Zero caractere Ecrit");
                                        exit(0);
                                    }
                                }
                            }
                        }//fin add object

                        close(fd);
                        close(fdBackup);

                        //ajout des caracteristique des objects
                        int pos = 4 * sizeof(int) + nbelmtssave * (3 * sizeof(int));
                        createCopy(filebackup, file, pos, "append");


                    }


                }
            }
        } else if (strcmp(option, "--setheight") == 0) {
            if (hORw < 20 && hORw > height) {
                //creer un backup du fichier save.map
                char *filebackup = "backup.map";
                createCopy(file, filebackup, 0, "trunc");
                int fd = open(file, O_WRONLY | O_TRUNC, 0666);
                int fdBackup;
                int r, w;
                int intbuff;
                if (fd != -1) {
                    w = write(fd, &width, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier hOrw");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &hORw, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier height save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &nbobjets, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier objects save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    int newnbelemts = nbelmtssave + (hORw - height) * 2;
                    w = write(fd, &newnbelemts, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier nbelemts save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }

                    fdBackup = open(filebackup, O_RDONLY);
                    int vue;
                    int x, y, obj;
                    if (fdBackup != -1) {
                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);
                        //completion du murs
                        for (int l = 0; l < hORw - height; ++l) {
                            //obj
                            obj = 1;
                            w = write(fd, &obj, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            x = 0;
                            w = write(fd, &x, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            y = l;
                            w = write(fd, &y, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            printf("WALL obj:%d x:%d y:%d \n", obj, x, y);
                        }
                        for (int l = 0; l < hORw - height; ++l) {
                            //obj
                            obj = 1;
                            w = write(fd, &obj, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            x = width - 1;
                            w = write(fd, &x, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            y = l;
                            w = write(fd, &y, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            //printf("WALL obj:%d x:%d y:%d \n", obj, x, y);
                        }

                        for (int i = 0; i < nbelmtssave; ++i) {


                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }


                            w = write(fd, &obj, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier obj save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            w = write(fd, &x, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier x save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }
                            y=y+(hORw-height);
                            w = write(fd, &y, sizeof(int));
                            if (w == -1) {
                                perror("Erreur de ecriture du fichier y save");
                                exit(0);
                            }
                            if (w == 0) {
                                perror("Zero caractere Ecrit");
                                exit(0);
                            }

                        }
                        //fin save old elements


                        close(fd);
                        close(fdBackup);
                        //fin add ground
                        //ajout des caracteristique des objects
                        int pos = 4 * sizeof(int) + nbelmtssave * (3 * sizeof(int));
                        createCopy(filebackup, file, pos, "append");
                    }

                }
            }
            else {
                //si la nouvelle valeur est inferieur à l'ancienne valeur de height
                char *filebackup = "backup.map";
                createCopy(file, filebackup, 0, "trunc");
                int fd = open(file, O_WRONLY | O_TRUNC, 0666);
                int fdBackup;
                int r, w;
                int intbuff;
                if (fd != -1) {
                    w = write(fd, &width, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier hOrw");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &hORw, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier height save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    w = write(fd, &nbobjets, sizeof(int));
                    if (w == -1) {
                        perror("Erreur de ecriture du fichier objects save");
                        exit(0);
                    }
                    if (w == 0) {
                        perror("Zero caractere Ecrit");
                        exit(0);
                    }
                    int x, y, obj;
                    fdBackup = open(filebackup, O_RDONLY);
                    int vue;

                    if (fdBackup != -1) {
                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);
                        int nbelemtsDelete = 0;
                        for (int i = 0; i < nbelmtssave; ++i) {
                            // printf("i: %d \n", i);

                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj  backup\n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }

                            for (int j = 0; j < height-hORw; ++j) {
                                if (y == j ) {
                                    nbelemtsDelete++;
                                    break;
                                }
                            }
                        }

                        int newnbelemts = nbelmtssave - nbelemtsDelete;
                       // printf("new :%d \n", newnbelemts);
                        w = write(fd, &newnbelemts, sizeof(int));
                        if (w == -1) {
                            perror("Erreur de ecriture du fichier nbelemts save");
                            exit(0);
                        }
                        if (w == 0) {
                            perror("Zero caractere Ecrit");
                            exit(0);
                        }


                        lseek(fdBackup, 4 * sizeof(int), SEEK_SET);
                        int nbtest=0;
                        for (int i = 0; i < nbelmtssave; ++i) {
                            // printf("i: %d \n", i);

                            r = read(fdBackup, &obj, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture obj  backup\n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &x, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture x \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            r = read(fdBackup, &y, sizeof(int));
                            if (r == -1) {
                                perror("Erreur de lecture y \n");
                                exit(0);
                            }
                            if (r == 0) {
                                perror("Zero caractere lu \n");
                                exit(0);
                            }
                            int in = 0;
                            for (int j = 0; j < height-hORw; ++j) {
                                if (y == j) {
                                    in = 1;
                                    break;
                                }
                            }

                            if (in != 1) {
                                nbtest++;
                                //changement des coordonnes du mur pour les mettre à la fin
                                w = write(fd, &obj, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier obj save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }
                                w = write(fd, &x, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier x save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }
                                y=y-(height-hORw);
                                w = write(fd, &y, sizeof(int));
                                if (w == -1) {
                                    perror("Erreur de ecriture du fichier y save");
                                    exit(0);
                                }
                                if (w == 0) {
                                    perror("Zero caractere Ecrit");
                                    exit(0);
                                }


                            }


                        }//fin add object

                        close(fd);
                        close(fdBackup);
                        //fin add ground
                        //ajout des caracteristique des objects
                        int pos = 4 * sizeof(int) + nbelmtssave * (3 * sizeof(int));
                        createCopy(filebackup, file, pos, "append");


                    }
                }
            }
        }

    }




}