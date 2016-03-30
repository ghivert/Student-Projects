
/* ###--------------------------------------------------------------### */
/* file		: utl_hash2.c						*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_hash2						*/
/* description	: get a hash code from a string				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_hash2 (str, pt_cod1, pt_cod2)

char         *str;
unsigned int *pt_cod1;
unsigned int *pt_cod2;

  {
  unsigned int cod1 = 0;
  unsigned int cod2 = 0;
  int          i    = 0;

  while (str [i] != '\0')
    {
    cod1 = (cod1 << 1) ^ (cod2        + (str [i] << (i % 4)));
    cod2 = (cod1 << 3) + (cod2 << 1)  +  str [i]             ;
    i ++;
    }

  *pt_cod1 = cod1;
  *pt_cod2 = cod2;
  }
