
/* ###--------------------------------------------------------------### */
/* file		: utl_spluttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_spluttyp						*/
/* description	: split a list into two parts				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_spluttyp (pt_ty1, pt_ty2)

struct uttyp *pt_ty1;
struct uttyp *pt_ty2;

  {
  struct uttyp *res_typ = NULL;

  if (pt_ty1 != NULL)
    {
    while (pt_ty1->NEXT != NULL)
      {
      if (pt_ty1->NEXT == pt_ty2)
        {
        pt_ty1->NEXT = NULL  ;
        res_typ      = pt_ty2;
        break;
        }
      pt_ty1 = pt_ty1->NEXT;
      }
    }

  return (res_typ);
  }
