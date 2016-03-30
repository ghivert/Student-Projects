
/* ###--------------------------------------------------------------### */
/* file		: utl_adduttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_adduttyp						*/
/* description	: create an UTTYP structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct uttyp *utl_adduttyp (list, dat1, dat2)

struct uttyp *list;
union  utdat  dat1;
union  utdat  dat2;

  {
  struct uttyp *pt_typ;
  int           i     ;

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

  pt_typ       = UTL_FRETYP      ;
  UTL_FRETYP   = UTL_FRETYP->NEXT;

  pt_typ->NEXT = list            ;
  pt_typ->DAT1 = dat1            ;
  pt_typ->DAT2 = dat2            ;

  return (pt_typ);
  }
