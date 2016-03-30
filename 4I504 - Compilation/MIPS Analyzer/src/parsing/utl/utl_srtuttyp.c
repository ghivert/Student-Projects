
/* ###--------------------------------------------------------------### */
/* file		: utl_srtuttyp.c					*/
/* date		: Jun 25 2010						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_srtuttyp						*/
/* description	: sort a list - increasing order regarding the		*/
/*		  comparison function given as parameter		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_srtuttyp (list, pt_cmp)

struct uttyp  *list      ;
int          (*pt_cmp) ();

  {
  struct uttyp *srt_lst = NULL;
  struct uttyp *hed_lst = NULL;
  struct uttyp *prv_typ = NULL;
  struct uttyp *pt_typ  = NULL;

	/* ###------------------------------------------------------### */
	/*   nothing to do if the comparison function is not provided	*/
	/* ###------------------------------------------------------### */

  if (pt_cmp == NULL)
    srt_lst = list;
  else
    {
	/* ###------------------------------------------------------### */
	/*   initialize the sorted list					*/
	/* ###------------------------------------------------------### */

    srt_lst = NULL;

	/* ###------------------------------------------------------### */
	/*   for each element of the input list				*/
	/* ###------------------------------------------------------### */

    while (list != NULL)
      {
      hed_lst = list      ;
      list    = list->NEXT;

	/* ###------------------------------------------------------### */
	/*   find the postion of the head of the list in the sorted	*/
	/*   list							*/
	/* ###------------------------------------------------------### */

      prv_typ = NULL   ;
      pt_typ  = srt_lst;
      while (pt_typ != NULL)
        {
        if ((*pt_cmp) (hed_lst->DAT1, hed_lst->DAT2,
                       pt_typ->DAT1 , pt_typ->DAT2  ) <= 0)
          break;

        prv_typ = pt_typ      ;
        pt_typ  = pt_typ->NEXT;
        }

	/* ###------------------------------------------------------### */
	/*   insert the element into the sorted list			*/
	/* ###------------------------------------------------------### */

      if (prv_typ != NULL)
        {
        prv_typ->NEXT = hed_lst ;
        hed_lst->NEXT = pt_typ  ;
        }
      else
        {
        hed_lst->NEXT = srt_lst ;
        srt_lst       = hed_lst ;
        }
      }
    }

  return (srt_lst);
  }
