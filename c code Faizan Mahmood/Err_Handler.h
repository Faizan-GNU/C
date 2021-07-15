#ifndef _ERR_HANDLER_H_
#define _ERR_HANDLER_H_

/**********************************************************************************************************************
TYYDEF
**********************************************************************************************************************/
typedef unsigned char t_BYTE;
typedef unsigned short t_WORD;
typedef unsigned long t_DWORD;

/* Define Severity levels */

typedef enum
{
   INFORMATION	=	0,
   LOW			=	1,
   MEDIUM		=	2,
   HIGH			=	3,
   CRITICAL		=	4,
   FINISH		=	5
}Err_Severity;


/* Structure for parameters of an error */

#pragma pack (1)
typedef struct Parameters
{
   t_BYTE   Module_ID;
   t_WORD   Error_ID;
   t_DWORD  Time_Stamp;
   t_WORD	Time_Delta;
   t_BYTE	Error_Frequency;
   Err_Severity  Severity;
}Parameters;

#pragma pack ()

/**********************************************************************************************************************
PROTOTYPES
**********************************************************************************************************************/
extern void ERR_Details(struct Parameters*);
extern struct Parameters* ERR_Init();
extern t_BYTE ERR_Get(t_WORD, t_BYTE);
extern void ERR_Set(struct Parameters*, t_WORD, t_BYTE);
extern void ERR_Remove(struct Parameters*);
extern bool ERR_Deinit(struct Parameters*);
extern void ERR_CountEngineStart(bool*);
extern void ERR_Handler(t_BYTE, t_WORD, t_DWORD);

#endif
/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
