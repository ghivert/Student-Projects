
/* ###--------------------------------------------------------------### */
/* file		: asm_GetObjectSectionSymbols.c				*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_GetObjectSectionSymbols				*/
/* description	: return the list of symbols in a section		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *asm_GetObjectSymbolList (pt_obj, ident)

struct asobj *pt_obj;
char         *ident ;

  {
  struct uttyp  *pt_typ  = NULL;

  if (pt_obj != NULL)
    {
    pt_typ = pt_obj->SEC_SYM;
    while (pt_typ != NULL)
      {
      if ((char *) pt_typ->DAT1.VPNT == ident)
        break;
      pt_typ = pt_typ->NEXT;
      }

    if (pt_typ == NULL)
      {
      pt_obj->SEC_SYM = utl_adduttyp (pt_obj->SEC_SYM, ident, NULL);
      pt_typ          = pt_obj->SEC_SYM ;
      }
    }
 
  return (pt_typ);
  }
