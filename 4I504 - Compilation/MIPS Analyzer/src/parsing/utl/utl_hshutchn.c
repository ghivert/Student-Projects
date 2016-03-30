
/* ###--------------------------------------------------------------### */
/* file		: utl_hshutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_hshutchn						*/
/* description	: generate a hash code from a list			*/
/* called func.	: utl_hashkey						*/
/* ###--------------------------------------------------------------### */

unsigned int utl_hshutchn (pt_chn)

struct utchn *pt_chn;

  {
  unsigned int hsh_code = 0;

  while (pt_chn != NULL)
    {
    hsh_code = utl_hashkey (pt_chn->DATA.UINT , hsh_code);
    pt_chn = pt_chn->NEXT;
    }

  return (hsh_code);
  }
