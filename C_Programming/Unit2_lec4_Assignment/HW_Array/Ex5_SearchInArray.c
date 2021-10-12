#include <stdio.h>

int main()
{
	int a[10];
	int i,j,size,s,loc;

	printf("Enter no of elements : \n");
	scanf("%d", &size);
	
	for (i=0;i<size;i++)
	{
	    scanf("%d", &a[i]);
	}
	
	printf("Enter the element to be Searched : \n");
	scanf("%d", &s);
	
	
	for (i=0;i<size;i++) {
	    if (a[i]==s){
        	printf("Number found at the location = %d \n",i+1);
	    }
	}
	
	return 0;
}
