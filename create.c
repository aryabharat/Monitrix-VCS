// C program to illustrate
// command line arguments
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// Create a new file if already exist give error message.

void create_new_file(char* name[])
{
  FILE *fp = fopen(name[2], "wx");
    if (fp == NULL)
    {
        puts("file already exists with this name");
        exit(0);
    }
}


int main(int argc,char* argv[])
{
    int counter;
  //  printf("Program Name Is: %s",argv[0]);

   // argc is 2 for new file.
    if(argc==3)
    {
      if(!strcmp(argv[1], ".init"))
      {
        create_new_file(argv);
      }
      else
      {
        printf("Error %s",argv[1]);
      }
    }

   /*
   code to make a new directory in the name direcorty.
   */
    if(argc>3)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
    return 0;
}
