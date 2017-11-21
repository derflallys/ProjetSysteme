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
    int buf;
    int w;
    /*
        Ouverture du fichier en ecriture seul avec comme option trunc pour sauvegarder une nouvelle version à chaque sauvegarde
    */
    int fd = open(filename,O_CREAT|O_WRONLY|O_TRUNC,0666);
    if(fd !=-1)
    {
        //save width char: w
        /*
            Ici j'ecris dans le fichier le width et je fais de meme pour height , le nombre de type d'object
            Je sais ça prend plus de temps de sauvegarder un int en tant char car à la lecture je dois faire la transcription inverse , mais c'etait jusque pour voir
            en claire les int ecrient , donc j'ai fait la convertion en utilisant la fonction sprintf
        */
        //sprintf(&buff,"%d",map_width());
        buf= map_width();
        w=write (fd,&buf,sizeof(int));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        if(w==0)
            exit_with_error (" Zero caractere lu \n");
        //save height
        //sprintf(&buff,"%d",map_height());
        buf= map_height();
        w=write (fd,&buf,sizeof(int));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        if(w==0)
            exit_with_error (" Zero caractere lu \n");

        //save objects char: n
        //sprintf(&buff,"%d",map_objects());
        buf= map_objects();
        w=write (fd,&buf,sizeof(int));
        if(w==-1)
            exit_with_error ("Erreur d'ecriture\n");
        if(w==0)
            exit_with_error (" Zero caractere lu \n");

        unsigned obj;
        /*
            Je parcours la matrice pour sauvegarder le nombre d'elements(objects) , ce qui me servira pour recuperer lors du load
            les coordonnées de l'objects et le type de l'object
        */
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
        /*
            J'ecris dans le fichier les coordonnées de chque l'objects et le type de l'object de la matrice sachant  la valeur -1 signifie pas d'object
        */
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
                    if(w==0)
                        exit_with_error (" Zero caractere lu \n");
                    write(fd,&x,sizeof(int));
                    if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
                    if(w==0)
                        exit_with_error (" Zero caractere lu \n");
                    write(fd,&y,sizeof(int));
                   if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
                   if(w==0)
                        exit_with_error (" Zero caractere lu \n");
                }

            }
        }
        //lnames me permet sauvegarder la taille de chaque chaine juste avant ce dernier afin de facilier la lecture (load )
        int lnames=0;
        /*
            Cette boucle me permet d'ecrire dans le fichier les differents caracteristiques de chaque objects ainsi que leur noms en parcourant le
            nombre de type d'object
        */
        for(int i=0;i<map_objects();i++)
        {
            //frame
            //meme remarque en utilisant la fonction sprintf
            sprintf(&buff,"%d",map_get_frames(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
            exit_with_error (" Zero caractere lu \n");
            //solidity
            sprintf(&buff,"%d",map_get_solidity(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                exit_with_error (" Zero caractere lu \n");
            //destrictible
            sprintf(&buff,"%d",map_is_destructible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                    exit_with_error (" Zero caractere lu \n");
            //collectible
            sprintf(&buff,"%d",map_is_collectible(i));
            w=write(fd,&buff,sizeof(unsigned));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                    exit_with_error (" Zero caractere lu \n");
            //generator
            sprintf(&buff,"%d",map_is_generator(i));
            w=write(fd,&buff,sizeof(unsigned));

            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                    exit_with_error (" Zero caractere lu \n");

            //longueur name
            //calcul la longueur du nom de l'image en utilisation strlen
            lnames = strlen(map_get_name(i));

            w=write(fd,&lnames,sizeof(int));
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                    exit_with_error (" Zero caractere lu \n");

            //name
            w=write(fd,map_get_name(i),lnames);
            if(w==-1)
                    exit_with_error ("Erreur d'ecriture\n");
            if(w==0)
                    exit_with_error (" Zero caractere lu \n");

        }
    }
    else
    {
        exit_with_error ("erreur ouverture fichier");
    }
    close(fd);
   fprintf (stdout, "Maps saved\n");
}

void map_load (char *filename)
{
  //ouverture du fichier en lecture seul
  int fd = open(filename,O_RDONLY);
  if(fd!=-1)
  {
      //buff me permet de recuperer les donnees ecrit en char lors du save
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

    //lecture du fichier dans lordes d'ecriture , si j'avais ecrit dans le fichier des ints en char apres lecture je les converties en int avec la fonction atoi
     int width;
     r=read(fd,&width,sizeof(int));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     if(r==0)
        exit_with_error ("Aucun caractere lu\n");
     //int width = atoi(&buff);
     printf(" w: %d \n",width);

     int height;
     r=read(fd,&height,sizeof(int));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     if(r==0)
        exit_with_error ("Aucun caractere lu\n");
     //int height = atoi(&buff);

    int nbobject ;
     r=read(fd,&nbobject,sizeof(int));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     if(r==0)
        exit_with_error ("Aucun caractere lu\n");
     //int nbobject = atoi(&buff);


     r=read(fd,&nbelmts,sizeof(int));
     if(r==-1)
        exit_with_error ("Erreur de lecture\n");
     if(r==0)
        exit_with_error ("Aucun caractere lu\n");


    //J'initialise la matrice
     map_allocate (width, height);

    //cette boucle me permet de recuperer les coordonnees des objects avec leur type et de les placer dans la matrice avec mapset en utilisant le nombre d'elements
     for(int i= 0 ; i<nbelmts;i++)
     {
        r=read(fd,&obj,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");
        if(r==0)
            exit_with_error ("Aucun caractere lu\n");

        r=read(fd,&x,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");
        if(r==0)
            exit_with_error ("Aucun caractere lu\n");
        r=read(fd,&y,sizeof(int));
        if(r==-1)
             exit_with_error ("Erreur de lecture\n");
        if(r==0)
            exit_with_error ("Aucun caractere lu\n");
        map_set (x, y,obj);

     }

    //J'initialise le nombre de type d'object
     map_object_begin (nbobject);
    //Dans la boucle de parcours le nombre de type d'object et je recupere leur caracteristique et le name et je l'ajoute avec la fonction map_object_add
     for(int i= 0 ; i<nbobject;i++)
            {
                char * filename ;

                //frame
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");
                frame = atoi(&buff);

                //solid
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");
                solid = atoi(&buff);

                //dest
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");
                dest = atoi(&buff);

                //collect
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");
                collect = atoi(&buff);
                //gener
                r=read(fd,&buff,sizeof(unsigned));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");
                gener = atoi(&buff);

                //lname
                r=read(fd,&lname,sizeof(int));
                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");


                //name
                //J'alloue de la memoire à filename avec le nombre de caractere de la chaine lie dans le fichier  avec malloc
                filename = malloc(lname);
                if(filename==NULL)
                    {
                        fprintf(stderr,"Erreur malloc \n");
                        EXIT_FAILURE;
                    }
                r=read(fd,filename,lname);
                //ensuite j'achete le caractere de fin de chaine
                filename[lname]='\0';

                if(r==-1)
                    exit_with_error ("Erreur de lecture\n");
                if(r==0)
                    exit_with_error ("Aucun caractere lu\n");

                //Comme c'est les coins et marble qui on des caracteristiques differents de ceux de bases je verifie leur caracteristique et je le mets
                if(strcmp(filename,"images/coin.png")==0)
                    map_object_add (filename, frame,   collect  ==1 ? solid | MAP_OBJECT_COLLECTIBLE : solid  );
                else
                if(strcmp(filename,"images/marble.png")==0)
                    map_object_add (filename, frame,   dest  ==1 ? solid | MAP_OBJECT_DESTRUCTIBLE : solid  );
                else
                    map_object_add (filename, frame,    solid   );

                //je libere l'espace allouer recemment
                free(filename);


            }
            map_object_end ();

            fprintf(stdout,"Map Load \n");
     }
    else
    {
        exit_with_error("Erreur de open");
        EXIT_FAILURE;
     }

      close(fd);

}

#endif
