#include <stdio.h>

void main()
{
    float a,b;
    char c;
    printf("Enter operator either + or - or * or /: ");
    scanf("%c",&c);
    printf("Enter two operands: ");
    scanf("%f",&a);
    scanf("%f",&b);

    switch(c)
    {
        case '+':
        {
                printf("\n%f %c %f = %f",a,c,b,a+b);
        }
        break;
        case '-':
        {
            printf("\n%f %c %f = %f",a,c,b,a-b);
        }
        break;
        case '*':
        {
            printf("\n%f %c %f = %f",a,c,b,a*b);
        }
        break;
        case '/':
        {
            printf("\n%f %c %f = %f",a,c,b,a/b);
        }
        break;
        default:
        {
            printf("\nWrong Input");
        }
        break;
    }


}


