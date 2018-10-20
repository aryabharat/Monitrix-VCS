
// C program to illustrate
// command line arguments
#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Create a new file if already exist give error message.

void create_new_file(char* name[])
{
  // Creating a directory
    if (mkdir(name[2], 0777) == -1)
        printf("\nError");

    else
      {
        strcat(name[2], "/temp");     // Created a temp folder inside of the  main Repoistry folder.
        mkdir(name[2], 0700);
        printf("\nDirectory created\n");
      }
}

int main(int argc,char* argv[])
{
    int counter;
  //  printf("Program Name Is: %s",argv[0]);

   // argc is 3 for new directory..
    if(argc==3)
    {
      if(!strcmp(argv[1], ".init"))
      {
        create_new_file(argv);
      }
      else
      {
        printf("Error %s\n",argv[1]);
      }
    }
    else
     {
         printf("Error %s\n",argv[1]);
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
    */
    return 0;
}
