#include <stdio.h>

void main()
{
    char c;
    printf("Enter a character: ");
    scanf("%c",&c);
    if( (c>=65&&c<=90) || (c>=97&&c<=120))
    {
        printf("%c is an Alphapit",c);
    }
    else
    {
        printf("%c is not an Alphapit",c);
    }
}
