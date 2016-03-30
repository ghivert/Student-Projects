
/* ###--------------------------------------------------------------### */
/* file		: utl_freuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_freuttyp						*/
/* description	: release one UTTYP (typed chained list) structure	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_freuttyp (pt_typ)

struct uttyp *pt_typ;

  {
  struct uttyp *nxt_typ = NULL;

  if (pt_typ != NULL)
    {
    nxt_typ      = pt_typ->NEXT;
    pt_typ->NEXT = UTL_FRETYP  ;
    UTL_FRETYP   = pt_typ      ;
    }

  return (nxt_typ);
  }
