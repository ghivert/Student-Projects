
/* ###--------------------------------------------------------------### */
/* file		: utl_SetStringMode.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SetStringMode					*/
/* description	: set the string conversion mode			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_SetStringMode (mode)

unsigned int mode;

  {
  UTL_STR_MODE = mode;
  }
