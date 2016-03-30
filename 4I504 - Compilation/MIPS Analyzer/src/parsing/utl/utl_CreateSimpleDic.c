
/* ###--------------------------------------------------------------### */
/* file		: utl_CreateSimpleDic.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_CreateSimpleDic					*/
/* description	: create a simple dictionary				*/
/* called func.	: utl_CreateDictionary					*/
/* ###--------------------------------------------------------------### */

struct utdic *utl_CreateSimpleDic (size)

unsigned short size ;

  {
  struct utdic *pt_dic = NULL;

  utl_Trace ("utl_CreateSimpleDic", UTL_FUN__IN );

  pt_dic = utl_CreateDictionary (size, UTL_DIC__SLOW, NULL, NULL, NULL,
                                 NULL, NULL, NULL   , UTL_DIC__WRITEONCE);

  utl_Trace ("utl_CreateSimpleDic", UTL_FUN__OUT);

  return (pt_dic);
  }
