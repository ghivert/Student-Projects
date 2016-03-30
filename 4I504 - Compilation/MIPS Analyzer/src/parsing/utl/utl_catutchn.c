
/* ###--------------------------------------------------------------### */
/* file		: utl_catutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_catutchn						*/
/* description	: catenate two lists					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_catutchn (pt_ch1, pt_ch2)

struct utchn *pt_ch1;
struct utchn *pt_ch2;

  {
  struct utchn *tmp_chn = NULL;

  if (pt_ch1 != NULL)
    {
    tmp_chn = pt_ch1;
    while (tmp_chn->NEXT != NULL)
      tmp_chn = tmp_chn->NEXT;

    tmp_chn->NEXT = pt_ch2 ;
    }
  else
    pt_ch1 = pt_ch2;

  return (pt_ch1);
  }
