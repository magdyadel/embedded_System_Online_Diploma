#include <stdio.h>

int main()
{
	float a[10];
	float avg=0;
	int i,n;

	printf("Enter the the number of data: \n");
	scanf("%d", &n);
	for (i=0;i<n;i++)
	{
		printf("Enter number: ");
		scanf("%f", &a[i]);
	}

	for(i=0;i<n;i++){
		avg += a[i];
	}
	printf("Average: %0.2f",avg/n);
	return 0;
}
