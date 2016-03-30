
/* ###--------------------------------------------------------------### */
/* file		: utl_SetTraceLevel.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SetTraceLevel					*/
/* description	: set the function trace level				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_SetTraceLevel (level)

unsigned int level;

  {
  UTL_TRC_LEVEL = level;
  }
