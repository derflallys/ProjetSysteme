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


  // Mur
  map_object_add ("images/wall.png", 1, MAP_OBJECT_SOLID);
  // Texture pour le sol
  map_object_add ("images/ground.png", 1, MAP_OBJECT_SOLID);
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

    char buff;

   int fd = open(filename,O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd !=-1)
    {
        //save width char: w
        sprintf(&buff,"%d",map_width());
        //save width unsignedint val
        write (fd,&buff,sizeof(unsigned));
        sprintf(&buff,"%d",map_height());
        //save height unsignedint val
        write (fd,&buff,sizeof(unsigned));
        //save objects char: n
         sprintf(&buff,"%d",map_objects());
        //save objects unsignedint val
        write (fd,&buff,sizeof(unsigned));
        int obj;
        for (int x = 0; x < map_width(); x++)
       {
            for(int y = 0; y < map_height(); y++)
            {

                obj = map_get(x,y);
                if(obj!=-1)
                {
                    printf("(%d,%d) \n",x,y);
                    write(fd,&obj,sizeof(unsigned));
                   // printf("%d \n",map_get(x,y));
                    //frame
                    sprintf(&buff,"%d",map_get_frames(obj));
                    write(fd,&buff,sizeof(unsigned));
                   // printf("%d \n",map_get_frames(obj));
                    //solid
                    sprintf(&buff,"%d",map_get_solidity(obj));
                    write(fd,&buff,sizeof(unsigned));
                   // printf("%d \n",map_get_solidity(obj));
                    //destr
                    sprintf(&buff,"%d",map_is_destructible(obj));
                    write(fd,&buff,sizeof(unsigned));
                   // printf("%d \n",map_is_destructible(obj));
                    //collect
                    sprintf(&buff,"%d",map_is_collectible(obj));
                    write(fd,&buff,sizeof(unsigned));
                 //   printf("%d \n",map_is_collectible(obj));
                    //generator
                    sprintf(&buff,"%d",map_is_generator(obj));
                    write(fd,&buff,sizeof(unsigned));
                  //  printf("%d \n",map_is_generator(obj));
                    //name
                    //sprintf(&buff,"%s",map_get_name(obj));
                    write(fd,map_get_name(obj),strlen(map_get_name(obj))*sizeof(char));

                   printf("%s \n",map_get_name(obj));
                }
                else
                {

                }
            }

        }
    }
    else
    {
        perror("errerui");
    }


    close(fd);
  //fprintf (stderr, "Sorry: Map save is not yet implemented\n");
}

void map_load (char *filename)
{
  int fd = open(filename,O_RDONLY);
  if(fd!=-1)
  {

      char buff;

      int i=0;
      int r ;
      //lseek(fd,SEEK_SET,1);
     r=read(fd,&buff,sizeof(unsigned));
           int width = atoi(&buff);

         write(1,&buff,r);
         r=read(fd,&buff,sizeof(unsigned));
         int height = atoi(&buff);

         write(1,&buff,r);
         r=read(fd,&buff,sizeof(unsigned));
         int nbobject = atoi(&buff);

         write(1,&buff,r);

         map_allocate (width, height);
          for (int x = 0; x < width; x++)
            map_set (x, height - 1, 0); // Ground

          for (int y = 0; y < height - 1; y++) {
            map_set (0, y, 1); // Wall
            map_set (width - 1, y, 1); // Wall
          }

          map_object_begin (nbobject);

          int obj ;
          int frame;
          int solid;
          int dest;
          int collect;
          int gener;
          char * name [100];
          while((r=read(fd,&buff,sizeof(unsigned)))>0 )
          {
              if(i>=6)
              {
                while((r=read(fd,&buff,1))>0)
                {
                      // strcat(&name,&buff);
                      write(1,&buff,r);
                 }
                // write(1,name,sizeof(name));
                 i=0;
                // map_object_add (&name, frame,solid frame>1 ? & : |  dest!= 0 ? );

              }
               else
               {
                    if(i==0)
                        obj = atoi(&buff);

                    if(i==1)
                        frame= atoi(&buff);

                    if(i==2)
                        solid = atoi(&buff);

                    if(i==3)
                        dest = atoi(&buff);

                    if(i==4)
                        collect= atoi(&buff);

                    if(i==5)
                        gener= atoi(&buff);

                    write(1,&buff,r);
               }




              i++;

          }



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
