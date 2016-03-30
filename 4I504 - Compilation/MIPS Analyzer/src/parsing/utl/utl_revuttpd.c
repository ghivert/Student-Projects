
/* ###--------------------------------------------------------------### */
/* file		: utl_revuttpd.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_revuttpd						*/
/* description	: reverse the order of a list of UTTPD structures	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttpd *utl_revuttpd (pt_tpd)

struct uttpd *pt_tpd;

  {
  struct uttpd *prv_tpd = NULL;
  struct uttpd *nxt_tpd = NULL;

  if (pt_tpd != NULL)
    {
    while ((nxt_tpd = pt_tpd->NEXT) != NULL)
      {
      pt_tpd->NEXT = prv_tpd;
      prv_tpd      = pt_tpd ;
      pt_tpd       = nxt_tpd;
      }

    pt_tpd->NEXT = prv_tpd;
    }

  return (pt_tpd);
  }
