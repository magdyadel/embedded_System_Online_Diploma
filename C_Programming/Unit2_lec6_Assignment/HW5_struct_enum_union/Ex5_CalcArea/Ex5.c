#include <stdio.h>

#define Pi 3.14159
#define calcArea(r) Pi*r*r

int main()
{
    
	double rad;
	printf("Enter the radius: ");
	scanf("%lf", &rad);
	printf("Area = %.2lf", calcArea(rad));

	return 0;
}