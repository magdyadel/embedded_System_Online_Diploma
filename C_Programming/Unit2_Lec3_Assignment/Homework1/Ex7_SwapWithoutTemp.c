#include <stdio.h>

void main()
{
    float a,b;
    printf("Enter value of a: ");
    scanf("%f",&a);
    printf("Enter value of b: ");
    scanf("%f",&b);

    //Another Way to SWAP
    //a=a+b;
    //b=a-b;
    //a=a-b;
    //printf("\nAfter swapping, value of a = %f",a);
    //printf("\nAfter swapping, value of b = %f",b);

    printf("\nAfter swapping, value of a = %f",b);
    printf("\nAfter swapping, value of b = %f",a);
}


