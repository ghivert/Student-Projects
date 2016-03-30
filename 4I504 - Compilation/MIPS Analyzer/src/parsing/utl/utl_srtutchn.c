
/* ###--------------------------------------------------------------### */
/* file		: utl_srtutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_srtutchn						*/
/* description	: sort a list - increasing order regarding the		*/
/*		  comparison function given as parameter		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_srtutchn (list, pt_cmp)

struct utchn  *list      ;
int          (*pt_cmp) ();

  {
  struct utchn *srt_lst = NULL;
  struct utchn *hed_lst = NULL;
  struct utchn *prv_chn = NULL;
  struct utchn *pt_chn  = NULL;

	/* ###------------------------------------------------------### */
	/*   nothing to do if the comparison function is not provided	*/
	/* ###------------------------------------------------------### */

  if (pt_cmp == NULL)
    srt_lst = list;
  else
    {
	/* ###------------------------------------------------------### */
	/*   initialize the sorted list					*/
	/* ###------------------------------------------------------### */

    srt_lst = NULL;

	/* ###------------------------------------------------------### */
	/*   for each element of the input list				*/
	/* ###------------------------------------------------------### */

    while (list != NULL)
      {
      hed_lst = list      ;
      list    = list->NEXT;

	/* ###------------------------------------------------------### */
	/*   find the postion of the head of the list in the sorted	*/
	/*   list							*/
	/* ###------------------------------------------------------### */

      prv_chn = NULL   ;
      pt_chn  = srt_lst;
      while (pt_chn != NULL)
        {
        if ((*pt_cmp) (hed_lst->DATA, pt_chn->DATA) <= 0)
          break;

        prv_chn = pt_chn;
        pt_chn  = pt_chn->NEXT;
        }

	/* ###------------------------------------------------------### */
	/*   insert the element into the sorted list			*/
	/* ###------------------------------------------------------### */

      if (prv_chn != NULL)
        {
        prv_chn->NEXT = hed_lst ;
        hed_lst->NEXT = pt_chn  ;
        }
      else
        {
        hed_lst->NEXT = srt_lst ;
        srt_lst       = hed_lst ;
        }
      }
    }

  return (srt_lst);
  }
