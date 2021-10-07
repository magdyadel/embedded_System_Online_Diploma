#include <stdio.h>

void main()
{
    float n1,n2,n3;
    printf("Enter three Number: ");
    scanf("%f",&n1);
    scanf("%f",&n2);
    scanf("%f",&n3);

    if(n1>n2)
    {
        printf("Largest num = %f",(n1>n3)?n1:n3);
    }
    else
    {
        printf("Largest num = %f",(n2>n3)?n2:n3);
    }
}
