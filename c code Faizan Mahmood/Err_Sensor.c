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

Component   Main Module

Filename    Err_Sensor.c

brief       software module dealing with sensor related errors

author      Faizan Mahmood

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  			Description
--------  ----------  ----  			-----------
01.00.00  2021-06-24  Faizan Mahmood    calls the error handler when different sensor erros occur

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES  					Preprocessor Directives
**********************************************************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Err_Sensor.h"

/**********************************************************************************************************************
TYYDEF
**********************************************************************************************************************/
typedef unsigned char t_BYTE;
typedef unsigned short t_WORD;
typedef unsigned long t_DWORD;

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
void Err_Sensor()
{
	char option;								/* To store input to check which error code has appeared */
	const static t_BYTE Module_ID = 0xCC;		/* Fixed ID of engine module */
    t_WORD Error_ID;
    t_DWORD Time_Stamp;	
	
	repeat:
		
	printf("\n\n Which Error code has appeared:\n 1) CC01\n 2) CC02\n 3) CC03\t");
	option = getche();
	
	if(option == '1')
	{
		Error_ID = 0xCC01;
		Time_Stamp = GetTickCount();
		ERR_Handler(Module_ID, Error_ID, Time_Stamp);
	}
	
	else if(option == '2')
	{
		Error_ID = 0xCC02;
		Time_Stamp = GetTickCount();
		ERR_Handler(Module_ID, Error_ID, Time_Stamp);
	}
	
	else if(option == '3')
	{
		Error_ID = 0xCC03;
		Time_Stamp = GetTickCount();
		ERR_Handler(Module_ID, Error_ID, Time_Stamp);
	}
	
	else
	{
		printf("\n\n Invalid input");
		goto repeat;
	}

}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
