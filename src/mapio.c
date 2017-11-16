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


        for (int x = 0; x < map_width(); x++)
       {
            for(int y = 0; y < map_height(); y++)
            {

                obj = map_get(x,y);
                if(obj!=-1)
                {

                    //sprintf(&buff,"%d",obj);
                    write(fd,&obj,sizeof(int));

                    //sprintf(&buff,"%d",x);
                    write(fd,&x,sizeof(int));

                    //sprintf(&buff,"%d",y);
                    write(fd,&y,sizeof(int));
                   // printf("%d \n",map_get(x,y));

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
                    exit_with_error ("Erreur de lecture\n");
            //solidity
            sprintf(&buff,"%d",map_get_solidity(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            //destrictible
            sprintf(&buff,"%d",map_is_destructible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            //collectible
            sprintf(&buff,"%d",map_is_collectible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            //generator
            sprintf(&buff,"%d",map_is_generator(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            //longueur name
            lnames = strlen(map_get_name(i));
            //printf("%s \n",map_get_name(i));
            //printf("taille : %d \n",strlen(map_get_name(i)));
            w=write(fd,&lnames,sizeof(int));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            //name
            w=write(fd,map_get_name(i),lnames);
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");


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
      char * filename ;

     r=read(fd,&buff,sizeof(unsigned));
     int width = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&buff,sizeof(unsigned));
     int height = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&buff,sizeof(unsigned));
     int nbobject = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&nbelmts,sizeof(int));

     //printf("%d \n",nbelmts);


     map_allocate (width, height);

     //printf("%d \n",nbelmts);
     for(int i= 0 ; i<nbelmts;i++)
     {
        r=read(fd,&obj,sizeof(int));

        r=read(fd,&x,sizeof(int));

        r=read(fd,&y,sizeof(int));


        map_set (x, y,obj);
        //printf("%d \n",i);
     }


     map_object_begin (nbobject);

     for(int i= 0 ; i<nbobject;i++)
            {
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

                //printf("length : %d \n",lname);
                //name

                filename = malloc(lname+1);
                r=read(fd,filename,lname);

                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                printf("name : %s \n",filename);

                map_object_add (filename, frame, solid | dest | frame | collect | gener );
                //free(filename);
                lname=0;
            }
            map_object_end ();
            free(filename);
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
