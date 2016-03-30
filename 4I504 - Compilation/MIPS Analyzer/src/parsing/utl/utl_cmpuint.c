
/* ###--------------------------------------------------------------### */
/* file		: utl_cmpuint.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_cmpuint						*/
/* description	: compare two unsigned integers				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_cmpuint (dat1, dat2)

union utdat dat1;
union utdat dat2;

  {
  return (dat1.UINT - dat2.UINT);
  }
