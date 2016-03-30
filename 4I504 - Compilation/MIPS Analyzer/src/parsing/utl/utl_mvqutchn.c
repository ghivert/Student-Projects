
/* ###--------------------------------------------------------------### */
/* file		: utl_mvqutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: utility functions					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_mvqutchn						*/
/* description	: move an element to the end of the list		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_mvqutchn (pt_chn, pt_elm)

struct utchn *pt_chn;
struct utchn *pt_elm;

  {
  struct utchn *tmp_chn = NULL;
  struct utchn *prv_chn = NULL;

  if ((pt_chn != NULL) && (pt_chn->NEXT != NULL))
    {
	/* ###------------------------------------------------------### */
	/*   find the element						*/
	/* ###------------------------------------------------------### */

    tmp_chn = pt_chn;
    while (tmp_chn != NULL)
      {
      if (tmp_chn == pt_elm)
        break;
      prv_chn = tmp_chn      ;
      tmp_chn = tmp_chn->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   extract the element from the list				*/
	/* ###------------------------------------------------------### */

    if ((tmp_chn != NULL) && (tmp_chn->NEXT != NULL))
      {
      if (prv_chn != NULL)
        prv_chn->NEXT = pt_elm->NEXT;
      else
        pt_chn        = pt_elm->NEXT;

	/* ###------------------------------------------------------### */
	/*   move the element to the end of the list			*/
	/* ###------------------------------------------------------### */

      tmp_chn = pt_elm->NEXT;
      while (tmp_chn->NEXT != NULL)
        tmp_chn = tmp_chn->NEXT;

      tmp_chn->NEXT = pt_elm;
      tmp_chn       = pt_elm;
      pt_elm->NEXT  = NULL  ;
      }
    }

  return (pt_chn);
  }
