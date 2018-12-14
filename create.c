#include<stdio.h>
#include<stdlib.h>
#include "Difference.h"
#include "command.h"
int main(int argc,char* argv[])
{
   // argc is 3 for new directory..

    if(argc==3)
    {
        if(!strcmp(argv[1], ".init"))
        {
          create_new_file(argv);
        }
       else if(!strcmp(argv[1], "diff"))
        {
          diff(argv);
        }
        else
        {
          printf("\nError %s\n",argv[1]);
        }
    }
    else if(argc == 2)
     {
       if(!strcmp(argv[1], "commit"))
        {
             commit();
        }
       else if(!strcmp(argv[1], "log"))
	      {
            logs();
	      }
        else if(!strcmp(argv[1], "reload"))
        {
          reload();
        }
       else
        {
           printf("\nError %s\n",argv[1]);
        }
     }
     else
      {
          printf("\nError %s\n",argv[1]);
      }
   /*
   code to make a new directory in the name direcorty.
   */
    /*
    if(argc>3)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
    A directory is a location in a file system, like /bin. A repository is typically a bunch of version controlled files.
    */
    return 0;
}
