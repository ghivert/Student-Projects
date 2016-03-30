
/* ###--------------------------------------------------------------### */
/* file		: utl_lenuttpd.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_lenuttpd						*/
/* description	: count the number of structures in a list		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_lenuttpd (pt_tpd)

struct uttpd *pt_tpd;

  {
  unsigned int len = 0;

  while (pt_tpd != NULL)
    {
    len ++;
    pt_tpd = pt_tpd->NEXT;
    }

  return (len);
  }
