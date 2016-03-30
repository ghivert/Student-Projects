
/* ###--------------------------------------------------------------### */
/* file		: utl_frluttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_frluttyp						*/
/* description	: release a list of UTTYP structures			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_frluttyp (pt_typ)

struct uttyp *pt_typ;

  {
  struct uttyp *tmp_typ;

  if (pt_typ != NULL)
    {
    tmp_typ = pt_typ;

    while (tmp_typ->NEXT != NULL)
      tmp_typ = tmp_typ->NEXT;

    tmp_typ->NEXT = UTL_FRETYP ;
    UTL_FRETYP    = pt_typ     ;
    }

  return (NULL);
  }
