
/* ###--------------------------------------------------------------### */
/* file		: utl_cpyutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_cpyutchn						*/
/* description	: make a copy of a list					*/
/* called func.	: utl_revutchn, utl_addutchn				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_cpyutchn (pt_src)

struct utchn *pt_src;

  {
  struct utchn *pt_chn = NULL;

  while (pt_src != NULL)
    {
    pt_chn = utl_addutchn (pt_chn, pt_src->DATA);
    pt_src = pt_src->NEXT;
    }

  pt_chn = utl_revutchn (pt_chn);

  return (pt_chn);
  }
