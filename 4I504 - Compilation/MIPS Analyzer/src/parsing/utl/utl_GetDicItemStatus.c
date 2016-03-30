
/* ###--------------------------------------------------------------### */
/* file		: utl_GetDicItemStatus.c				*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetDicItemStatus					*/
/* description	: return the dictionary's status after an item has been	*/
/*		  searched						*/
/* called func.	: utl_GetDicItem					*/
/* ###--------------------------------------------------------------### */

unsigned int utl_GetDicItemStatus (pt_dic, key)

struct utdic *pt_dic;
void         *key   ;

  {
  void         *data   = NULL           ;
  unsigned int  status = UTL_DIC__FAILED;

  if (pt_dic != NULL)
    {
    data   = utl_GetDicItem (pt_dic, key);
    status = pt_dic->STATUS;
    }

  return (status);
  }
