
/* ###--------------------------------------------------------------### */
/* file		: utl_adqutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_adqutchn						*/
/* description	: create an UTCHN structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_adqutchn (list, data)

struct utchn *list;
union  utdat  data;

  {
  struct utchn *tmp_chn;
  struct utchn *pt_chn ;
  int           i      ;

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
	/*    initialize the first available structure and add it to	*/
	/* the end of the existing list					*/
	/* ###------------------------------------------------------### */

  pt_chn       = UTL_FRECHN      ;
  UTL_FRECHN   = UTL_FRECHN->NEXT;

  pt_chn->NEXT = NULL            ;
  pt_chn->DATA = data            ;

  if (list == NULL)
    list = pt_chn;
  else
    {
    tmp_chn = list;
    while (tmp_chn->NEXT != NULL)
      tmp_chn = tmp_chn->NEXT;

    tmp_chn->NEXT = pt_chn;
    }

  return (list);
  }
