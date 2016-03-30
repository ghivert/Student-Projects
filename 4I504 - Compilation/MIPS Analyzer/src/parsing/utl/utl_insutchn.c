
/* ###--------------------------------------------------------------### */
/* file		: utl_insutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_insutchn						*/
/* description	: insert an UTCHN structure into a sorted list		*/
/* called func.	: utl_addutchn, utl_cmpsint				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_insutchn (list, data, pt_cmp)

struct utchn  *list      ;
union  utdat   data      ;
int          (*pt_cmp) ();

  {
  struct utchn *prv_chn = NULL;
  struct utchn *pt_chn  = NULL;

	/* ###------------------------------------------------------### */
	/*   initialize the comparison function				*/
	/* ###------------------------------------------------------### */

  if (pt_cmp == NULL)
    pt_cmp = utl_cmpsint;

	/* ###------------------------------------------------------### */
	/*   find the position of the new data in the list		*/
	/* ###------------------------------------------------------### */

  pt_chn = list;
  while (pt_chn != NULL)
    {
    if ((*pt_cmp) (data, pt_chn->DATA) <= 0)
      break;

    prv_chn = pt_chn;
    pt_chn  = pt_chn->NEXT;
    }

	/* ###------------------------------------------------------### */
	/*   insert the data into to list				*/
	/* ###------------------------------------------------------### */

  if (prv_chn != NULL)
    {
    pt_chn        = utl_addutchn (prv_chn->NEXT, data);
    prv_chn->NEXT = pt_chn ;
    pt_chn        = list   ;
    }
  else
    pt_chn        = utl_addutchn (list         , data);

  return (pt_chn);
  }
