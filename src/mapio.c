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
  map_object_add ("images/coin.png", 20, MAP_OBJECT_AIR &  MAP_OBJECT_COLLECTIBLE);


  map_object_end ();
}

void map_save (char *filename)
{
    unsigned int buffInt;
    char buff;

   int fd = open(filename,O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd !=-1)
    {
        //save width char: w
        write (fd,"w",1);
        sprintf(&buff,"%d",map_width());
        //save width unsignedint val
        write (fd,&buff,sizeof(unsigned));

         //save height char: h
            write (fd,"h",1);
            sprintf(&buff,"%d",map_height());
        //save height unsignedint val
        write (fd,&buff,sizeof(unsigned));
        //save objects char: n
        write (fd,"n",1);

         sprintf(&buff,"%d",map_objects());
        //save objects unsignedint val
        write (fd,&buff,sizeof(unsigned));




    }
    else
    {
        perror("errerui");
        }
        int obj;
   for (int x = 0; x < map_height(); x++)
   {
        for(int y = 0; y < map_width(); y++)
        {
            obj = map_get(x,y);
            printf("%d \n",map_get_name(obj));
        }
   }
    close(fd);
  fprintf (stderr, "Sorry: Map save is not yet implemented\n");
}

void map_load (char *filename)
{
  int fd = open(filename,O_RDONLY);
  if(fd!=-1)
  {
      unsigned buffInt ;
      char buff;
      write(1,"entree \n",7);
      int i=0;
      int r ;
      lseek(fd,SEEK_SET,1);
     r=read(fd,&buff,sizeof(unsigned));

         write(1,&buff,r);


       /*
      int r = read(fd,&buff,1);
      if(r>0)
          r= read(fd,&buffInt,sizeof(unsigned int));

      write(1,&buffInt,sizeof(unsigned int ));
       write(1,"  after \n",7);
        */
      close(fd);
  }

 // exit_with_error ("Map load is not yet implemented\n");
}

#endif
