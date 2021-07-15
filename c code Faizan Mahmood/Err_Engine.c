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

Component   Engine Error Module

Filename    Err_Engine.c

brief       Engine related error handling

author      Faizan Mahmood

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  			Description
--------  ----------  ----  			-----------
01.00.00  2021-06-26  Faizan Mahmood    calls the error handler when different sensor erros occur

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES  					Preprocessor Directives
**********************************************************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Err_Engine.h"

/**********************************************************************************************************************
TYYDEF
**********************************************************************************************************************/
typedef unsigned char t_BYTE;
typedef unsigned short t_WORD;
typedef unsigned long t_DWORD;

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
void Err_Engine()
{
	char option;								/* To store input to check which error code has appeared */
	const static t_BYTE Module_ID = 0xEE;		/* Fixed ID of engine module */
    t_WORD Error_ID;
    t_DWORD Time_Stamp;
	
	repeat:
		
	printf("\n\n Which Error code has appeared:\n 1) EE01\n 2) EE02\t");
	option = getche();
	
	if(option == '1')
	{
		Error_ID = 0xEE01;
		Time_Stamp = GetTickCount();
		ERR_Handler(Module_ID, Error_ID, Time_Stamp);
	}
	
	else if(option == '2')
	{
		Error_ID = 0xEE02;
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
