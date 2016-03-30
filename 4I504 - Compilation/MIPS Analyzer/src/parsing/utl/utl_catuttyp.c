
/* ###--------------------------------------------------------------### */
/* file		: utl_catuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_catuttyp						*/
/* description	: catenate two lists					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_catuttyp (pt_tp1, pt_tp2)

struct uttyp *pt_tp1;
struct uttyp *pt_tp2;

  {
  struct uttyp *tmp_typ = NULL;

  if (pt_tp1 != NULL)
    {
    tmp_typ = pt_tp1;
    while (tmp_typ->NEXT != NULL)
      tmp_typ = tmp_typ->NEXT;

    tmp_typ->NEXT = pt_tp2 ;
    }
  else
    pt_tp1 = pt_tp2;

  return (pt_tp1);
  }
