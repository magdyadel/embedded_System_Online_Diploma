#include <stdio.h>

int main()
{
    
    int n1,n2;
    printf("Enter two number (intervals): ");
    scanf("%d",&n1);
    scanf("%d",&n2);
    
    getPrime(n1,n2);
    
    return 0;
}

void getPrime(int n1,int n2)
{
    printf("Prime number between %d and %d are: ",n1,n2);
    int i,j,temp,flag=0;
    for(i=n1;i<=n2;i++)
    {
        flag=0;
        temp=i/2;
        for(j=2;j<=temp;j++)
        {
            if(i%j==0)
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        { 
            printf("%d ",i);
        }
    }
}