
/* ###--------------------------------------------------------------### */
/* file		: utl_catenate.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_catenate						*/
/* description	: catenate two lists					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttpd *utl_catenate (pt_tp1, pt_tp2)

struct uttpd *pt_tp1;
struct uttpd *pt_tp2;

  {
  struct uttpd *tmp_tpd = NULL;

  if (pt_tp1 != NULL)
    {
    tmp_tpd = pt_tp1;
    while (tmp_tpd->NEXT != NULL)
      tmp_tpd = tmp_tpd->NEXT;

    tmp_tpd->NEXT = pt_tp2 ;
    }
  else
    pt_tp1 = pt_tp2;

  return (pt_tp1);
  }
