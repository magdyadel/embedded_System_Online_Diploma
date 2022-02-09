/*
 *  linkedlist.h
 *  Author: Magdy Adel
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


#define DPRINTF(...)	{fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

/* User Configuration */
//effective data
struct Sdata{
	int ID;
	char name[40];
	float hight;
};

//Linked list node
typedef struct{
	struct Sdata student;
	struct sstd * PNextStudent;
} sstd;

sstd SStudent;

//APIs
void AddStudent();
int DeleteStudent();
void showAllStudent();
void DeleteAll();
void GetNth(uint32_t index);
int getLength(sstd * pFirst);
sstd* getFirst();
void RevAllStudents(sstd *pFirst );

#endif /* LINKEDLIST_H_ */
