/*
 * main.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Magdy
 */

#include "Student.h"

int main()
{
	int Choice;
	SStd_buffer_t FIFOStudent;

	FIFO_init(&FIFOStudent ,stList , 50);



	DPRINTF("--------Welcome to Student Management System------------\n");
	while(1)
	{
		DPRINTF("\nChoose The Task that you want to perform\n");
		DPRINTF("1. Add the student Details Manually\n");
		DPRINTF("2. Add the student Details From Text File\n");
		DPRINTF("3. Find the Student Details by Roll Number\n");
		DPRINTF("4. Find the Student Details by First Name\n");
		DPRINTF("5. Find the student Details by Course ID\n");
		DPRINTF("6. Find the Total number of Students\n");
		DPRINTF("7. Delete the Students Details by Roll Number\n");
		DPRINTF("8. Update the Students Details by Roll Number\n");
		DPRINTF("9. Show all information\n");
		DPRINTF("10. To Exit\n");
		DPRINTF("Enter your choice to perform the task: ");

		scanf("%d",&Choice);
		switch(Choice)
		{
		case 1:
			DPRINTF("==============================\n");
			DPRINTF("Add the student Details\n");
			DPRINTF("==============================\n");
			AddStdManualy(&FIFOStudent);
			break;
		case 2:
			AddStudentFile(&FIFOStudent);
			break;
		case 3:
			DPRINTF("--------------------------------------\n");
			getByRoll(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 4:
			DPRINTF("--------------------------------------\n");
			getByFName(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 5:
			DPRINTF("-----------------------------------\n");
			getByCourse(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 6:
			DPRINTF("---------------------------------------\n");
			getTotalNum(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 7:
			DPRINTF("---------------------------------\n");
			DeleteStudent(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 8:
			DPRINTF("----------------------------\n");
			updateStudent(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 9:
			DPRINTF("----------------------------\n");
			ShowAll(&FIFOStudent);
			DPRINTF("--------------------------------------\n");
			break;
		case 10:
			exit(1);
		}
	}
	return 0;
}
