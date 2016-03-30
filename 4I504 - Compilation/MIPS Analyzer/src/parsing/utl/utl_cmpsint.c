
/* ###--------------------------------------------------------------### */
/* file		: utl_cmpsint.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_cmpsint						*/
/* description	: compare two signed integers				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_cmpsint (dat1, dat2)

union utdat dat1;
union utdat dat2;

  {
  return (dat1.SINT - dat2.SINT);
  }
