
/* ###--------------------------------------------------------------### */
/* file		: utl_catuttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_catuttdc						*/
/* description	: catenate two lists					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_catuttdc (pt_td1, pt_td2)

struct uttdc *pt_td1;
struct uttdc *pt_td2;

  {
  struct uttdc *tmp_tdc = NULL;

  if (pt_td1 != NULL)
    {
    tmp_tdc = pt_td1;
    while (tmp_tdc->NEXT != NULL)
      tmp_tdc = tmp_tdc->NEXT;

    tmp_tdc->NEXT = pt_td2 ;
    }
  else
    pt_td1 = pt_td2;

  return (pt_td1);
  }
