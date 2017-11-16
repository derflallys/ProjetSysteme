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
        write (fd,&buff,sizeof(unsigned));



        //save height
        sprintf(&buff,"%d",map_height());
        write (fd,&buff,sizeof(unsigned));

        //save objects char: n
        sprintf(&buff,"%d",map_objects());
        write (fd,&buff,sizeof(unsigned));

        unsigned obj;
        unsigned nbelmts = 0;

         for (int x = 0; x < map_width(); x++)
           {
                for(int y = 0; y < map_height(); y++)
                {
                    obj = map_get(x,y);
                    if(obj!=-1)
                    {
                        nbelmts++;
                     }

                }
           }
        sprintf(&buff,"%d",nbelmts);
        write(fd,&buff,sizeof(unsigned));


        for (int x = 0; x < map_width(); x++)
       {
            for(int y = 0; y < map_height(); y++)
            {

                obj = map_get(x,y);
                if(obj!=-1)
                {

                    sprintf(&buff,"%d",obj);
                    write(fd,&buff,sizeof(unsigned));

                    sprintf(&buff,"%d",x);
                    write(fd,&buff,sizeof(unsigned));

                    sprintf(&buff,"%d",y);
                    write(fd,&buff,sizeof(unsigned));
                   // printf("%d \n",map_get(x,y));

                }

            }
        }
        unsigned lname;

        for(int i=0;i<map_objects();i++)
        {
            printf("%d \n",i);
            sprintf(&buff,"%d",map_get_frames(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            sprintf(&buff,"%d",map_get_solidity(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            sprintf(&buff,"%d",map_is_destructible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            sprintf(&buff,"%d",map_is_collectible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            sprintf(&buff,"%d",map_is_generator(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            lname = strlen(map_get_name(i));
            sprintf(&buff,"%d",lname);

            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");
            w=write(fd,map_get_name(i),strlen(map_get_name(i)));
            if(w==-1)
                    exit_with_error ("Erreur de lecture\n");


        }
    }
    else
    {
        perror("erreur ouverture fichier");
    }


    close(fd);
  fprintf (stderr, "Sorry: Map save is not yet implemented\n");
}

void map_load (char *filename)
{
  int fd = open(filename,O_RDONLY);
  if(fd!=-1)
  {

      char buff;
      int r ;

     r=read(fd,&buff,sizeof(unsigned));
     int width = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&buff,sizeof(unsigned));
     int height = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&buff,sizeof(unsigned));
     int nbobject = atoi(&buff);
     //write(1,&buff,r);

     r=read(fd,&buff,sizeof(unsigned));
     int nbelmts = atoi(&buff);
     //write(1,&buff,r);


     map_allocate (width, height);
     unsigned obj ;
     unsigned x;
     unsigned y;
     unsigned frame;
     unsigned solid;
     unsigned dest;
     unsigned collect;
     unsigned gener;
     unsigned lname;

     for(int i= 0 ; i<nbelmts;i++)
     {
        r=read(fd,&buff,sizeof(unsigned));
        obj = atoi(&buff);
        r=read(fd,&buff,sizeof(unsigned));
        x = atoi(&buff);
        r=read(fd,&buff,sizeof(unsigned));
        y = atoi(&buff);

        map_set (x, y,obj);

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
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                lname = atoi(&buff);
                write(1,&lname,r);
                //name
                r=read(fd,&buff,lname);
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                write(1,&buff,r);

                map_object_add (&buff, frame, solid | dest | frame | collect | gener );
            }
            map_object_end ();

     }
    else
    {
        perror("Erreur de open");
        EXIT_FAILURE;
     }

      close(fd);
  }

 // exit_with_error ("Map load is not yet implemented\n");


#endif
