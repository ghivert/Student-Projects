
/* ###--------------------------------------------------------------### */
/* file		: utl_ccputchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_ccputchn						*/
/* description	: make a conditional copy of a list			*/
/* called func.	: utl_revutchn, utl_addutchn				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_ccputchn (pt_src, pt_cnd)

struct utchn  *pt_src;
int          (*pt_cnd) ();

  {
  struct utchn *pt_chn = NULL;

	/* ###------------------------------------------------------### */
	/*   the function passed as argument is used to evaluate the	*/
	/* condition. If a null pointer is passed, a copy of the entire	*/
	/* list is returned. Otherwise, a copy of an element is created	*/
	/* only if the value returned by the evaluation function is not	*/
	/* zero.							*/
	/* ###------------------------------------------------------### */

  if (pt_cnd == NULL)
    {
    while (pt_src != NULL)
      {
      pt_chn = utl_addutchn (pt_chn, pt_src->DATA);
      pt_src = pt_src->NEXT;
      }
    }
  else
    {
    while (pt_src != NULL)
      {
      if ((*pt_cnd) (pt_src) != 0)
        pt_chn = utl_addutchn (pt_chn, pt_src->DATA);

      pt_src = pt_src->NEXT;
      }
    }

  pt_chn = utl_revutchn (pt_chn);

  return (pt_chn);
  }
