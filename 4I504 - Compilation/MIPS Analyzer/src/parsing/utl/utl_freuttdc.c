
/* ###--------------------------------------------------------------### */
/* file		: utl_freuttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_freuttdc						*/
/* description	: release the head structure of a list and return the	*/
/*		  next element						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_freuttdc (pt_tdc)

struct uttdc *pt_tdc;

  {
  struct uttdc *nxt_tdc = NULL;

  if (pt_tdc != NULL)
    {
    nxt_tdc      = pt_tdc->NEXT;
    pt_tdc->NEXT = UTL_FRETDC  ;
    UTL_FRETDC   = pt_tdc      ;
    }

  return (nxt_tdc);
  }
