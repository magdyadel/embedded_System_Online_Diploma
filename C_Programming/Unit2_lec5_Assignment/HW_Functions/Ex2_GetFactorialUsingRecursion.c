#include <stdio.h>

int main()
{
    int n1;
    printf("Enter a positive integer: ");
    scanf("%d",&n1);
    
    printf("Factorial of %d = %d",n1,getFactorial(n1));
    return 0;
}

int getFactorial(int n1)
{
    if (n1>=1)
        return n1*getFactorial(n1-1);
    else
        return 1;
}