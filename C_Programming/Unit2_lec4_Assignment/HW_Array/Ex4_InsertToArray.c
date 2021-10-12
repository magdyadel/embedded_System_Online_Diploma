#include <stdio.h>

int main()
{
	int a[10];
	int i,j,size,in,loc;

	printf("Enter no of elements : \n");
	scanf("%d", &size);
	
	for (i=0;i<size;i++)
	{
	    scanf("%d", &a[i]);
	}
	
	printf("Enter the element to be inserted : \n");
	scanf("%d", &in);
	
	printf("Enter the location : \n");
	scanf("%d", &loc);	
	
	int temp;
	for (i=0;i<size+1;i++) {
	    if (i==(loc-1)){
	        temp=a[i];
	        a[i]=in;
	    }
	    else if(i>=loc){
	        in=a[i];
	        a[i]=temp;
	        temp=in;
	    }
	}
	
	for (i=0;i<size+1;i++)
	{
	    printf("%d , ",a[i]);
	}
	
	return 0;
}
