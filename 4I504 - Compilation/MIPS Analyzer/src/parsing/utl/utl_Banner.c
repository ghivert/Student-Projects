
/* ###--------------------------------------------------------------### */
/* file		: utl_Banner.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_Banner						*/
/* description	: print a string with huge characters			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_Banner (str)

char *str;

  {
  printf ("%s\n", str);
  }
