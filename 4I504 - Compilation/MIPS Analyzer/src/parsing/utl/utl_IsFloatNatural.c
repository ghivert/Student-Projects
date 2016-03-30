
/* ###--------------------------------------------------------------### */
/* file		: utl_IsFloatNatural.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_IsFloatNatural					*/
/* description	: return 1 if a floating point number is a natural	*/
/*                integer						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_IsFloatNatural (f_val)

float f_val;

  {
  unsigned int n_val ;
  int          flag  = 0;

  n_val = (unsigned int) f_val;
  if ((n_val & 0x7fffffff) == f_val)
    flag = 1;

  return (flag);
  }
