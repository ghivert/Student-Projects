
/* ###--------------------------------------------------------------### */
/* file		: utl_OctToInt.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_OctToInt						*/
/* description	: convert a string of octal digits into an integer	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_OctToInt (str, pt_str)

char  *str   ;
char **pt_str;

  {
  unsigned int  valu = 0;
  char          c    = 0;

  if (str != NULL)
    {
    c = *str;
    while (utl_isodigit (c) != 0)
      {
      valu = (valu << 3) + utl_CharToInt (c);

      str ++;
      c = *str;
      }

    if (pt_str != NULL)
      *pt_str = str ;
    }
  return (valu);
  }
