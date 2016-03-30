
/* ###--------------------------------------------------------------### */
/* file		: utl_typ2chn.c						*/
/* date		: Jun 25 2010						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_typ2chn						*/
/* description	: make a copy of a list					*/
/* called func.	: utl_revutchn, utl_addutchn				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_typ2chn (pt_src, field)

struct uttyp *pt_src;
unsigned int  field ;

  {
  struct utchn *pt_chn = NULL;

  if (field == UTL_TYP__DAT1)
    {
    while (pt_src != NULL)
      {
      pt_chn = utl_addutchn (pt_chn, pt_src->DAT1);
      pt_src = pt_src->NEXT;
      }
    }

  if (field == UTL_TYP__DAT2)
    {
    while (pt_src != NULL)
      {
      pt_chn = utl_addutchn (pt_chn, pt_src->DAT2);
      pt_src = pt_src->NEXT;
      }
    }

  pt_chn = utl_revutchn (pt_chn);

  return (pt_chn);
  }
