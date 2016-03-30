
/* ###--------------------------------------------------------------### */
/* file		: utl_free.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_free						*/
/* description	: release a memory allocation				*/
/* called func.	: free							*/
/* ###--------------------------------------------------------------### */

void utl_free (pt)

void *pt;

  {
  free (pt);
  }
