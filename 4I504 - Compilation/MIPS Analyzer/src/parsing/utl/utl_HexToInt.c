
/* ###--------------------------------------------------------------### */
/* file		: utl_HexToInt.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_HexToInt						*/
/* description	: convert a string of hexadecimal digits into an integer*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_HexToInt (str, pt_str)

char  *str   ;
char **pt_str;

  {
  unsigned int  valu = 0;
  char          c    = 0;

  if (str != NULL)
    {
    c = *str;
    while (utl_isxdigit (c) != 0)
      {
      valu = (valu << 4) + utl_CharToInt (c);

      str ++;
      c = *str;
      }

    if (pt_str != NULL)
      *pt_str = str ;
    }
  return (valu);
  }
