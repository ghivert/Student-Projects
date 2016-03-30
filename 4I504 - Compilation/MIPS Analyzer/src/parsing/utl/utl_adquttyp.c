
/* ###--------------------------------------------------------------### */
/* file		: utl_adquttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_adquttyp						*/
/* description	: create an UTTYP structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_adquttyp (list, dat1, dat2)

struct uttyp *list;
union  utdat  dat1;
union  utdat  dat2;

  {
  struct uttyp *tmp_typ;
  struct uttyp *pt_typ ;
  int           i      ;

	/* ###------------------------------------------------------### */
	/*    make a block allocation					*/
	/* ###------------------------------------------------------### */

  if (UTL_FRETYP == NULL)
    {
    UTL_FRETYP = (struct uttyp *)
                  utl_alloc (sizeof (struct uttyp) * UTL_BLC__TYP);

    pt_typ = UTL_FRETYP;
    for (i=1 ; i<UTL_BLC__TYP ; i++)
      {
      pt_typ->NEXT = pt_typ + 1;
      pt_typ ++;
      }
    pt_typ->NEXT = NULL;
    }

	/* ###------------------------------------------------------### */
	/*    initialize the first available structure and add it to	*/
	/* the end of the existing list					*/
	/* ###------------------------------------------------------### */

  pt_typ       = UTL_FRETYP      ;
  UTL_FRETYP   = UTL_FRETYP->NEXT;

  pt_typ->NEXT = NULL            ;
  pt_typ->DAT1 = dat1            ;
  pt_typ->DAT2 = dat2            ;

  if (list == NULL)
    list = pt_typ;
  else
    {
    tmp_typ = list;
    while (tmp_typ->NEXT != NULL)
      tmp_typ = tmp_typ->NEXT;

    tmp_typ->NEXT = pt_typ;
    }

  return (list);
  }
