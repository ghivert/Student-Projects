
/* ###--------------------------------------------------------------### */
/* file		: asm_GetInputSection.c					*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_GetInputSection					*/
/* description	: return the input section from its identifier		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct asisc *asm_GetInputSection (pt_fig, ident)

struct asfig *pt_fig;
char         *ident ;

  {
  struct asisc  *pt_isc  = NULL;

  if (pt_fig != NULL)
    {
    pt_isc = pt_fig->IN_SEC;
    while (pt_isc != NULL)
      {
      if (pt_isc->IDENT == ident)
        break;
      pt_isc = pt_isc->NEXT;
      }
    }
 
  return (pt_isc);
  }
