#include <stdio.h>

void main()
{
    int n;
    printf("Enter an Integer : ");
    scanf("%d",&n);

    if(n>0)
    {
        int i,f=1;
        for(i=1;i<=n;i++)
        {
            f*=i;
        }
        printf("Factorial = %d",f);

    }
    else if(n<0)
    {
        printf("Error!!! Factorial of negative number doesn't exist");
    }
    else if(n==0)
    {
        printf("Factorial = 1");
    }
    else
    {
        printf("Wrong Input!!!");
    }
}


