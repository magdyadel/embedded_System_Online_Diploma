#include <stdio.h>

struct SStudent 
{
	char m_Name[25];
	unsigned int m_Roll;
	float m_Marks;
};

struct SStudent readData(unsigned char roll)
{
	struct SStudent std;

	printf("\n\nFor roll number %u\n", roll);
	printf("Enter name: ");
	scanf("%s",std.m_Name);
	std.m_Roll = roll;
	printf("Enter marks: ");
	scanf("%f", &std.m_Marks);

	return std;
}

void printData(struct SStudent studentData)
{
	printf("Information for roll number %u:\n", studentData.m_Roll);
	printf("Name: %s\n", studentData.m_Name);		
	printf("Marks: %f\n\n", studentData.m_Marks);
}

void printData(struct SStudent studentData);
struct SStudent readData(unsigned char roll);
int main()
{
	struct SStudent stdList[10];
	int num,i = 0;
	unsigned char current = 0;
	printf("Enter number of students: ");
    scanf("%d", &num);
	printf("\n\nEnter information of students:");
	for(i=0;i<num;i++){
	     stdList[i]=readData(++current);
	     
	}
	printf("\n\nDisplaying information of students:\n\n");
	for(i=0; i < num; i++)
	{
		printData(stdList[i]);
	}
	return 0;
}