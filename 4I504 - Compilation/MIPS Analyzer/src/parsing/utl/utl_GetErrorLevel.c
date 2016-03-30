
/* ###--------------------------------------------------------------### */
/* file		: utl_GetErrorLevel.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetErrorLevel					*/
/* description	: return the error level mask				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_GetErrorLevel ()

  {
  return (UTL_ERR_LEVEL);
  }
