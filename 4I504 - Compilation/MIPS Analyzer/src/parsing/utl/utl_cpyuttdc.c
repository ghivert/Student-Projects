
/* ###--------------------------------------------------------------### */
/* file		: utl_cpyuttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_cpyuttdc						*/
/* description	: make a copy of a list					*/
/* called func.	: utl_revuttdc, utl_adduttdc				*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_cpyuttdc (pt_src)

struct uttdc *pt_src;

  {
  struct uttdc *pt_tdc = NULL;

  while (pt_src != NULL)
    {
    pt_tdc = utl_adduttdc (pt_tdc, pt_src->DAT1, pt_src->DAT2, pt_src->DAT3);
    pt_src = pt_src->NEXT;
    }

  pt_tdc = utl_revuttdc (pt_tdc);

  return (pt_tdc);
  }
