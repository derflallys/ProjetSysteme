#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>






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
           printf("width \n");
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