#include <stdio.h>

int main()
{
    int n,p;
    printf("Enter base number: ");
    scanf("%d", &n);
    printf("Enter power number(positive integer): ");
    scanf("%d", &p);
    printf("%d",getPower(n,p-1));
    return 0;
}

int getPower(int n,int p)
{
    if(p)
    {
        return n*getPower(n,p-1);
    }
}  