
/* ###--------------------------------------------------------------### */
/* file		: utl_freutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_freutchn						*/
/* description	: release the head structure of a list and return the	*/
/*		  next element						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_freutchn (pt_chn)

struct utchn *pt_chn;

  {
  struct utchn *nxt_chn = NULL;

  if (pt_chn != NULL)
    {
    nxt_chn      = pt_chn->NEXT;
    pt_chn->NEXT = UTL_FRECHN  ;
    UTL_FRECHN   = pt_chn      ;
    }

  return (nxt_chn);
  }
