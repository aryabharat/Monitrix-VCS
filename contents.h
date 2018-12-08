#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    
    if(!dot || dot == filename) 
    	return "";
    
    return dot + 1;
}

void dirwalk(char *dir,int depth)
{
	DIR *dp;
	char str[30]; 
	char name[30]; 
	struct dirent *entry;
	struct stat statbuf;

	int count = 0;
	double c_count = 0;
	double java_count = 0;
	double sh_count = 0;
	double cpp_count  = 0;
	double php_count = 0;
	double html_count = 0;
	double css_count = 0;
	double xml_count  = 0;

	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr,"Cannot open directory: %s\n",dir);
		return;
	}

	chdir(dir);

	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			/* Found a directory ,but ignore . and .. */
			if(strcmp(".",entry->d_name) ==0 || strcmp("..",entry->d_name) == 0)
				continue;
			printf("\n%*s %s/\n",depth,"",entry->d_name);

			/*funtion is called recursively at a new indent level */
			dirwalk(entry->d_name,depth + 4);
		} 
		else if(S_ISREG(statbuf.st_mode)) {
			printf("%*s %s \n",depth,"",entry->d_name); 
		}

		count++;

		const char *s = get_filename_ext(entry->d_name);
		
		if (s[0]=='c' || s[0]=='h')
			c_count++;

		if (strcmp(s, "java") == 0)
			java_count++;

		if (strcmp(s, "sh") == 0)
			sh_count++;

		if (strcmp(s, "cpp") == 0)
			cpp_count++;

		if (strcmp(s, "php") == 0)
			php_count++;

		if (strcmp(s, "css") == 0)
			css_count++;

		if (strcmp(s, "html") == 0)
			html_count++;

		if (strcmp(s, "xml") == 0)
			xml_count++;

	}

	printf("\n  THE LANGUAGES USED ARE:\n");
	
	if(c_count)
		printf("   C: %lf%%", c_count*100/count);

	if(java_count)
		printf("   JAVA: %lf%%", java_count*100/count);

	if(cpp_count)
		printf("   C++: %lf%%", cpp_count*100/count);

	if(sh_count)
		printf("   SHELL: %lf%%", sh_count*100/count);

	if(php_count)
		printf("   PHP: %lf%%", php_count*100/count);

	if(css_count)
		printf("   CSS: %lf%%", css_count*100/count);

	if(html_count)
		printf("   HTML: %lf%%", html_count*100/count);

	if(xml_count)
		printf("   XML: %lf%%", xml_count*100/count);

	printf("\n\n");

chdir("..");
closedir(dp);
}