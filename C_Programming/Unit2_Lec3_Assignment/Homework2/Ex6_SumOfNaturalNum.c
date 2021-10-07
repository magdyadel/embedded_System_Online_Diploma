#include <stdio.h>

void main()
{
    int n;
    printf("Enter an Integer : ");
    scanf("%d",&n);

    int i,sum=0;
    for(i=1;i<=n;i++)
    {
        sum+=i;
    }
    printf("Sum = %d",sum);
}


