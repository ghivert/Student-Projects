
/* ###--------------------------------------------------------------### */
/* file		: utl_GetDicStatus.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetDicStatus					*/
/* description	: return the status					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_GetDicStatus (pt_dic)

struct utdic *pt_dic ;

  {
  unsigned int status = UTL_DIC__FAILED;

  if (pt_dic != NULL)
    status = pt_dic->STATUS;

  return (status);
  }
