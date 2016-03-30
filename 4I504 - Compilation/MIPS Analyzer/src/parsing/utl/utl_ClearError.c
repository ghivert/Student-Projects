
/* ###--------------------------------------------------------------### */
/* file		: utl_ClearError.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_ClearError					*/
/* description	: clear the error flag in the status			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_ClearError ()

  {
  UTL_STATUS &= ~UTL_STS__ERROR;
  }
