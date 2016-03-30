
/* ###--------------------------------------------------------------### */
/* file		: utl_mvquttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: utility functions					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_mvquttyp						*/
/* description	: move an element to the end of the list		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_mvquttyp (pt_typ, pt_elm)

struct uttyp *pt_typ;
struct uttyp *pt_elm;

  {
  struct uttyp *tmp_typ = NULL;
  struct uttyp *prv_typ = NULL;

  if ((pt_typ != NULL) && (pt_typ->NEXT != NULL))
    {
	/* ###------------------------------------------------------### */
	/*   find the element						*/
	/* ###------------------------------------------------------### */

    tmp_typ = pt_typ;
    while (tmp_typ != NULL)
      {
      if (tmp_typ == pt_elm)
        break;
      prv_typ = tmp_typ      ;
      tmp_typ = tmp_typ->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   extract the element from the list				*/
	/* ###------------------------------------------------------### */

    if ((tmp_typ != NULL) && (tmp_typ->NEXT != NULL))
      {
      if (prv_typ != NULL)
        prv_typ->NEXT = pt_elm->NEXT;
      else
        pt_typ        = pt_elm->NEXT;

	/* ###------------------------------------------------------### */
	/*   move the element to the end of the list			*/
	/* ###------------------------------------------------------### */

      tmp_typ = pt_elm->NEXT;
      while (tmp_typ->NEXT != NULL)
        tmp_typ = tmp_typ->NEXT;

      tmp_typ->NEXT = pt_elm;
      tmp_typ       = pt_elm;
      pt_elm->NEXT  = NULL  ;
      }
    }

  return (pt_typ);
  }
