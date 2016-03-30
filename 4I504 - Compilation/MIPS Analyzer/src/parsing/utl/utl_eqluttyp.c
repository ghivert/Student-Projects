
/* ###--------------------------------------------------------------### */
/* file		: utl_eqluttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_eqluttyp						*/
/* description	: return 0 if two lists are equal			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_eqluttyp (pt_ty1, pt_ty2)

struct uttyp *pt_ty1;
struct uttyp *pt_ty2;

  {
  int res = 0;

  while ((pt_ty1 != NULL) && (pt_ty2 != NULL))
    {
    res    |= (pt_ty1->DAT1.SINT - pt_ty2->DAT1.SINT) |
              (pt_ty1->DAT2.SINT - pt_ty2->DAT2.SINT)  ;

    pt_ty1  =  pt_ty1->NEXT;
    pt_ty2  =  pt_ty2->NEXT;
    }

  if ((pt_ty1 != NULL) || (pt_ty2 != NULL))
    res = 1;

  return (res);
  }
