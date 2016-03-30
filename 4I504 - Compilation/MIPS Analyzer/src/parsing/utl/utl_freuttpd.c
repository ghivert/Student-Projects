
/* ###--------------------------------------------------------------### */
/* file		: utl_freuttpd.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_freuttpd						*/
/* description	: release one UTTPD (typed chained list) structure	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttpd *utl_freuttpd (pt_tpd)

struct uttpd *pt_tpd;

  {
  struct uttpd *nxt_tpd = NULL;

  if (pt_tpd != NULL)
    {
    nxt_tpd      = pt_tpd->NEXT;
    pt_tpd->NEXT = UTL_FRETPD  ;
    UTL_FRETPD   = pt_tpd      ;
    }

  return (nxt_tpd);
  }
