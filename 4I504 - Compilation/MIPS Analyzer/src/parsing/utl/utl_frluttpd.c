
/* ###--------------------------------------------------------------### */
/* file		: utl_frluttpd.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_frluttpd						*/
/* description	: release a list of UTTPD structures			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttpd *utl_frluttpd (pt_tpd)

struct uttpd *pt_tpd;

  {
  struct uttpd *tmp_tpd;

  if (pt_tpd != NULL)
    {
    tmp_tpd = pt_tpd;

    while (tmp_tpd->NEXT != NULL)
      tmp_tpd = tmp_tpd->NEXT;

    tmp_tpd->NEXT = UTL_FRETPD ;
    UTL_FRETPD    = pt_tpd     ;
    }

  return (NULL);
  }
