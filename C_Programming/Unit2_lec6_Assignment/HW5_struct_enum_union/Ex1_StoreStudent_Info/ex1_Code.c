#include <stdio.h>

struct SStudent {
    char m_name[25];
    int m_roll;
    float m_marks;
}std;

int main()
{
    printf("Enter information of students: \n\n");
	printf("Enter name: ");
	scanf("%s", std.m_name);
	printf("\nEnter roll number: ");
	scanf("%d", &std.m_roll);
	printf("\nEnter marks: ");
	scanf("%f", &std.m_marks);

	printf("\nDisplaying Information");

	printf("\nname: %s", std.m_name);
	printf("\nRoll: %d", std.m_roll);
	printf("\nMarks: %0.1f", std.m_marks);
    return 0;
}
