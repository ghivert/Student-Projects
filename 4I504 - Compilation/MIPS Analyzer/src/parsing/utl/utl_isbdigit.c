
/* ###--------------------------------------------------------------### */
/* file		: utl_isbdigit.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_isbdigit						*/
/* description	: return non zero value if the parameter is a		*/
/*		  binary digit						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_isbdigit (c)

unsigned char c;

  {
  return (UTL_CHR_TYPE [c] & UTL_CHR__BDG);
  }
