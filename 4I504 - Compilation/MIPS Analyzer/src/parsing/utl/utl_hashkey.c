
/* ###--------------------------------------------------------------### */
/* file		: utl_hashkey.c						*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_hashkey						*/
/* description	: get a hash code from a key				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_hashkey (key, ini_cod)

void         *key    ;
unsigned int  ini_cod;

  {
  unsigned int code;

  code  =   ((unsigned int) key)        + ini_cod ;
  code ^= ((((unsigned int) key) >>  3)          );
  code ^= ((((unsigned int) key) >>  5) + ini_cod);
  code ^= ((((unsigned int) key) >> 16)          );

  return (code);
  }
