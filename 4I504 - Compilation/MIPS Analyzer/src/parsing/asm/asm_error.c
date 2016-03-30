
/* ###--------------------------------------------------------------### */
/* file		: asm_error.c						*/
/* date		: Mar  3 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_error						*/
/* description	: print an error message				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

#define ASM_ERR__NBR   19

unsigned int asm_error (code, func, line, s1, n1)

int           code;
char         *func;
int           line;
char         *s1  ;
int           n1  ;

  {
  static char         *msg [] =
    {
    "%.0uunknown error%.0s%.0u\n"                             ,	/*    0	*/
    "%.0umissing label%.0s%.0u\n"                             ,	/*    1	*/
    "%u: redeclaration of label `%s`%.0u\n"                   ,	/*    2	*/
    "%u: redeclaration of symbol `%s`%.0u\n"                  ,	/*    3	*/
    "%u: misaligned address : %.0s0x%.0x\n"                   ,	/*    4	*/
    "%u: immediate exceeding 16 bits : %.0s0x%.8x\n"          ,	/*    5	*/
    "%u: immediate exceeding  5 bits : %.0s0x%.8x\n"          ,	/*    6	*/
    "%u: branch target instruction unreachable%.0s%.0u\n"     ,	/*    7	*/
    "%u: immediate exceeding 20 bits : %.0s0x%.8x\n"          ,	/*    8	*/
    "%u: undifined symbol : %s%.0u\n"                         ,	/*    9	*/
    "%u: redefinition of output section : %s%.0u\n"           ,	/*   10	*/
    "%u: redefinition of input section : %s%.0u\n"            ,	/*   11	*/
    "%u: unknown section : %s%.0u\n"                          ,	/*   12	*/
    "%u: section undefined%.0s%.0u\n"                         ,	/*   13	*/
    "%u: unknown integer register : %.0s%u\n"                 ,	/*   14	*/
    "%u: unknown coprocessor register : %.0s%u\n"             ,	/*   15	*/
    "%u: %s%.0u\n"                                            ,	/*   16	*/
    "%u: Too many errors ... Have a nice day ...%.0s%.0u\n"   ,	/*   17	*/
    "%u: illegal align directive : %.0s%u\n"                  ,	/*   18	*/
    "%u: missing end directive%0.s%0.u\n"                     ,	/*   19	*/
    "%u: illegal end directive%0.s%0.u\n"                   	/*   20	*/
    } ;

  static unsigned int  lvl [] =
    {
    0x00000002                                                ,	/*    0	*/
    0x00000002                                                ,	/*    1	*/
    0x00000002                                                ,	/*    2	*/
    0x00000002                                                ,	/*    3	*/
    0x00000002                                                ,	/*    4	*/
    0x00000002                                                ,	/*    5	*/
    0x00000002                                                ,	/*    6	*/
    0x00000002                                                ,	/*    7	*/
    0x00000002                                                ,	/*    8	*/
    0x00000002                                                ,	/*    9	*/
    0x00000002                                                ,	/*   10	*/
    0x00000002                                                ,	/*   11	*/
    0x00000002                                                ,	/*   12	*/
    0x00000002                                                ,	/*   13	*/
    0x00000002                                                ,	/*   14	*/
    0x00000002                                                ,	/*   15	*/
    0x00000002                                                ,	/*   16	*/
    0x00000001                                                ,	/*   17	*/
    0x00000002                                                ,	/*   18	*/
    0x00000002                                                ,	/*   19	*/
    0x00000002                                                 	/*   20	*/
    } ;

  ASM_STATUS |= ASM_STS__ERROR;

  if (code >= ASM_ERR__NBR)
    code = 0;

  if ((lvl [code] & ASM_ERR_LEVEL) != 0)
    {
    fprintf (stderr, "ASM Error: %s: ", func        );
    fprintf (stderr,  msg [code]      , line, s1, n1);

    if (lvl [code] == 0x00000001)
      {
      fprintf (stderr, "\n\tFatal error\n");
      exit    (-1);
      }
    }

  return (1);
  }
