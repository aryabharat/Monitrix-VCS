#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>     // Header used for log also.
#include <string.h>
#include <unistd.h>      // Header file for Commit command
#include <limits.h>     // Header File for commit command "PATH_MAX"
#include <dirent.h>
#include <sys/types.h>   //Header for log file
#include <time.h>       // Header for log ctime

// Create a new file if already exist give error message.

void create_new_file(char* name[])
{
  // Creating a directory
    if (mkdir(name[2], 0777) == -1)
        printf("\nError\n");

    else
      {
        strcat(name[2], "/temp");     // Created a temp folder inside of the  main Repoistry folder.
        mkdir(name[2], 0700);
        printf("\nDirectory created\n");
      }
}

void logs()
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(cwd);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
      {
	       printf("%s  ",de->d_name);
         struct stat attr;
         stat(de->d_name, &attr);
	       printf("Last modified time: %s", ctime(&attr.st_mtime));
      }
}

void commit()
{
    mkdir("temp/version",0777);
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(cwd);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    printf("ALL the files in the repo are:");
    while ((de = readdir(dr)) != NULL)
            {

              if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
                   continue;
               //printf("%s\n", de->d_name);

              char  source_file[50];
              strcpy (source_file, de->d_name);
              char target_file[50] = " temp/version";
              char sy[] = "cp -r ";
              strcat(sy,source_file);
              //strcat(sy, " ");
              strcat(sy,target_file);
              printf("%s\n", sy);
              system(sy);
            }

    closedir(dr);
  /*  if (getcwd(cwd, sizeof(cwd)) != NULL)
      {
          printf("Current working dir: %s\n", cwd);
      }
     else
       {
          perror("getcwd() error");
          return 1;
       }*/
}

int main(int argc,char* argv[])
{
    int counter;
  //  printf("Program Name Is: %s\n",argv[0]);

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
