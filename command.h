#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>                          // Header used for log also.
#include <string.h>
#include <unistd.h>                            // Header file for Commit command
#include <limits.h>                           // Header File for commit command "PATH_MAX"#include <dirent.h>
#include <dirent.h>                           // Header for dirent
#include <sys/types.h>                         //Header for log file
#include <time.h>                             // Header for log ctime


// prints the progress bar
void progress()
{
	int max = 200000;
  long i;
  float progress = 0.0;
  int c  = 0, last_c=20, x = 0;

  fprintf(stderr, "%3d%% [", (int)progress);

  for(i = 1; i < max+1; i++){
    progress = i*100.0/max;
    c = (int) progress/3;
    // x++;
    fprintf(stderr, "\n\033[F");
    fprintf(stderr, "%3d%%", (int)progress);
    fprintf(stderr, "\033[1C");
    fprintf(stderr, "\033[%dC#", last_c);
    last_c = c;
  }
  fprintf(stderr, "]");
}

// Create a new file if already exist give error message.
void create_new_file(char* name[])
{
  // Creating a directory
    if (mkdir(name[2], 0777) == -1)
        printf("\nError\n");

    else
      {
        strcat(name[2], "/temp");                                 // Created a temp folder inside of the  main Repoistry folder.
        mkdir(name[2], 0700);
        strcat(name[2], "/.count.txt");
        FILE * fPtr;
        fPtr = fopen(name[2], "w");
        fputs("0", fPtr);
        fclose(fPtr);
        printf("Directory created\n");
      }
}

// logs shows all the last active log of a file
void logs()
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    struct dirent *de;                                                   // Pointer for directory entry
    DIR *dr = opendir(cwd);                                            // opendir() returns a pointer of DIR type
    if (dr == NULL)                                                    // opendir returns NULL if couldn't open directory
    {
        printf("\nCould not open current Repoistry\n" );
        return;
    }

    while ((de = readdir(dr)) != NULL)
      {
        if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
            {
							continue;
						}
	       printf("%s  ",de->d_name);
         struct stat attr;
         stat(de->d_name, &attr);
	       printf("\nLast modified time: %s\n", ctime(&attr.st_mtime));
      }
}

// commit create a new verison in /temp
void commit()
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    struct dirent *de;
    DIR *dr = opendir(cwd);

    if (dr == NULL)
    {
        printf("\nCould not open current repository\n" );
        return;
    }
                                                         //code to count the verison number
    FILE *fr;
    int filecount;
    fr = fopen("temp/.count.txt", "r");
		if (fr == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    fscanf(fr,"%d",&filecount);                           //read from file
    fclose(fr);
    filecount++;
    fr = fopen("temp/.count.txt", "w");
    fprintf(fr, "%d",filecount);                      //  write to file
    fclose(fr);
    char tempstr[10];
    char  source_file[50];
    sprintf(tempstr, "%d", filecount);                  // convert number into string
    char target_file[50] = "temp/version";
    strcat(target_file,tempstr);
    mkdir(target_file,0777);
    while ((de = readdir(dr)) != NULL)
            {
              if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
                   {
										 continue;
									 }
              strcpy (source_file, de->d_name);
              char sy[] = "cp -r ";
              strcat(sy,source_file);
              strcat(sy," ");
              strcat(sy,target_file);
              system(sy);
            }
		progress();                                          //prints the progress bar
    printf("COMMIT SAVED\n");
    closedir(dr);
}

// show the difference from previous version
void diff(char *name[])
{
  char previous_file[20] = "temp/version";
  char tempstr[20];
  FILE *fr;
  int filecount;
  fr = fopen("temp/.count.txt", "r");
  fscanf(fr,"%d",&filecount);
  fclose(fr);
  sprintf(tempstr, "%d", filecount);
  strcat(previous_file,tempstr);
  strcat(previous_file,"/");
  strcat(previous_file,name[2]);
  openfiles( previous_file,name[2]);
}

//retrieve an old version
void reload_util(int v_no)
{
	struct dirent *de;                          // Pointer for directory entry
	 char buffer[20] = "temp/version";
	 char strtemp[20];
	 sprintf(strtemp, "%d", v_no);
	 strcat(buffer,strtemp);
	 //printf("%s\n",buffer );
	 DIR *dr = opendir(buffer);                 // opendir() returns a pointer of DIR type.

	 if (dr == NULL)  // opendir returns NULL if couldn't open directory
	 {
			 printf("Could not open current directory" );
			 exit(0);
	 }
	 while ((de = readdir(dr)) != NULL)
					 {
						 if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,".."))
		             {
									 continue;
								 }
							char tempstr[30] = "";
							strcat(tempstr,buffer);
							strcat(tempstr,"/");
							strcat(tempstr,de->d_name);
		 					char sy[50] = "cp -r ";
		 					strcat(sy,tempstr);
							strcat(sy," ");
							strcat(sy,de->d_name);
		 					system(sy);
					 }
	 closedir(dr);
}

// reloades the previous version
void reload()
{
	printf("Choose a verison nuumber to retrieve\n");
	FILE *fr;
	int filecount;
	fr = fopen("temp/.count.txt", "r");
	fscanf(fr,"%d",&filecount);                                    /*read from file*/
	fclose(fr);
  for(int i = 0; i < filecount; i++)
  {
    printf(" version%d\n",i+1);
  }
	int v_no;
  printf("> ");
	scanf("%d",&v_no);
	if(v_no <= filecount && v_no > 0)
	 {
		 char temp;
		 printf("Are you sure to reload the version[Y/N]\n>");
		 scanf(" %c", &temp);
		 if(temp == 'y' || temp == 'Y')
		 {
				 char cwd[PATH_MAX];
		     getcwd(cwd, sizeof(cwd));
		     struct dirent *de;                                                   // Pointer for directory entry
		     DIR *dr = opendir(cwd);                                           // opendir() returns a pointer of DIR type.
		     if (dr == NULL)                                                  // opendir returns NULL if couldn't open directory
		     {
		         printf("\nCould not open current directory\n" );
		         return;
		     }
		     while ((de = readdir(dr)) != NULL)                                        //Till theres a file in the repository
		       {
		         if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
		              {
										continue;
									}
						char sy[30] = "rm -r ";
						strcat(sy,de->d_name);
						system(sy);
		       }

				 reload_util(v_no);
				 progress();
			   printf("\nVersion Reloaded\n");///
		 }
		 else
		 {
			 printf("\nReloading cancled\n");
		 }
	 }
	 else
	 {
		 	 printf("\nVeriosn Does not exist\n");
	 }
}
