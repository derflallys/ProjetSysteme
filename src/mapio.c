#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "error.h"

#ifdef PADAWAN

void map_new (unsigned width, unsigned height)
{
  map_allocate (width, height);

  for (int x = 0; x < width; x++)
    map_set (x, height - 1, 0); // Ground

  for (int y = 0; y < height - 1; y++) {
    map_set (0, y, 1); // Wall
    map_set (width - 1, y, 1); // Wall
  }

  map_object_begin (8);

  // Texture pour le sol
  map_object_add ("images/ground.png", 1, MAP_OBJECT_SOLID);
  // Mur
  map_object_add ("images/wall.png", 1, MAP_OBJECT_SOLID);
  // Gazon
  map_object_add ("images/grass.png", 1, MAP_OBJECT_SEMI_SOLID);
  // Marbre
  map_object_add ("images/marble.png", 1, MAP_OBJECT_SOLID | MAP_OBJECT_DESTRUCTIBLE);
  // Herbe
  map_object_add ("images/herb.png", 1, MAP_OBJECT_AIR);
  // Petit plancher flottant
  map_object_add ("images/floor.png", 1, MAP_OBJECT_SEMI_SOLID);
   // Fleur
  map_object_add ("images/flower.png", 1, MAP_OBJECT_AIR);
   // Coins
  map_object_add ("images/coin.png", 20, MAP_OBJECT_AIR |  MAP_OBJECT_COLLECTIBLE);


  map_object_end ();
}

void map_save (char *filename)
{

    char buff;
    int w;
    int fd = open(filename,O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd !=-1)
    {
        //save width char: w
        sprintf(&buff,"%d",map_width());
        w=write (fd,&buff,sizeof(unsigned));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        //save height
        sprintf(&buff,"%d",map_height());
        w=write (fd,&buff,sizeof(unsigned));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        //save objects char: n
        sprintf(&buff,"%d",map_objects());
        w=write (fd,&buff,sizeof(unsigned));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        unsigned obj;
        int nbelmts = 0;

         for (int x = 0; x < map_width(); x++)
         {
                for(int y = 0; y < map_height(); y++)
                {
                    obj = map_get(x,y);
                    if(obj!=-1)
                        nbelmts++;
                }
         }

         write(fd,&nbelmts,sizeof( int));
         if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");

        for (int x = 0; x < map_width(); x++)
       {
            for(int y = 0; y < map_height(); y++)
            {

                obj = map_get(x,y);
                if(obj!=-1)
                {


                    write(fd,&obj,sizeof(int));
                    if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");

                    write(fd,&x,sizeof(int));
                    if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");

                    write(fd,&y,sizeof(int));
                   if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");

                }

            }
        }
        int lnames=0;

        for(int i=0;i<map_objects();i++)
        {
            //frame
            sprintf(&buff,"%d",map_get_frames(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //solidity
            sprintf(&buff,"%d",map_get_solidity(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //destrictible
            sprintf(&buff,"%d",map_is_destructible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //collectible
            sprintf(&buff,"%d",map_is_collectible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //generator
            sprintf(&buff,"%d",map_is_generator(i));
            w=write(fd,&buff,sizeof(unsigned));

            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //longueur name
            lnames = strlen(map_get_name(i));

            w=write(fd,&lnames,sizeof(int));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            //name
            w=write(fd,map_get_name(i),lnames);
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");


        }
    }
    else
    {
        perror("erreur ouverture fichier");
    }
    close(fd);
   fprintf (stdout, "Maps saved\n");
}

void map_load (char *filename)
{
  int fd = open(filename,O_RDONLY);
  if(fd!=-1)
  {

      char buff;
      int r ;
      int nbelmts;
      int obj ;
      int x;
      int y;
      unsigned frame;
      unsigned solid;
      unsigned dest;
      unsigned collect;
      unsigned gener;
      int lname;


     r=read(fd,&buff,sizeof(unsigned));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     int width = atoi(&buff);


     r=read(fd,&buff,sizeof(unsigned));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     int height = atoi(&buff);


     r=read(fd,&buff,sizeof(unsigned));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     int nbobject = atoi(&buff);


     r=read(fd,&nbelmts,sizeof(int));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");



     map_allocate (width, height);


     for(int i= 0 ; i<nbelmts;i++)
     {
        r=read(fd,&obj,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");

        r=read(fd,&x,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");

        r=read(fd,&y,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");

        map_set (x, y,obj);

     }


     map_object_begin (nbobject);

     for(int i= 0 ; i<nbobject;i++)
            {
                char * filename ;
                //frame
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                frame = atoi(&buff);
                //solid
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                solid = atoi(&buff);
                //dest
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                dest = atoi(&buff);
                //collect
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                collect = atoi(&buff);
                //gener
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                gener = atoi(&buff);

                //lname
                r=read(fd,&lname,sizeof(int));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");


                //name

                filename = malloc(lname);
                if(filename==NULL)
                    {
                        fprintf(stderr,"Erreur malloc \n");
                        EXIT_FAILURE;
                    }
                r=read(fd,filename,lname);
                filename[lname]='\0';

                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");


                printf("%s  %d  %d %d %d %d\n",filename,frame,solid,dest,collect,gener);
                int f = (dest  | collect | gener);
                printf("f:  %d \n",f);
                if(strcmp(filename,"images/coin.png")==0)
                    map_object_add (filename, frame,   collect  ==1 ? solid | MAP_OBJECT_COLLECTIBLE : solid  );
                else
                if(strcmp(filename,"images/marble.png")==0)
                    map_object_add (filename, frame,   dest  ==1 ? solid | MAP_OBJECT_DESTRUCTIBLE : solid  );
                else
                    map_object_add (filename, frame,    solid   );
                free(filename);


            }
            map_object_end ();

            fprintf(stdout,"Map Load");
     }
    else
    {
        perror("Erreur de open");
        EXIT_FAILURE;
     }

      close(fd);
      // exit_with_error ("Map load is not yet implemented\n");
}

#endif
