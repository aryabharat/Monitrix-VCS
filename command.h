#include <sys/stat.h>     // Header used for log also.
#include <string.h>
#include <unistd.h>      // Header file for Commit command
#include <limits.h>     // Header File for commit command "PATH_MAX"#include <dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>   //Header for log file
#include <time.h>       // Header for log ctime
//retrieve an old version
void reload_util(char v_no[10])
{
	struct dirent *de;  // Pointer for directory entry

	 // opendir() returns a pointer of DIR type.
	 char v_name[30]= "temp/version";

	   strcat(v_name[30], v_no);
		 printf("%s\n", v_name);
	 DIR *dr = opendir("");

	 if (dr == NULL)  // opendir returns NULL if couldn't open directory
	 {
			 printf("Could not open current directory" );
			 exit(0);
	 }
	 // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
	 // for readdir()
	 while ((de = readdir(dr)) != NULL)
					 printf("%s\n", de->d_name);

	 closedir(dr);
}
void reload()
{
	printf("Choose a verison to retrieve\n");
	FILE *fr;
	int filecount;
	fr = fopen("temp/.count.txt", "r");
	fscanf(fr,"%d",&filecount); /*read from file*/
	fclose(fr);
  for(int i = 0; i < filecount; i++)
  {
    printf(" version%d\n",i+1);
  }
	int v_no;
	scanf("%d",&v_no);
	if(v_no <= filecount && v_no > 0)
	 {
		 char temp;
		 printf("Are you sure to reload the version[Y/N]\n>");
		 scanf(" %c", &temp);
		 if(temp == 'y' || temp == 'Y')
		 {
			 reload_util(v_no);
			 printf("\nVersion Reloaded");
		 }
		 else
		 {
			 printf("\nReloading cancled");
		 }
	 }
	 else
	 {
		 	 printf("\nVeriosn Does not exist");
	 }
}


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
        strcat(name[2], "/.count.txt");
        FILE * fPtr;
        fPtr = fopen(name[2], "w");
        fputs("0", fPtr);
        fclose(fPtr);
        printf("\nDirectory created\n");
      }
}

void diff(char *name[])
{
  char previous_file[20] = "temp/version";
  char tempstr[20];
  FILE *fr;
  int filecount;
  fr = fopen("temp/.count.txt", "r");
  fscanf(fr,"%d",&filecount); /*read from file*/
  fclose(fr);
  sprintf(tempstr, "%d", filecount);
  strcat(previous_file,tempstr);
  strcat(previous_file,"/");
  strcat(previous_file,name[2]);
  //printf("%s\n",previous_file);
  openfiles( previous_file,name[2]);
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
        printf("\nCould not open current directory\n" );
        return;
    }
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
      {
        if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
             continue;
	       printf("%s  ",de->d_name);
         struct stat attr;
         stat(de->d_name, &attr);
	       printf("\nLast modified time: %s\n", ctime(&attr.st_mtime));
      }
}

void commit()
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(cwd);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("\nCould not open current directory\n" );
        return;
    }
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    //printf("ALL the files in the repo are:");
    //code to count the verison number
    FILE *fr;
    int filecount;
    fr = fopen("temp/.count.txt", "r");
		if (fr == NULL)
    {
        printf("Error \n");
        exit(0);
    }
    fscanf(fr,"%d",&filecount); /*read from file*/
    //printf("%d",n); /*display on screen*/
    fclose(fr);
    filecount++;
    fr = fopen("temp/.count.txt", "w");
    fprintf(fr, "%d",filecount); /*  write to file*/
    fclose(fr);
    char tempstr[10];
    char  source_file[50];
    sprintf(tempstr, "%d", filecount);  // convert number into string
    char target_file[50] = "temp/version";
    strcat(target_file,tempstr);
    mkdir(target_file,0777);
    while ((de = readdir(dr)) != NULL)
            {
              if(!strcmp(de->d_name,"temp") || !strcmp(de->d_name,".") || !strcmp(de->d_name,"..") )
                   continue;
               //printf("%s\n", de->d_name);
              //char  source_file[50];
              strcpy (source_file, de->d_name);
              //char target_file[50] = " temp/version";
              char sy[] = "cp -r ";
              strcat(sy,source_file);
              //strcat(sy, " ");
              strcat(sy," ");
              strcat(sy,target_file);
            //  printf("%s\n", sy);
              system(sy);
            }
    printf("COMMIT SAVED\n");
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
