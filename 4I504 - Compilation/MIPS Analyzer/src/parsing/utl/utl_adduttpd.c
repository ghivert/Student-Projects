
/* ###--------------------------------------------------------------### */
/* file		: utl_adduttpd.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_adduttpd						*/
/* description	: create an UTTPD structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct uttpd *utl_adduttpd (list, dat1, dat2)

struct uttpd *list;
union  utdat  dat1;
double        dat2;

  {
  struct uttpd *pt_tpd;
  int           i     ;

  if (UTL_FRETPD == NULL)
    {
    UTL_FRETPD = (struct uttpd *)
                  utl_alloc (sizeof (struct uttpd) * UTL_BLC__TPD);

    pt_tpd = UTL_FRETPD;
    for (i=1 ; i<UTL_BLC__TPD ; i++)
      {
      pt_tpd->NEXT = pt_tpd + 1;
      pt_tpd ++;
      }
    pt_tpd->NEXT = NULL;
    }

  pt_tpd       = UTL_FRETPD      ;
  UTL_FRETPD   = UTL_FRETPD->NEXT;

  pt_tpd->NEXT = list            ;
  pt_tpd->DAT1 = dat1            ;
  pt_tpd->DAT2 = dat2            ;

  return (pt_tpd);
  }
