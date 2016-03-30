
/* ###--------------------------------------------------------------### */
/* file		: utl_revuttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_revuttdc						*/
/* description	: reverse the order of a list of structures		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_revuttdc (pt_tdc)

struct uttdc *pt_tdc;

  {
  struct uttdc *prv_tdc = NULL;
  struct uttdc *nxt_tdc = NULL;

  if (pt_tdc != NULL)
    {
    while ((nxt_tdc = pt_tdc->NEXT) != NULL)
      {
      pt_tdc->NEXT = prv_tdc;
      prv_tdc      = pt_tdc ;
      pt_tdc       = nxt_tdc;
      }

    pt_tdc->NEXT = prv_tdc;
    }

  return (pt_tdc);
  }
