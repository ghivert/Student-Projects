
/* ###--------------------------------------------------------------### */
/* file		: asm_addasobj.c					*/
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
/* function	: asm_addasobj						*/
/* description	: create an ASOBJ structure				*/
/* called func.	: utl_alloc, utl_CreateSimpleDic			*/
/* ###--------------------------------------------------------------### */

struct asobj *asm_addasobj (list, ident)

struct asobj *list ;
char         *ident;

  {
  struct asobj *pt_obj;
  int           i     ;

	/* ###------------------------------------------------------### */
	/*    make a block allocation					*/
	/* ###------------------------------------------------------### */

  if (ASM_FREOBJ == NULL)
    {
    ASM_FREOBJ = (struct asobj *)
                  utl_alloc (sizeof (struct asobj) * ASM_BLC__OBJ);

    pt_obj = ASM_FREOBJ;
    for (i=1 ; i<ASM_BLC__OBJ ; i++)
      {
      pt_obj->NEXT = pt_obj + 1;
      pt_obj ++;
      }
    pt_obj->NEXT = NULL;
    }

	/* ###------------------------------------------------------### */
	/*    initialize and return the first available structure	*/
	/* ###------------------------------------------------------### */

  pt_obj          = ASM_FREOBJ                          ;
  ASM_FREOBJ      = ASM_FREOBJ->NEXT                    ;

  pt_obj->NEXT    = list                                ;
  pt_obj->IDENT   = ident                               ;

  pt_obj->SYM_DIC = utl_CreateSimpleDic (UTL_DIC__SMALL);
  pt_obj->SEC_SYM = NULL                                ;

  pt_obj->FLAG    = 0                                   ;

  return (pt_obj);
  }
