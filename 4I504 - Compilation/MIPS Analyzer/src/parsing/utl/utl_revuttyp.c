
/* ###--------------------------------------------------------------### */
/* file		: utl_revuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_revuttyp						*/
/* description	: reverse the order of a list of UTTYP structures	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_revuttyp (pt_typ)

struct uttyp *pt_typ;

  {
  struct uttyp *prv_typ = NULL;
  struct uttyp *nxt_typ = NULL;

  if (pt_typ != NULL)
    {
    while ((nxt_typ = pt_typ->NEXT) != NULL)
      {
      pt_typ->NEXT = prv_typ;
      prv_typ      = pt_typ ;
      pt_typ       = nxt_typ;
      }

    pt_typ->NEXT = prv_typ;
    }

  return (pt_typ);
  }
