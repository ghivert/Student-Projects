
/* ###--------------------------------------------------------------### */
/* file		: utl_GetMemSize.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetMemSize					*/
/* description	: return the size of memory allocated until now		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_GetMemSize ()

  {
  return (UTL_MEMSIZE);
  }
