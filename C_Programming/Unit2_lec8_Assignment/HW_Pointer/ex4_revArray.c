#include<stdio.h>

int main(){

    
	int size;

	printf("input the number of the elements to store in the array(max 15) : ");
	scanf("%d", &size);

	int arr[size];
	int i;
	for(i = 0; i < size; i++)
	{
		printf("\nelement - %d : ", i+1);
		scanf("%d", &arr[i]);
	}
	
	int* p_arr;
	p_arr = &arr[size - 1];

	for(i = 0; i < size; i++)
	{
		printf("\nelement - %d : %d", size-i-1, *p_arr);
		p_arr--;
	}
	return 0;
}
