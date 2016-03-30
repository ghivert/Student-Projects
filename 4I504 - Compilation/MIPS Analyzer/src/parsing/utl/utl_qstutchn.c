
/* ###--------------------------------------------------------------### */
/* file		: utl_qstutchn.c					*/
/* date		: Jul 13 2010						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_qstutchn						*/
/* description	: quick sort - increasing order regarding the		*/
/*		  comparison function given as parameter		*/
/*									*/
/* called func.	: utl_qstutchn, utl_catutchn				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_qstutchn (list, pt_cmp)

struct utchn  *list      ;
int          (*pt_cmp) ();

  {
  struct utchn *pt_pvt  = NULL;
  struct utchn *pt_inf  = NULL;
  struct utchn *pt_sup  = NULL;
  struct utchn *pt_chn  = NULL;
  struct utchn *nxt_chn = NULL;

	/* ###------------------------------------------------------### */
	/*   nothing to do if :						*/
	/*        - the comparison function is not provided		*/
	/*     or - the list is empty 					*/
	/*     or - the list contains only one element			*/
	/* ###------------------------------------------------------### */

  if ((pt_cmp == NULL) || (list == NULL) || (list->NEXT == NULL))
    pt_inf = list;
  else
    {
    pt_pvt = list      ;
    pt_chn = list->NEXT;

    while (pt_chn != NULL)
      {
      nxt_chn = pt_chn->NEXT;
      if ((*pt_cmp) (pt_chn->DATA, pt_pvt->DATA) <= 0)
        {
        pt_chn->NEXT = pt_inf;
        pt_inf       = pt_chn;
        }
      else
        {
        pt_chn->NEXT = pt_sup;
        pt_sup       = pt_chn;
        }
      pt_chn = nxt_chn;
      }

    pt_inf       = utl_qstutchn (pt_inf, pt_cmp);
    pt_sup       = utl_qstutchn (pt_sup, pt_cmp);
    pt_pvt->NEXT = pt_sup;
    pt_inf       = utl_catutchn (pt_inf, pt_pvt);
    }

  return (pt_inf);
  }
