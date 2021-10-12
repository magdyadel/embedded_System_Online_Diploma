#include <stdio.h>

int main()
{
	float a[2][2];
	float b[2][2];
	int i,j;

	printf("Enter the elements of 1st matrix\n");

	for (i=0;i<2;i++)
	{
		for (j=0;j<2; j++)
		{
			printf("Enter a%d%d: ", i+1, j+1);
			scanf("%f", &a[i][j]);
		}
	}

	printf("Enter the elements of 2st matrix: \n");
	for (i=0;i<2;i++)
	{
		for (j=0;j<2; j++)
		{
			printf("Enter b%d%d: ", i+1, j+1);
			scanf("%f", &b[i][j]);
		}
	}

	float sum[2][2];
	for (i=0;i<2;i++)
	{
		for (j=0;j<2; j++)
		{
			sum[i][j]= a[i][j] + b[i][j];
		}
	}

	printf("Sum Of Matrix:\n");
	for (i=0;i<2;i++)
	{
		for (j=0;j<2; j++)
		{
			printf("%0.2f \t",sum[i][j]);
		}
		printf("\n");
	}

	return 0;
}
