#define MAX 200

int maximum(int x, int y); 

void lcs(char *X, char *Y, int ctr) {

	int m = strlen(X); 
	int n = strlen(Y); 
	int L[m+1][n+1];
	
	//Creating the memorization table
	for (int i=0; i<=m; i++) { 
		for (int j=0; j<=n; j++) { 
			if (i == 0 || j == 0) 
				L[i][j] = 0; 
			else if (X[i-1] == Y[j-1]) 
				L[i][j] = L[i-1][j-1] + 1; 
			else L[i][j] = maximum(L[i-1][j], L[i][j-1]); 
		} 
	}

	int ix = L[m][n]; 
  
	char lcs[ix+1]; 
	char addition[m];
	char deletion[n];
	lcs[ix] = '\0';

	//Initializing variable sized character array named addition 
	for (int i = 0; i < m; ++i) {
		addition[i] = '0';
	}
	
	//Initializing variable sized character array named deletion
	for (int i = 0; i < n; ++i) {
		deletion[i] = '0';
	}
  
	int i = m, j = n; 
	while (i > 0 && j > 0) { 
  		if (X[i-1] == Y[j-1]) {
			lcs[ix-1] = X[i-1];  //Including in lcs
			i--; 
			j--; 
			ix--; 
		} 
		else if (L[i-1][j] > L[i][j-1]) {
			addition[i-1] = X[i-1]; // Including in addition
			i--;
		}
		else {
			deletion[j-1] = Y[j-1];  // Including in deletion
			j--;
		}
	}

	int q = 0;
	int r = 0;

	 for (int i = 0; i < m; ++i) {
	 	//printf("At line %d :", ctr);
	 	if (addition[i] != '0') {
	 		if (r == 0) {
	 			printf("At line %d :", ctr);
	 			//printf("%s", lcs);
	 			r++;
	 		}
	 		printf("\033[1;32m%c\033[0m",addition[i]); //Printing addition
	 	}
	}

	if(strlen(lcs) == 0){
		printf("At line %d :", ctr);
		printf("\033[1;32m%s\033[0m", X);
	}

	int p = 0;
	for (int i = 0; i < n; ++i) {
		if (deletion[i] != '0') {
			if (p == 0) {
			printf("\nAt line %d :", ctr);
			p++;
		}
			printf("\033[1;31m%c\033[0m",deletion[i]); //Printing deletion
		}
	}

   //Printing the lcs
	if (q == 0) {
		printf("\nAt line %d :", ctr);
		printf("%s\n", lcs);
		q++;
	}
}


//Returns the maximum of 2 integers
int maximum(int x, int y) {
	return (x > y) ? x : y;
} 
  
//Open and read the given files
void openfiles(char *file1, char *file2) { 
  
  FILE *ptr1, *ptr2;

	ptr1 = fopen(file1, "r");
	ptr2 = fopen(file2, "r");

	if (ptr1 == NULL && ptr2 == NULL) {
		printf("File does not exists. \n");
		exit(0);
	}

	if (ptr1 == NULL) {
		printf("New file was created. \n");
		exit(0);
	} 

	fseek(ptr1, 0, SEEK_END);
	int len1 = ftell(ptr1);
	printf("Total size of %s = %d bytes\n", file1, len1);
	rewind(ptr1);


	if (ptr2 == NULL) {
		printf("File was deleted. \n");
		exit(0);
	} 

	fseek(ptr2, 0, SEEK_END);
	int len2 = ftell(ptr2);
	printf("Total size of %s = %d bytes\n", file2, len2);
	rewind(ptr2);

	printf("\n");
	char str1[MAX];
	char str2[MAX];

	char c;
	int count1 = 1, count2 = 1;

	for (c = getc(ptr1); c != EOF; c = getc(ptr1))  {
        if (c == '\n') 
            count1 = count1 + 1; 
	}

    for (c = getc(ptr2); c != EOF; c = getc(ptr2)) {
        if (c == '\n') 
            count2 = count2 + 1; 
    }

    rewind(ptr1);
    rewind(ptr2);

	int ctr = 1;

	while ((fgets (str1, MAX, ptr1)!= NULL) && (fgets (str2, MAX, ptr2)!=NULL)) {
		lcs(str1, str2, ctr);
		ctr++;
	
	}

	rewind(ptr1);
    rewind(ptr2);
    
    int cmt = 0;
    int cnt = 0;

    int c_ounter;

	if (count1 > count2) {
	
		char line[500]; /*Suitable maximum line size */
        while (fgets(line, sizeof line, ptr1) != NULL) /* read a line */{
            if (cmt >= count2)
            {   
            	cmt++;
            	printf("\nAt line %d:", cmt);
                
            printf("\033[1;32m%s\033[0m",line);
            }   
            else
            {   
                cmt++;
            }   
        } 
	} else if (count2 > count1) {
		
		char line[500]; /*suitable maximum line size */
        while (fgets(line, sizeof line, ptr2) != NULL) /* read a line */{
            if (cmt >= count1)
            {   
            	cmt++;
            	printf("\nAt line %d:", cmt);
            printf("\033[1;31m%s\033[0m",line);
            }   
            else
            {   
                cmt++;
            }   
          }
	}
	else printf("\n");
	printf("\n");
	
	fclose(ptr1);
	fclose(ptr2);
   
} 
