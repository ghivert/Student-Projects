
/* ###--------------------------------------------------------------### */
/* file		: utl_CharToInt.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_CharToInt						*/
/* description	: convert a (binary, octal, decimal or hexadecimal)	*/
/*		  digit into an integer					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_CharToInt (c)

unsigned char  c;

  {
  return (UTL_CHR_VALUE [c]);
  }
