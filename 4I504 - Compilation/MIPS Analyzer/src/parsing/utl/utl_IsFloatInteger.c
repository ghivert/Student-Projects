
/* ###--------------------------------------------------------------### */
/* file		: utl_IsFloatInteger.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_IsFloatInteger					*/
/* description	: return 1 if a floating point number is an integer	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_IsFloatInteger (f_val)

float f_val;

  {
  int          i_val ;
  int          flag  = 0;

  i_val = (int) f_val;
  if (i_val == f_val)
    flag = 1;

  return (flag);
  }
