
/* ###--------------------------------------------------------------### */
/* file		: utl_ccputtyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_ccputtyp						*/
/* description	: make a conditional copy of a list			*/
/* called func.	: utl_revuttyp, utl_adduttyp				*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_ccputtyp (pt_src, pt_cnd)

struct uttyp  *pt_src;
int          (*pt_cnd) ();

  {
  struct uttyp *pt_typ = NULL;

	/* ###------------------------------------------------------### */
	/*   the function passed as argument is used to evaluate the	*/
	/* condition. If a null pointer is passed, a copy of the entire	*/
	/* list is returned. Otherwise, a copy of an element is created	*/
	/* only if the value returned by the evaluation function is not	*/
	/* zero.							*/
	/* ###------------------------------------------------------### */

  if (pt_cnd == NULL)
    {
    while (pt_src != NULL)
      {
      pt_typ = utl_adduttyp (pt_typ, pt_src->DAT1, pt_src->DAT2);
      pt_src = pt_src->NEXT;
      }
    }
  else
    {
    while (pt_src != NULL)
      {
      if ((*pt_cnd) (pt_src) != 0)
        pt_typ = utl_adduttyp (pt_typ, pt_src->DAT1, pt_src->DAT2);

      pt_src = pt_src->NEXT;
      }
    }

  pt_typ = utl_revuttyp (pt_typ);

  return (pt_typ);
  }
