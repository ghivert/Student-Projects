
/* ###--------------------------------------------------------------### */
/* file		: utl_eqlutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_eqlutchn						*/
/* description	: return 0 if two lists are equal			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_eqlutchn (pt_ch1, pt_ch2)

struct utchn *pt_ch1;
struct utchn *pt_ch2;

  {
  int res = 0;

  while ((pt_ch1 != NULL) && (pt_ch2 != NULL))
    {
    res    |= (pt_ch1->DATA.SINT - pt_ch2->DATA.SINT);

    pt_ch1  =  pt_ch1->NEXT;
    pt_ch2  =  pt_ch2->NEXT;
    }

  if ((pt_ch1 != NULL) || (pt_ch2 != NULL))
    res = 1;

  return (res);
  }
