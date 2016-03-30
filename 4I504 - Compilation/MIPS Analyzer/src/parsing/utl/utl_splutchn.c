
/* ###--------------------------------------------------------------### */
/* file		: utl_splutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_splutchn						*/
/* description	: split a list into two parts				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_splutchn (pt_ch1, pt_ch2)

struct utchn *pt_ch1;
struct utchn *pt_ch2;

  {
  struct utchn *res_chn = NULL;

  if (pt_ch1 != NULL)
    {
    while (pt_ch1->NEXT != NULL)
      {
      if (pt_ch1->NEXT == pt_ch2)
        {
        pt_ch1->NEXT = NULL  ;
        res_chn      = pt_ch2;
        break;
        }
      pt_ch1 = pt_ch1->NEXT;
      }
    }

  return (res_chn);
  }
