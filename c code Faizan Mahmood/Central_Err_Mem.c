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

Filename    Central_Err_Mem.c

brief       main module dealing with input signals

author      Faizan Mahmood

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  			Description
--------  ----------  ----  			-----------
01.00.00  2021-06-24  Faizan Mahmood    Checks if there is error or not. If there is error it calls the respective 
										error module. If there is no error it checks whether the engine starts or not.
										If the engine does not start it calls the engine start count function

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES  					Preprocessor Directives
**********************************************************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "Err_Handler.c"
#include "Err_Engine.c"
#include "Err_Sensor.c"


/**********************************************************************************************************************
TYYDEF
**********************************************************************************************************************/
typedef unsigned char t_BYTE;

/**********************************************************************************************************************
FUNCTION 
**********************************************************************************************************************/
int main(void)
{
	char error_check;				/* To store input to check if there is error or not */
	char module_check;				/* To store input to check the error beglongs to what module */
	bool ignition = false;			/* To store input to check if the engine starts or not */
	
	printf("  ##############################################################################\n");
	printf("  #####                         Central Error Memory                       #####\n");
	printf("  ##############################################################################\n\n");
	
	while (1)
	{
		printf("\n\n Is there an error? Press y/n\t");
		error_check = getche();
		
		/* Outer if() checks if there is error or not.
		   Inner if() checks which module has error */
		
		if(error_check == 'y')
		{
			printf("\n\n Is it an engine module error or sensor module error? Press e/s\t");
			module_check = getche();
			
			if(module_check == 'e')	Err_Engine();
			
			else if(module_check == 's')	Err_Sensor();
			
			else	printf("\n\n Invalid input\n");
		}
	
		else if(error_check == 'n' && ignition == true)	printf("\n\n Everything is running properly\n");
		
		else if(error_check == 'n' && ignition == false)	ERR_CountEngineStart(&ignition); 	/* When the engine is start this function is no more called */
		
		else	printf("\n\n Invalid input\n");
	}

	return 0;

}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
