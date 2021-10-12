#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char str[100];
	 
	int count=0;

    printf("Enter a string : \n");
    gets(str);
    
	while(str[count]!=0){
	    count++;
	}
	printf("Length of string = %d \n",count);
 
	return 0;
}
