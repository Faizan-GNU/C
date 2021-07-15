/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
*  Copyright (c) 2021, Faizan Mahmood . All rights reserved!                                                          *
*                                                                                                                     *
*    All rights exclusively reserved for Faizan Mahmood, unless expressly otherwise agreed.                           *
*                                                                                                                     *
*    Redistribution in source or any other form, with or without modification, is not permitted.                      *
*                                                                                                                     *
*    You may use this code under the according license terms of Faizan Mahmood. Please contact                        *
*    phaizan.mahmood@gmail.com to get the appropriate terms and conditions.                                           *
*                                                                                                                     *
***********************************************************************************************************************

Component   Handler Module

Filename    Err_Handler.c

brief       consists all function related to error handling

author      Faizan Mahmood

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  			Description
--------  ----------  ----  			-----------
01.00.00  2021-06-24  Faizan Mahmood    This module initializes an error structure and fills up all its parameters
										in respective fields. It also checks the severity of errors and depending
										on the frequency of the error and the time delay between two same errors 
										it increases the error severity or removes the error.

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES  					Preprocessor Directives
**********************************************************************************************************************/
#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Err_Handler.h"

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/
#define Total_Errors 5

/**********************************************************************************************************************
TYYDEF
**********************************************************************************************************************/
typedef unsigned char t_BYTE;
typedef unsigned short t_WORD;
typedef unsigned long t_DWORD;

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function creats new parameter pointer using dynamic memory allocation and initializes the elements with NULL.
	The total number of new memory allocation are equal to the totoal number of errors. 
	It returns the base address of parameter variable */

struct Parameters* ERR_Init() 
{  
	struct Parameters *ptr;
	
	ptr = (struct Parameters*)calloc(Total_Errors,sizeof(struct Parameters)); 
	
	if (ptr == NULL) 
	{
        printf("Error! memory not allocated.");
        exit(0);
	}
	
	else	printf("\n\n Error initialized.\n");

	return ptr;
	
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function receives error id and error frequency as parametres and returns the error severity.
	The error severity depends on the error id and error frequency*/

t_BYTE ERR_Get(t_WORD Error_ID, t_BYTE Error_Frequency)	
{
	t_BYTE Severity;
	
	/*	Switch case checks the error id to determine default severity.
		And the if() statmemts determine the severity depending on error frequency*/
	
	switch(Error_ID)
	{
		case 0xCC01:
			if(Error_Frequency<=3) Severity = (t_BYTE)INFORMATION;
			else if(Error_Frequency>3 && Error_Frequency<=6) Severity = (t_BYTE)LOW;
			else if(Error_Frequency>6 && Error_Frequency<=9) Severity = (t_BYTE)MEDIUM;
			else if(Error_Frequency>9 && Error_Frequency<=12) Severity = (t_BYTE)HIGH;
			else if(Error_Frequency>12 && Error_Frequency<=15) Severity = (t_BYTE)CRITICAL;
			else Severity = (t_BYTE)FINISH;
			break;
			
   		case 0xCC02:
   			if(Error_Frequency<=3) Severity = (t_BYTE)LOW;
			else if(Error_Frequency>3 && Error_Frequency<=6) Severity = (t_BYTE)MEDIUM;
			else if(Error_Frequency>6 && Error_Frequency<=9) Severity = (t_BYTE)HIGH;
			else if(Error_Frequency>9 && Error_Frequency<=12) Severity = (t_BYTE)CRITICAL;
			else Severity = (t_BYTE)FINISH;
			break;
			
   		case 0xCC03:
   			if(Error_Frequency<=3) Severity = (t_BYTE)MEDIUM;
			else if(Error_Frequency>3 && Error_Frequency<=6) Severity = (t_BYTE)HIGH;
			else if(Error_Frequency>6 && Error_Frequency<=9) Severity = (t_BYTE)CRITICAL;
			else Severity = (t_BYTE)FINISH;
			break;
						
   		case 0xEE01:
   			if(Error_Frequency<=3) Severity = (t_BYTE)HIGH;
			else if(Error_Frequency>3 && Error_Frequency<=6) Severity = (t_BYTE)CRITICAL;
			else Severity = (t_BYTE)FINISH;
			break;
			
   		case 0xEE02:
   			if(Error_Frequency<=3) Severity = (t_BYTE)CRITICAL;
			else Severity = (t_BYTE)FINISH;
			break;
	}
	
	return Severity;
	
}


/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function receives pointer to parameter structure, error id and module id as its parameters
	Then it updates all the elements of parameter structure */
	
void ERR_Set(Parameters *parameter, t_WORD Error_ID, t_BYTE Module_ID)
{
	parameter->Module_ID = Module_ID;
	parameter->Error_ID = Error_ID;
	parameter->Error_Frequency++;
	parameter->Severity = ERR_Get(Error_ID, parameter->Error_Frequency);
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function receives pointer to parameter structure and resets the element, error frequency to 0.
	Also it resets the severity of error to its default severity level.
	An error is only removed if the time difference between two similar errors is more than 30 secs*/

void ERR_Remove(Parameters *parameter)
{
	if(parameter->Time_Delta > 30000)
	{
		if(parameter->Error_ID == 0xCC01)		parameter->Severity = (t_BYTE)INFORMATION;
		else if(parameter->Error_ID == 0xCC02)	parameter->Severity = (t_BYTE)LOW;
		else if(parameter->Error_ID == 0xCC03)	parameter->Severity = (t_BYTE)MEDIUM;
		else if(parameter->Error_ID == 0xEE01)	parameter->Severity = (t_BYTE)HIGH;
		else if(parameter->Error_ID == 0xEE02)	parameter->Severity = (t_BYTE)CRITICAL;
		
		parameter->Error_Frequency = 0;
		
		parameter->Time_Delta = 0;
	}	
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function receives the base pointer of parameter structure and then free it from the memory alocation which rests the module.
	It return bollean variable to signal that error has be deinitialized and new memory alocation is required for the coming errors*/

bool ERR_Deinit(Parameters* ptr) 
{
	free(ptr);
	printf("\n\n Error module reset.\n");
	
	return true;
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function can be called from other modules when an error needs to be handled.
	It takes module id, error id and time stamp at which the error raised as input parameters
	Depending on the error ID which is unique for every error. It tells the description of the error
	It also calculates the  time difference between two similar errors
	If the error severity exceeds the limit it requires the user to reset the module or exit the system*/
	
void ERR_Handler(t_BYTE Module_ID, t_WORD Error_ID, t_DWORD Time_Stamp)
{	
	static struct Parameters *ptr;		/* Pointer to parameter structure */
	static bool init = true;			/* To keep a check on error init function */
	t_BYTE i;							/* Loop iteration variable */
	char reset;							/* To input the signal to check whether to reset the module or exit */
	
	/* To make sure that error init function runs only once */
	
	if(init == true)	
	{
		ptr = ERR_Init();
		init = false;
	}
	
	/* Swtich case tells the error description depending on the error id.
	It also calculates the time difference between two similar errors
	if() within each case statment makes sure that the time delta starts after the first error */

	switch(Error_ID)
	{
		case 0xCC01:
			printf("\n  Car Proximity Sensor Failure. Please fix it for better assistance.\n");
			
			if(ptr->Time_Stamp > 0)
			ptr->Time_Delta = Time_Stamp - ptr->Time_Stamp;	
			
			ptr->Time_Stamp = Time_Stamp;
			ERR_Remove(ptr);
			ERR_Set(ptr,Error_ID,Module_ID);		
			ERR_Details(ptr);	
			
		break;
		
		case 0xCC02:
			printf("\n Air bag Failure. Please get it fixed for your safety\n");
			
			if((ptr+1)->Time_Stamp > 0)
			(ptr+1)->Time_Delta = Time_Stamp - (ptr+1)->Time_Stamp;	
			
			(ptr+1)->Time_Stamp = Time_Stamp;
			ERR_Remove((ptr+1));
			ERR_Set((ptr+1), Error_ID, Module_ID);
			ERR_Details(ptr+1);
			
		break;
		
		case 0xCC03:
			printf("\n Break Oil is less. Please check your breaks or it will be a problem in future.\n");
			
			if((ptr+2)->Time_Stamp > 0)
			(ptr+2)->Time_Delta = Time_Stamp - (ptr+2)->Time_Stamp;
			
			(ptr+2)->Time_Stamp = Time_Stamp;
			ERR_Remove((ptr+2));
			ERR_Set((ptr+2),Error_ID, Module_ID);
			ERR_Details(ptr+2);
			
		break;
		
		case 0xEE01:
			printf("\n Engine Oil needs to be changed. Please chnage it at first priority\n");
			
			if((ptr+3)->Time_Stamp > 0)
			(ptr+3)->Time_Delta = Time_Stamp - (ptr+3)->Time_Stamp;
			
			(ptr+3)->Time_Stamp = Time_Stamp;
			ERR_Remove((ptr+3));
			ERR_Set((ptr+3),Error_ID, Module_ID);
			ERR_Details(ptr+3);
			
		break;
		
		case 0xEE02:
			printf("\n Electrical System Failure.\n\n");
			
			if((ptr+4)->Time_Stamp > 0)
			(ptr+4)->Time_Delta = Time_Stamp - (ptr+4)->Time_Stamp;
			
			(ptr+4 )->Time_Stamp = Time_Stamp;
			ERR_Remove((ptr+4));
			ERR_Set((ptr+4),Error_ID, Module_ID);
			ERR_Details(ptr+4);
			
		break;	
	}
	
	/*  for() loop runs the total number of error times
		within for() loop is if() statment which checks if the severity of the error exceeds the boundry or not
		If the boundry is exceeded the asks the user to either reset the system or exit the system */
	
	for(i=0; i<Total_Errors; i++)
	{	
		if((ptr+i)->Severity == FINISH)
		{
			printf("\n This is Catastrophe\n");
			printf("\n\n Press r to reset or Press any key to exit\t");
			reset = getche();
			
			if(reset == 'r')
			{
				init = ERR_Deinit(ptr);
				printf("\n\n System is reset.\n\n");
			}
			
			else
			{
				printf("\n\n System will shutdown in 5 seconds\t");
				sleep(5);
				exit(1);
			}	
		}
		
	}	
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/*	This function prints all the elements of the error parameter structure */

void ERR_Details(struct Parameters* ptr) 		
{
	printf("\n ##############################################################################\n");
	printf("\n Error ID          %x" , ptr->Error_ID);
	printf("\n Module ID         %x" , ptr->Module_ID);
	printf("\n Error frequency:  %d" , ptr->Error_Frequency);
	printf("\n Error severity:   %d" , ptr->Severity);
	printf("\n Time Stamp:       %lu", ptr->Time_Stamp);
	printf("\n Time delta:       %d" , ptr->Time_Delta);
	printf("\n\n ##############################################################################\n\n");
}

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
/* This function counts the number engine starts. */

void ERR_CountEngineStart(bool* ignition) 	
{
	static t_BYTE Start_Attempt = 0;		/* To store the number of start attempts */
	char start_check;						/* To check if the car has started or not */
	
	printf("\n\n All Good\n\n Car is ready to start\n");
	printf("\n\n Has the car started or not? press y/n\t");
	start_check = getche();
	
		/* Outer if() checks if the car has started or not.
		   Inner if() counts the number of start attempts and limits the start attempts */
			
			if(start_check == 'y')
			{
				printf("\n\n Drive Safe\n");
				Start_Attempt = 0;
				*ignition = true;
			}
	
			else if(start_check == 'n')
			{
				Start_Attempt++;
	
				if(Start_Attempt<=3)
				{
					printf("\n\n Start attempt : %d out of 3",Start_Attempt);	
					*ignition = false;
				}
				
				else
				{
					printf("\n\n Too many start attempts. Please try again after 10 secs");
					sleep(10);
					Start_Attempt = 0;
					*ignition = 0;
				}
			}
			
			else
			{
				printf("\n\n Invalid input\n");
			}
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
