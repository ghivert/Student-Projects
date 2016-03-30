
/* ###--------------------------------------------------------------### */
/* file		: utl_lenuttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_lenuttyp						*/
/* description	: count the number of structures in a list		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_lenuttyp (pt_typ)

struct uttyp *pt_typ;

  {
  unsigned int len = 0;

  while (pt_typ != NULL)
    {
    len ++;
    pt_typ = pt_typ->NEXT;
    }

  return (len);
  }
