#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdint.h>
#define MAX 200

int maximum(int x, int y); 

void lcs(char *X, char *Y) {

	int m = strlen(X); 
	int n = strlen(Y); 
	int L[m+1][n+1];

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
	lcs[ix] = '\0';
  
	int i = m, j = n; 
	while (i > 0 && j > 0) { 
  		if (X[i-1] == Y[j-1]) {
			lcs[ix-1] = X[i-1];
			i--; 
			j--; 
			ix--;   
		} 
		else if (L[i-1][j] > L[i][j-1]) 
			i--; 
		else j--; 
	} 

   //Printing the lcs 
	printf("%s\n", lcs);
}

int maximum(int x, int y) {
	return (x > y) ? x : y;
} 
   
int main() { 
  FILE *ptr1, *ptr2;
	char file[100];

	printf("Enter the filename to open for reading:"); 
    	scanf("%s", file); 

	ptr1 = fopen(file, "r");
	if (ptr1 == NULL) {
		printf("Cannot open file \n");
		exit(0);
	} 

	printf("Enter the second filename to open for reading:"); 
    	scanf("%s", file); 

	ptr2 = fopen(file, "r");
	if (ptr2 == NULL) {
		printf("Cannot open file \n");
		exit(0);
	} 

	char str1[MAX];
	char str2[MAX];

	while ((fgets (str1, MAX, ptr1)!= NULL) && (fgets (str2, MAX, ptr2)!=NULL)) {
		lcs(str1, str2);
	}
	
	fclose(ptr1);
	fclose(ptr2);
  
	return 0; 
} 
