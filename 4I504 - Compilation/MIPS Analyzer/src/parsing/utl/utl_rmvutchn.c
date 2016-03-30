
/* ###--------------------------------------------------------------### */
/* file		: utl_rmvutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_rmvutchn						*/
/* description	: remove a data from a list. A comparison function	*/
/*		  is passed as argument. The element that matches the	*/
/*		  data is removed from the list. If the searched data	*/
/*		  is not found, the input list is returned without	*/
/*		  modification. The comparison is assumed to succeed	*/
/*		  always with a null function of comparison 		*/
/*									*/
/* called func.	: utl_freutchn						*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_rmvutchn (list, data, pt_cmp)

struct utchn  *list      ;
union  utdat   data      ;
int          (*pt_cmp) ();

  {
  struct utchn *prv_chn = NULL;
  struct utchn *pt_chn  = NULL;

  pt_chn = list;

  if (pt_cmp != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   find the the data in the list				*/
	/* ###------------------------------------------------------### */

    while (pt_chn != NULL)
      {
      if ((*pt_cmp) (data, pt_chn->DATA) == 0)
        break;

      prv_chn = pt_chn      ;
      pt_chn  = pt_chn->NEXT;
      }
    }

	/* ###------------------------------------------------------### */
	/*   remove the data from the list				*/
	/* ###------------------------------------------------------### */

  if (pt_chn != NULL)
    {
    pt_chn = utl_freutchn (pt_chn);

    if (prv_chn != NULL)
      prv_chn->NEXT = pt_chn ;
    else
      list          = pt_chn ;
    }

  return (list);
  }
