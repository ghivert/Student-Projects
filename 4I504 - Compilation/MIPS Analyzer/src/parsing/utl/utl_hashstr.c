
/* ###--------------------------------------------------------------### */
/* file		: utl_hashstr.c						*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_hashstr						*/
/* description	: get a hash code from a string				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_hashstr (str)

char         *str;

  {
  unsigned int cod1;
  unsigned int cod2;

  utl_hash2 (str, &cod1, &cod2);

  return (cod1);
  }
