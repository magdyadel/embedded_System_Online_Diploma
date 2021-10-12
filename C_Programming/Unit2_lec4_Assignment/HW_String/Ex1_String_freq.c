#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char str[100];
	char ch;
	int i,count=0;

    printf("Enter a string : \n");
    gets(str);
    
    printf("Enter a character to find frequancy : \n");
	scanf("%c", &ch);
	  
	for (i=0;i<strlen(str);i++) { 
	    if (str[i]==ch){
	        count++;
	    }
	}
	printf("frequancy of %c = %d \n",ch,count);
 
	return 0;
}
