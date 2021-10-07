#include <stdio.h>

void main()
{
    char c;
    printf("Enter a character: ");
    scanf("%c",&c);
    if( c=='i' || c=='e' || c=='u' || c=='o' || c=='a' )
    {
        printf("%c is a Vowel",c);
    }
    else
    {
        printf("%c is a Constant",c);
    }
}
