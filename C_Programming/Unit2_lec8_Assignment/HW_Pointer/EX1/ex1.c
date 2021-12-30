#include "stdio.h"


int main(void)
{
	int m = 29;
	printf("Address of m : %x \n", &m);
	printf("Value of m : %d \n", m);


	int *ab;	
	ab = &m;
	printf("\nNow ab is assigned with the address of m.");
	printf("\nAddress of pointer ab : %x", ab);
	printf("\nContent of pointer ab : %d", *ab);

	*ab = 7;
	printf("\n\nThe pointer variable ab is assigned with value 7 : ");
	printf("\nAddress of m : %x", &m);
	printf("\nValue of m : %d", m);

return 0;
}