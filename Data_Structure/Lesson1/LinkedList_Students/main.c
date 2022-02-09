/*
 *  main.c
 *  Author: Magdy Adel
 */
#include <stdint.h>
#include "linkedlist.h"


int main()
{
	char temp[10];
	while(1){
		DPRINTF("\tSELECT YOUR OPTION\n");
		DPRINTF("1:Add Student\n");
		DPRINTF("2:Delete Student\n");
		DPRINTF("3:print All Student\n");
		DPRINTF("4:Delete All Student\n");
		DPRINTF("5:GetNth... \n");
		DPRINTF("6:Get length of Student list... \n");
		DPRINTF("7:Reverse All of Student... \n");
		DPRINTF("\nEnter option number: ");
		gets(temp);
		DPRINTF("\n");
		switch(atoi(temp))
		{
			case 1:
				AddStudent();
				break;
			case 2:
				DeleteStudent();
				break;
			case 3:
				showAllStudent();
				break;
			case 4:
				DeleteAll();
				break;
			case 5:
			{
				uint32_t index;
				DPRINTF("\nEnter Index :");
				scanf("%d",&index);
				if(!index)
				{
					DPRINTF("\nWrong Index");
				}else
					GetNth(index);
			}
				break;
			case 6:
				DPRINTF("\n\t Length of Student list is : %d \n\n",getLength( getFirst() ) );
				break;
			case 7:
				RevAllStudents(getFirst() );
				break;
			default:
				DPRINTF("\t\"WRONG OPTION PLEASE TRY AGAIN\"\n");
				break;
		}
		DPRINTF(" ============================================\n\n\n");
	}
	return 0;
}
