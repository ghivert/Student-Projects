
/* ###--------------------------------------------------------------### */
/* file		: asm_addasiss.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_addasiss						*/
/* description	: create an ASISS structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct asiss *asm_addasiss (list)

struct asiss *list ;

  {
  struct asiss *pt_iss;
  int           i     ;

	/* ###------------------------------------------------------### */
	/*    make a block allocation					*/
	/* ###------------------------------------------------------### */

  if (ASM_FREISS == NULL)
    {
    ASM_FREISS = (struct asiss *)
                  utl_alloc (sizeof (struct asiss) * ASM_BLC__ISS);

    pt_iss = ASM_FREISS;
    for (i=1 ; i<ASM_BLC__ISS ; i++)
      {
      pt_iss->NEXT = pt_iss + 1;
      pt_iss ++;
      }
    pt_iss->NEXT = NULL;
    }

	/* ###------------------------------------------------------### */
	/*    initialize and return the first available structure	*/
	/* ###------------------------------------------------------### */

  pt_iss           = ASM_FREISS       ;
  ASM_FREISS       = ASM_FREISS->NEXT ;

  pt_iss->NEXT     = list             ;

  pt_iss->ADDR     = 0                ;
  pt_iss->SIZE     = 0                ;
  pt_iss->FLAG     = 0                ;

  return (pt_iss);
  }
