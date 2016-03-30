
/* ###--------------------------------------------------------------### */
/* file		: utl_alloc.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_alloc						*/
/* description	: make memory allocation				*/
/* called func.	: utl_error, malloc					*/
/* ###--------------------------------------------------------------### */

void *utl_alloc (size)

unsigned int size;

  {
  void *pt;

  if ((pt = malloc (sizeof (char) * size)) == NULL)
    utl_error (1, "utl_alloc", NULL, size);
  else
    UTL_MEMSIZE += size;

  return (pt);
  }
