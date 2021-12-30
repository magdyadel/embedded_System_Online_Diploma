
#include<stdio.h>
char readString(char s);

char readString(char s)
{
    char *str =&s;
    scanf("%c", &s);
    if (s != '\n') 
    {
        readString(*(str++));
    }
    printf("%c",s);
    return s;
} 
int main(){

	char str;
	printf("\nInput a string : ");
	readString(str);
	return 0;
}
