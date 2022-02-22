/*
 * student.c
 *
 *  Created on: Feb 21, 2022
 *      Author: Magdy
 */

#include "student.h"

//init
FIFO_status FIFO_init(SStd_buffer_t * fifo , Sdata * buf, uint32_t length)
{
	if(!buf)
		return FIFO_NULL;

	fifo->base =buf;
	fifo->head =buf;
	fifo->tail =buf;
	fifo->len=length;
	fifo->count=0;
	return FIFO_no_error;
}

//check if roll number is exist
int Check_RollNum(SStd_buffer_t* fifo , int Num)
{
	Sdata* ptr= fifo->base;
	int flag = 1;

	for(int i=0; i<fifo->count; i++){

		if(ptr->Roll == Num){
			flag = 0;
		}
		ptr++;
	}
	return flag;
}

//check if list is fill
FIFO_status stdList_isFull(SStd_buffer_t * fifo )
{
	//check FIFO is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;
	else if(fifo->count == fifo->len)
		return FIFO_full;
	else
		return FIFO_no_error;
}

//Add Student
FIFO_status AddStdManualy(SStd_buffer_t * fifo )
{
	Sdata* current= fifo->head;
	char data[40];
	int tempRoll;

	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_NULL;

	//check FIFO is full
	if(stdList_isFull(fifo) == FIFO_full)
		return FIFO_full;

	DPRINTF("-------------Add Student Details--------------- \n");
	DPRINTF("Enter the Roll Number of student: \n");
	gets(data);
	tempRoll=atoi(data);
	if(!Check_RollNum(fifo, tempRoll))
	{
		DPRINTF("\n\"Roll Number is already exist..\" \n");
		return FIFO_no_error;
	}
	stList->Roll=tempRoll;
	DPRINTF("Enter First Name: \n");
	gets(stList->fname);
	DPRINTF("Enter Last Name: \n");
	gets(stList->lname);
	DPRINTF("Enter %c GPA : \n",stList->fname);
	gets(data);
	stList->GPA=atof(data);
	DPRINTF("Enter the Course ID of each course:\n");
	for(int i=0; i<5; ++i){
		DPRINTF("Course %d ID: ",i+1);
		gets(data);
		stList->courseID[i] = atoi(data);
	}

	//Enqueue Value
	fifo->head++;
	fifo->count++;

	DPRINTF("Student Added Successfully.\n");
	getTotalNum(fifo);
	return FIFO_no_error;
}

//get numbers of all of students
void getTotalNum(SStd_buffer_t * fifo )
{
	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return;
	DPRINTF("[INFO] The total number of student is %d\n",fifo->count);
	DPRINTF("[INFO] You can add up to 50 students\n");
	DPRINTF("[INFO] You can add %d more students\n",50-fifo->count);
}

//Delete student using roll number
void DeleteStudent(SStd_buffer_t * fifo)
{
	Sdata * current=fifo->base;
	int temp;
	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return ;

	//check FIFO is empty
	if(fifo->count == 0)
	{
		DPRINTF("\n List is already empty \n ");
		return ;
	}
	DPRINTF("Enter student Roll number: ");
	scanf("%d",&temp);
	for(int i=0;i<fifo->count;i++)
	{
		if(current->Roll==temp)
		{
			//Dequeue Value
			*current = *(fifo->tail);
			fifo->count--;
			if( fifo->tail == ( fifo->base + (fifo->len * sizeof(stList) ))) //to know head is MAX (0x0 + 5*1)=5
				fifo->tail == fifo->base ;
			else
				fifo->tail++;
			DPRINTF("student deleted successfully");
			return ;
		}
		current++;
	}
	DPRINTF("\This Roll Number %d not found\n",temp);
}

//find by roll num
void getByRoll(SStd_buffer_t* fifo)
{
	Sdata * current=fifo->base;
	int temp;
	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return ;

	//check FIFO is empty
	if(fifo->count == 0)
	{
		DPRINTF("\n List is already empty \n ");
		return ;
	}
	DPRINTF("Enter student Roll number: ");
	scanf("%d",&temp);
	for(int i=0;i<fifo->count;i++)
	{
		if(current->Roll==temp)
		{
			printStudent(current);
			return;
		}
		current++;
	}
	DPRINTF("\This Roll Number %d not found\n",temp);
}

//find by First Name
void getByFName(SStd_buffer_t* fifo)
{
	Sdata * current=fifo->base;
	char temp[40];
	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return ;

	//check FIFO is empty
	if(fifo->count == 0)
	{
		DPRINTF("\n List is already empty \n ");
		return ;
	}
	DPRINTF("Enter student First Name: ");
	gets(temp);
	for(int i=0;i<fifo->count;i++)
	{
		if(!strcmp(current->fname, temp))
		{
			printStudent(current);
			return;
		}
		current++;
	}
	DPRINTF("\%s not found\n",temp);
}

//update student information
void updateStudent(SStd_buffer_t* fifo)
{
	Sdata * current=fifo->base;
	int temp, option ;
	char t[40];
	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return ;

	//check FIFO is empty
	if(fifo->count == 0)
	{
		DPRINTF("\n List is already empty \n ");
		return ;
	}
	DPRINTF("Enter student Roll number: ");
	scanf("%d",&temp);
	for(int i=0;i<fifo->count;i++)
	{
		if(current->Roll==temp)
		{
			printStudent(current);
			DPRINTF("1.first name\n");
			DPRINTF("2.last name\n");
			DPRINTF("3.roll no\n");
			DPRINTF("4. GPA\n");
			DPRINTF("5. courses\n");

			scanf("%d",&option);
			switch(option)
			{
			case 1:
				DPRINTF("Enter the new first name: ");
				gets(current->fname);
				break;
			case 2:
				DPRINTF("Enter the new last name: ");
				gets(current->lname);
				break;
			case 3:
				DPRINTF("Enter the new roll number: ");
				gets(t);
				current->Roll = atoi(t);
				break;
			case 4:
				DPRINTF("Enter the new GPA: ");
				gets(t);
				current->GPA = atof(t);
				break;
			case 5:
				DPRINTF("Enter the Course ID of each course:\n");
				for(int i=0; i<5; ++i)
				{
					DPRINTF("Course %d ID: ",i+1);
					gets(temp);
					current->courseID[i] = atoi((int)temp);
				}
			}
			return;
		}
		current++;
	}
	DPRINTF("\This Roll Number %d not found\n",temp);
}

void printStudent(Sdata *current)
{
	DPRINTF("First name is   : %s\n",current->fname);
	DPRINTF("Last  name is   : %s\n",current->lname);
	DPRINTF("roll  number is : %d\n",current->Roll);
	DPRINTF("GPA             : %0.2f\n",current->GPA);
	DPRINTF("the course ID of each course\n");
	for(int j=0;j<5;j++)
		DPRINTF("The course ID are: %d\n",current->courseID[j]);
	DPRINTF("---------------------------------------\n");
}

//add from file
void AddStudentFile(SStd_buffer_t* fifo)
{

	FILE* fp = fopen("Add Student.txt","r");

	int Rec_no = 0 , Field_no = 0 , Student_Count = 0;
	char Line[50];
	const char* Taken;


	while(fgets(Line,sizeof Line,fp) != NULL)
	{
		Rec_no++;
		Taken = strtok(Line,",");
		Field_no = 0;
		while(Taken != NULL)
		{
			Field_no++;
			if(Field_no == 1){
				if(Check_RollNum(fifo, atoi(Taken)) == 0){
					DPRINTF("[ERROR] Roll Number %d is already Taken\n",atoi(Taken));
					Student_Count++;
					break;
				}
				else{
					fifo->head->Roll = atoi(Taken);
					DPRINTF("[INFO] Roll Number %d is saved successfully\n",atoi(Taken));
				}
			}
			else if(Field_no == 2){
				strcpy(fifo->head->fname , Taken);
			}
			else if(Field_no == 3){
				strcpy(fifo->head->lname , Taken);
			}
			else if(Field_no == 4){
				fifo->head->GPA = atof(Taken);
			}
			else if(Field_no == 5){
				fifo->head->courseID[0] = atoi(Taken);
			}
			else if(Field_no == 6){
				fifo->head->courseID[1] = atoi(Taken);
			}
			else if(Field_no == 7){
				fifo->head->courseID[2] = atoi(Taken);
			}
			else if(Field_no == 8){
				fifo->head->courseID[3] = atoi(Taken);
			}
			else if(Field_no == 9){
				fifo->head->courseID[4] = atoi(Taken);
			}

			Taken = strtok(NULL,",\n");
		}
		if(Check_RollNum(fifo, atoi(Taken)) == 0)
			continue;

		fifo->count++;
		fifo->head++;
	}
	fclose(fp);
	DPRINTF("\n[INFO] students Details is added successfully");
	DPRINTF("\n--------------------------------");
	getTotalNum(fifo);
}

void getByCourse(SStd_buffer_t* fifo){

	int CID , Count = 0;
	Sdata* Ptr = fifo->base;

	DPRINTF("Enter the course ID: ");
	scanf("%d",&CID);

	for(int i=0; i<fifo->count; ++i){

		for(int j=0; j<5; ++j){
			if(Ptr->courseID[j] == CID){
				Count++;
				printStudent(Ptr);
			}
		}
		Ptr++;
	}
	if(Count == 0){
		DPRINTF("[ERROR] Course ID %d not found\n",CID);
	}
	DPRINTF("[INFO] Total Number of Students Enrolled: %d\n",Count);
}


void ShowAll(SStd_buffer_t* fifo){
	Sdata* Ptr;

	//check FIFO list is valid
	if(!fifo->base || !fifo->head || !fifo->tail)
		return ;

	//check FIFO is empty
	if(fifo->count == 0)
	{
		DPRINTF("\n List is already empty \n ");
		return ;
	}
	Ptr=fifo->tail;
	DPRINTF("---------Student Details are-----------\n");
	for(int i=0; i<fifo->count; ++i)
		printStudent(Ptr++);
	getTotalNum(fifo );
}
