#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char str[100];
	char rev[100]; 
	int i,j=0;
	
    printf("Enter a string : \n");
    gets(str);
    
	for(i=strlen(str)-1;i>=0;i--){
	    rev[j]=str[i];
	    j++;
	}
	printf("Reverse string is: %s \n",rev);
 
	return 0;
}
