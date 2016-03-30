
/* ###--------------------------------------------------------------### */
/* file		: utl_revutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_revutchn						*/
/* description	: reverse the order of a list of structures		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_revutchn (pt_chn)

struct utchn *pt_chn;

  {
  struct utchn *prv_chn = NULL;
  struct utchn *nxt_chn = NULL;

  if (pt_chn != NULL)
    {
    while ((nxt_chn = pt_chn->NEXT) != NULL)
      {
      pt_chn->NEXT = prv_chn;
      prv_chn      = pt_chn ;
      pt_chn       = nxt_chn;
      }

    pt_chn->NEXT = prv_chn;
    }

  return (pt_chn);
  }
