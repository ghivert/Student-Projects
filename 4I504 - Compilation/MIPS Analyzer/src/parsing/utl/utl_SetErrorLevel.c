
/* ###--------------------------------------------------------------### */
/* file		: utl_SetErrorLevel.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SetErrorLevel					*/
/* description	: set error level mask					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_SetErrorLevel (level)

unsigned int level;

  {
  UTL_ERR_LEVEL = level | UTL_ERR__UNMASKABLE;
  }
