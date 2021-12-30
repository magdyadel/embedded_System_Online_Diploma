#include<stdio.h>
int main(){
	char c='A';
	char *p=&c;
	int i;
	printf("The Alphabets are : \n");
	for(i=0;i<26;i++){
		printf("%c ",*p++);
	}
	return 0;
}
