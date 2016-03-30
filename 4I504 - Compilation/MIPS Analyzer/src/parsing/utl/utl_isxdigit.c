
/* ###--------------------------------------------------------------### */
/* file		: utl_isxdigit.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_isxdigit						*/
/* description	: return non zero value if the parameter is a		*/
/*		  hexadecimal digit					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_isxdigit (c)

unsigned char c;

  {
  return (UTL_CHR_TYPE [c] & UTL_CHR__XDG);
  }
