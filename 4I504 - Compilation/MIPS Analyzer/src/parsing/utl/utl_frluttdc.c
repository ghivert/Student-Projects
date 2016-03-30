
/* ###--------------------------------------------------------------### */
/* file		: utl_frluttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_frluttdc						*/
/* description	: release a list of UTTDC structures			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_frluttdc (pt_tdc)

struct uttdc *pt_tdc;

  {
  struct uttdc *tmp_tdc;

  if (pt_tdc != NULL)
    {
    tmp_tdc = pt_tdc;
    while (tmp_tdc->NEXT != NULL)
      tmp_tdc = tmp_tdc->NEXT;

    tmp_tdc->NEXT = UTL_FRETDC ;
    UTL_FRETDC    = pt_tdc     ;
    }

  return (NULL);
  }
