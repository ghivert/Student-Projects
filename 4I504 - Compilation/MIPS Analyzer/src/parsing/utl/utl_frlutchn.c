
/* ###--------------------------------------------------------------### */
/* file		: utl_frlutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_frlutchn						*/
/* description	: release a list of UTCHN structures			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_frlutchn (pt_chn)

struct utchn *pt_chn;

  {
  struct utchn *tmp_chn;

  if (pt_chn != NULL)
    {
    tmp_chn = pt_chn;
    while (tmp_chn->NEXT != NULL)
      tmp_chn = tmp_chn->NEXT;

    tmp_chn->NEXT = UTL_FRECHN ;
    UTL_FRECHN    = pt_chn     ;
    }

  return (NULL);
  }
