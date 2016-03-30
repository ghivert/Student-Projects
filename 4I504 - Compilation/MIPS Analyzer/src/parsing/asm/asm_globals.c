
/* ###--------------------------------------------------------------### */
/* file		: asm_globals.c						*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* description	: global variables					*/
/* ###--------------------------------------------------------------### */

unsigned int   ASM_ERR_LEVEL     = 0xffffffff    ;	/* visible lvls	*/
unsigned int   ASM_STATUS        = 0             ;	/* status	*/

unsigned int   ASM_SET_FLAGS     = 0             ;	/* set direc	*/

unsigned int   ASM_LINENO        = 0             ;
unsigned int   ASM_MAXERR        = ASM_ERR__MAX  ;

unsigned int   ASM_ARCHI         = ASM_ARC__MIPS1;

struct asobj  *ASM_FREOBJ        = NULL          ;
struct asisc  *ASM_FREISC        = NULL          ;
struct asosc  *ASM_FREOSC        = NULL          ;
struct asiss  *ASM_FREISS        = NULL          ;
