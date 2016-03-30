
/* ###--------------------------------------------------------------### */
/* file		: utl_adduttdc.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_adduttdc						*/
/* description	: create an UTTDC structure				*/
/* called func.	: utl_alloc						*/
/* ###--------------------------------------------------------------### */

struct uttdc *utl_adduttdc (list, dat1, dat2, dat3)

struct uttdc *list;
union  utdat  dat1;
union  utdat  dat2;
union  utdat  dat3;

  {
  struct uttdc *pt_tdc;
  int           i     ;

	/* ###------------------------------------------------------### */
	/*    make a block allocation					*/
	/* ###------------------------------------------------------### */

  if (UTL_FRETDC == NULL)
    {
    UTL_FRETDC = (struct uttdc *)
                  utl_alloc (sizeof (struct uttdc) * UTL_BLC__TDC);

    pt_tdc = UTL_FRETDC;
    for (i=1 ; i<UTL_BLC__TDC ; i++)
      {
      pt_tdc->NEXT = pt_tdc + 1;
      pt_tdc ++;
      }
    pt_tdc->NEXT = NULL;
    }

	/* ###------------------------------------------------------### */
	/*    initialize and return the first available structure	*/
	/* ###------------------------------------------------------### */

  pt_tdc       = UTL_FRETDC      ;
  UTL_FRETDC   = UTL_FRETDC->NEXT;

  pt_tdc->NEXT = list            ;
  pt_tdc->DAT1 = dat1            ;
  pt_tdc->DAT2 = dat2            ;
  pt_tdc->DAT3 = dat3            ;

  return (pt_tdc);
  }
