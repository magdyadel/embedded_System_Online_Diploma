/*
 * linkedlist.c
 *  Author: Magdy Adel
 */

#include "linkedlist.h"

sstd* gpFirstStudent=NULL; //global pointer to point at first student


void AddStudent()
{
	sstd * pNewStudent;
	sstd* pLastStudent;
	char temp_text[40];
	/* check list is empty */
	// "Is Empty"
	if(gpFirstStudent==NULL)
	{
		//create new record
		pNewStudent=(sstd*)malloc(sizeof(sstd));

		//assign it to gpfirst
		gpFirstStudent=pNewStudent;

	}else//list not Empty
	{
		//navigate until reach to the last record
		pLastStudent=gpFirstStudent;
		while(pLastStudent->PNextStudent)
			pLastStudent=pLastStudent->PNextStudent;
		//create new record
		pNewStudent=(sstd*)malloc(sizeof(sstd));
		pLastStudent->PNextStudent=pNewStudent;
	}

	/* fill new record */

	DPRINTF("\n Enter the ID: ");
	gets(temp_text);
	pNewStudent->student.ID=atoi(temp_text);

	DPRINTF("\n Enter student name: ");
	gets(pNewStudent->student.name);

	DPRINTF("\n Enter the height: ");
	gets(temp_text);
	pNewStudent->student.hight=atof(temp_text);

	//set the next pointer (new student) == null
	pNewStudent->PNextStudent=NULL;
}

int DeleteStudent()
{
	char temp_text[40];
	int selected_id;

	//get selected ID from user
	DPRINTF("\n Enter the ID to be deleted: ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	//list is not empty
	if(gpFirstStudent)
	{
		sstd * pSelected=gpFirstStudent;
		sstd * pPrev=NULL;

		while(pSelected)
		{
			//compare each node with selected ID
			if(pSelected->student.ID==selected_id)
			{
				if(pPrev) // the first student is not selected
					pPrev = pSelected->PNextStudent;
				else // 1st student is selected = ID
					gpFirstStudent = pSelected->PNextStudent;
				free(pSelected);
				return 1;

			}
			pPrev = pSelected;
			pSelected=pSelected->PNextStudent;
		}
	}
	DPRINTF("/n Cannot find student ID.");
	return 0;
}

void showAllStudent()
{
	sstd* pCurrent=gpFirstStudent;
	int count=0;
	//list is not empty
	if(gpFirstStudent)
	{
		while(pCurrent)
		{
			DPRINTF("\nRecord number : %d",count+1);
			DPRINTF("\n\t Student ID : %d",pCurrent->student.ID);
			DPRINTF("\n\t Student Name : %s",pCurrent->student.name);
			DPRINTF("\n\t Student Height %f: \n",pCurrent->student.hight);
			pCurrent=pCurrent->PNextStudent;
			count++;
		}
	}
	else
		DPRINTF("Empty List");
}

void DeleteAll()
{
	sstd* pCurrent=gpFirstStudent;
	//list is not empty
	if(gpFirstStudent)
	{
		while(pCurrent)
		{
			sstd * pTemp=pCurrent;
			pCurrent=pCurrent->PNextStudent;
			free(pTemp);
		}
		gpFirstStudent=NULL;
	}else
		DPRINTF("Empty List\n");
}

void GetNth(uint32_t index)
{
	int count=0;
	sstd* pCurrent=gpFirstStudent;
	//list is not empty
	if(gpFirstStudent)
	{
		while(pCurrent)
		{
			count++;
			if(count==index)
			{
				DPRINTF("\nRecord number : %d",index);
				DPRINTF("\n\t Student ID : %d",pCurrent->student.ID);
				DPRINTF("\n\t Student Name : %s",pCurrent->student.name);
				DPRINTF("\n\t Student Height %f: \n",pCurrent->student.hight);
				return;
			}
			pCurrent=pCurrent->PNextStudent;

		}
		DPRINTF("\nWrong input");

	}
}

sstd* getFirst()
{
	if(gpFirstStudent)
		return gpFirstStudent;
}

int getLength(sstd* pFirst)
{
	if(pFirst )
		return (1 + getLength(pFirst->PNextStudent));
	else
		return 0;
}

void RevAllStudents(sstd *pFirst )
{
	sstd *Current = pFirst;
	sstd *temp = NULL;
	sstd *Pre = NULL;
	while(Current)
	{
		temp = Current;
		Current = Current->PNextStudent;
		temp->PNextStudent = Pre;
		Pre = temp;
	}
	gpFirstStudent = temp;

}
