
/* ###--------------------------------------------------------------### */
/* file		: utl_cpyuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_cpyuttyp						*/
/* description	: make a copy of a list					*/
/* called func.	: utl_revuttyp, utl_adduttyp				*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_cpyuttyp (pt_src)

struct uttyp *pt_src;

  {
  struct uttyp *pt_typ = NULL;

  while (pt_src != NULL)
    {
    pt_typ = utl_adduttyp (pt_typ, pt_src->DAT1, pt_src->DAT2);
    pt_src = pt_src->NEXT;
    }

  pt_typ = utl_revuttyp (pt_typ);

  return (pt_typ);
  }
