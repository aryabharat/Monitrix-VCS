#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

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
  
   // Printing the lcs 
   printf("%s", lcs);
} 

   
int maximum(int x, int y) {
	return (x > y) ? x : y;
} 
   
int main() 
{ 
  char X[] = "Hello World. Let's make it a better placew\nasd"; 
  char Y[] = "hello world. Why's nity?ass";  
  lcs(X, Y); 
  
  return 0; 
} 