
/* ###--------------------------------------------------------------### */
/* file		: utl_rmvuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_rmvuttyp						*/
/* description	: remove a data from a list. Two comparison functions	*/
/*		  are passed as argument. The element that matches the	*/
/*		  data is removed from the list. If the searched data	*/
/*		  is not found, the input list is returned without	*/
/*		  modification. The comparison is assumed to succeed	*/
/*		  always with a null function of comparison 		*/
/*									*/
/* called func.	: utl_freuttyp						*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_rmvuttyp (list, dat1, dat2, pt_cmp1, pt_cmp2)

struct uttyp  *list       ;
union  utdat   dat1       ;
union  utdat   dat2       ;
int          (*pt_cmp1) ();
int          (*pt_cmp2) ();

  {
  struct uttyp *prv_typ = NULL;
  struct uttyp *pt_typ  = NULL;

  pt_typ = list;

	/* ###------------------------------------------------------### */
	/*   find the the data in the list				*/
	/* ###------------------------------------------------------### */

  if ((pt_cmp1 != NULL) && (pt_cmp2 != NULL))
    {
    while (pt_typ != NULL)
      {
      if (((*pt_cmp1) (dat1, pt_typ->DAT1) == 0) &&
          ((*pt_cmp2) (dat2, pt_typ->DAT2) == 0)   )
        break;

      prv_typ = pt_typ      ;
      pt_typ  = pt_typ->NEXT;
      }
    }

  if ((pt_cmp1 != NULL) && (pt_cmp2 == NULL))
    {
    while (pt_typ != NULL)
      {
      if  ((*pt_cmp1) (dat1, pt_typ->DAT1) == 0)
        break;

      prv_typ = pt_typ      ;
      pt_typ  = pt_typ->NEXT;
      }
    }

  if ((pt_cmp1 == NULL) && (pt_cmp2 != NULL))
    {
    while (pt_typ != NULL)
      {
      if  ((*pt_cmp2) (dat2, pt_typ->DAT2) == 0)
        break;

      prv_typ = pt_typ      ;
      pt_typ  = pt_typ->NEXT;
      }
    }

	/* ###------------------------------------------------------### */
	/*   remove the data from the list				*/
	/* ###------------------------------------------------------### */

  if (pt_typ != NULL)
    {
    pt_typ = utl_freuttyp (pt_typ);

    if (prv_typ != NULL)
      prv_typ->NEXT = pt_typ ;
    else
      list          = pt_typ ;
    }

  return (list);
  }
