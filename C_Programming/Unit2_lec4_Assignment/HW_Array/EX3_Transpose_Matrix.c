#include <stdio.h>

int main()
{
	int a[10][10];
	int i,j,r,c;

	printf("Enter rows and column of matrix: \n");
	scanf("%d", &r);
	scanf("%d", &c);
	
	printf("Enter elements of matrix: \n");
	for (i=0;i<r;i++)
	{
	    for(j=0;j<c;j++){
		    printf("Enter elements a%d%d: ",i+1,j+1);
		    scanf("%d", &a[i][j]);
	    }
	    
	}
	
	printf("Entered matrix: \n");
	for (i=0;i<r;i++)
	{
	    for(j=0;j<c;j++){
	    	printf("%d \t",a[i][j]);
    	}
    	printf("\n");
	}
	
	printf("Transpose matrix: \n");
	for (i=0;i<c;i++)
	{
	    for(j=0;j<r;j++){
	    	printf("%d \t",a[j][i]);
    	}
    	printf("\n");
	}

	return 0;
}
