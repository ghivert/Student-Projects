
/* ###--------------------------------------------------------------### */
/* file		: utl_DelDictionary.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_DelDictionary					*/
/* description	: delete a dictionary					*/
/* called func.	: utl_adduttyp, utl_DelAllDicItems			*/
/* ###--------------------------------------------------------------### */

struct utdic *utl_DelDictionary (pt_dic)

struct utdic *pt_dic;

  {
  utl_Trace ("utl_DelDictionary", UTL_FUN__IN );

  utl_DelAllDicItems (pt_dic);

  UTL_FREDIT   = utl_adduttyp (UTL_FREDIT, pt_dic->TABLE, pt_dic->SIZE);
  pt_dic->NEXT = UTL_FREDIC;
  UTL_FREDIC   = pt_dic    ;

  utl_Trace ("utl_DelDictionary", UTL_FUN__OUT);

  return (NULL);
  }
