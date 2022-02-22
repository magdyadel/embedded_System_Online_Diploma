/*
 * student.h
 *
 *  Created on: Feb 21, 2022
 *      Author: Magdy
 */

#ifndef STUDENT_H_
#define STUDENT_H_


#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"


#define DPRINTF(...)	{fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

/* User Configuration */
//student info
typedef struct {
	int Roll;
	char fname[40];
	char lname[40];
	float GPA;
	int courseID[5];
}Sdata;

//list contain students
Sdata stList[50];

//FIFO Data Types
typedef struct{
	unsigned int len;
	unsigned int count;
	Sdata* base;
	Sdata* head;
	Sdata* tail;
}SStd_buffer_t;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_NULL
}FIFO_status;


//APIs
FIFO_status FIFO_init(SStd_buffer_t * fifo , Sdata * buf, uint32_t length);
int Check_RollNum(SStd_buffer_t* FIFOBuf , int Num);
FIFO_status stdList_isFull(SStd_buffer_t * fifo );
FIFO_status AddStdManualy(SStd_buffer_t * fifo);
void getTotalNum(SStd_buffer_t * fifo);
void DeleteStudent(SStd_buffer_t * fifo);
void getByRoll(SStd_buffer_t* fifo) ;
void getByFName(SStd_buffer_t* fifo) ;
void updateStudent(SStd_buffer_t* fifo) ;
void printStudent(Sdata *current);
void AddStudentFile(SStd_buffer_t* fifo);
void getByCourse(SStd_buffer_t* fifo);
void ShowAll(SStd_buffer_t* fifo);

#endif /* STUDENT_H_ */
