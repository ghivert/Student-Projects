
/* ###--------------------------------------------------------------### */
/* file		: utl_frebyt.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_frebyt						*/
/* description	: add an array to the table of available spaces		*/
/* called func.	: utl_adduttyp						*/
/* ###--------------------------------------------------------------### */

void utl_frebyt (pt_byt, size)

char         *pt_byt;
unsigned int  size  ;

  {
  struct uttyp *pt_typ ;
  unsigned int  index  ;

  if ((pt_byt != NULL) && (size > 0))
    {
    index               = size % UTL_BYT__TABLESIZE;

    pt_typ              = utl_adduttyp (NULL, pt_byt, size);
    pt_typ->NEXT        = UTL_FREBTAB [index];
    UTL_FREBTAB [index] = pt_typ;
    }

  }
