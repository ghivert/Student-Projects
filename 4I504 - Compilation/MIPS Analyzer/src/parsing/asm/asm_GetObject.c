
/* ###--------------------------------------------------------------### */
/* file		: asm_GetObject.c					*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_GetObject						*/
/* description	: return the object structure corresponding to an	*/
/*		  assembly file						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct asobj *asm_GetObject (pt_fig, ident)

struct asfig *pt_fig;
char         *ident ;

  {
  struct asobj  *pt_obj  = NULL;

  if (pt_fig != NULL)
    {
    pt_obj = pt_fig->OBJECTS;
    while (pt_obj != NULL)
      {
      if (pt_obj->IDENT == ident)
        break;
      pt_obj = pt_obj->NEXT;
      }
   }
 
  return (pt_obj);
  }
