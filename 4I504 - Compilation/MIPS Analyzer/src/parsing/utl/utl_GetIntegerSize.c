
/* ###--------------------------------------------------------------### */
/* file		: utl_GetIntegerSize.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetIntegerSize					*/
/* description	: determine the number of bits required to represent	*/
/*		  an integer value					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_GetIntegerSize (valu, mode)

int           valu;
unsigned int  mode;

  {
  unsigned int size = 0;

  if (mode == UTL_DAT__SINT)
    {
    size ++;
    if (valu < 0)
      valu = -valu;
    }

  while (valu != 0)
    {
    size ++;
    valu = valu >> 1;
    }

  return (size);
  }
