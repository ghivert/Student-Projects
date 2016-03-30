
/* ###--------------------------------------------------------------### */
/* file		: utl_addutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_addutchn						*/
/* description	: create an UTCHN structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_addutchn (list, data)

struct utchn *list;
union  utdat  data;

  {
  struct utchn *pt_chn;
  int           i     ;

	/* ###------------------------------------------------------### */
	/*    make a block allocation					*/
	/* ###------------------------------------------------------### */

  if (UTL_FRECHN == NULL)
    {
    UTL_FRECHN = (struct utchn *)
                  utl_alloc (sizeof (struct utchn) * UTL_BLC__CHN);

    pt_chn = UTL_FRECHN;
    for (i=1 ; i<UTL_BLC__CHN ; i++)
      {
      pt_chn->NEXT = pt_chn + 1;
      pt_chn ++;
      }
    pt_chn->NEXT = NULL;
    }

	/* ###------------------------------------------------------### */
	/*    initialize and return the first available structure	*/
	/* ###------------------------------------------------------### */

  pt_chn       = UTL_FRECHN      ;
  UTL_FRECHN   = UTL_FRECHN->NEXT;

  pt_chn->NEXT = list            ;
  pt_chn->DATA = data            ;

  return (pt_chn);
  }
