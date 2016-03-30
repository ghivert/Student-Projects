
/* ###--------------------------------------------------------------### */
/* file		: utl_lenutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_lenutchn						*/
/* description	: count the number of structures in a list		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_lenutchn (pt_chn)

struct utchn *pt_chn;

  {
  unsigned int len = 0;

  while (pt_chn != NULL)
    {
    len ++;
    pt_chn = pt_chn->NEXT;
    }

  return (len);
  }
