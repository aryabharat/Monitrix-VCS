#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <stdint.h>
#define MAX 100                          //To define the value of MAX as 100 

/*This function calculates the maximum of 2 integers*/
int maximum(int x, int y);

/*lcs function is used to calculate the longest common subsequence
 of the two strings and store them in a seperate string*/
void lcs(char *X, char *Y) {

	int m = strlen(X);                   //To store length of X
	int n = strlen(Y);                   //To store length of Y
	int L[m+1][n+1];

	/* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
	for (int i=0; i<=m; i++) { 
		for (int j=0; j<=n; j++) { 
			if (i == 0 || j == 0) 
				L[i][j] = 0; 
			else if (X[i-1] == Y[j-1]) 
				L[i][j] = L[i-1][j-1] + 1; 
			else L[i][j] = maximum(L[i-1][j], L[i][j-1]); 
     } 
   } 

   //Variable to define length of Longest Common Subsequence
   int ix = L[m][n]; 

   //Character array to store the lcs string
   char lcs[ix+1]; 
   lcs[ix] = '\0';
  
   int i = m, j = n; 

   /* Start from the right-most-bottom-most corner 
   and one by one store characters in lcs[] */
   while (i > 0 && j > 0) { 
   	/* If given character in X[] and Y[] are same, 
   	then it must be included in LCS */ 
   	if (X[i-1] == Y[j-1]) { 
   		lcs[ix-1] = X[i-1];              // Including the given character in LCS
   		i--; 
   		j--; 
   		ix--;   
   	} 
   	// If not same, then find the larger of two and go in the direction of larger value 
   	else if (L[i-1][j] > L[i][j-1]) 
         i--; 
     else j--; 
   } 
  
   // Printing the lcs 
   printf("%s", lcs);
}

int maximum(int x, int y) {
	return (x > y) ? x : y;              //Returning the larger value
} 
   
/*Driver program to test the above functions*/
int main() { 
  FILE *ptr1, *ptr2;                     //Creates 2 file type pointers
	char file[100];                      //Character variable to store the filename
	char X, Y;

	printf("Enter the filename to open for reading:"); 
    scanf("%s", file); 

    //To open the given file in read mode
	if (ptr1 == NULL) {
	ptr1 = fopen(file, "r");            
		printf("Cannot open file \n");   //If file pointer points ti Null character
		exit(0);                         //To stop the execution of program
	} 

	printf("Enter the second filename to open for reading:"); 
    scanf("%s", file); 

    //To open the given file in read mode
	if (ptr2 == NULL) {
	ptr2 = fopen(file, "r");            
		printf("Cannot open file \n");   //If file pointer points ti Null character
		exit(0);                         //To stop the execution of program
	} 

	// Character arrays to store the contents of the files opened
	char str1[MAX];                    
	char str2[MAX];

	//To read the files line by line until the end of file is reached
	while ((fgets (str1, MAX, ptr1)!= NULL) && (fgets (str2, MAX, ptr2)!=NULL)) {
		//Calling the function to calculate Longest Common Subsequence of 2 character arrays
		lcs(str1, str2);                
	}

	//Closing the files opened
	fclose(ptr1);
	fclose(ptr2);
  
  return 0; 
} 