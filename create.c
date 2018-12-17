#include <stdio.h>
#include <stdlib.h>
#include "Difference.h"
#include "command.h"

int main(int argc,char* argv[])
{
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
    return 0;
}
