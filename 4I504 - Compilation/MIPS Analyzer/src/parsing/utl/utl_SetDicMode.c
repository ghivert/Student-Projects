
/* ###--------------------------------------------------------------### */
/* file		: utl_SetDicMode.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SetDicMode					*/
/* description	: set the mode of the dictionary			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utdic *utl_SetDicMode (dic, mode)

struct utdic *dic ;
unsigned int  mode;

  {
  if (dic != NULL)
    dic->FLAG = mode;

  return (dic);
  }
