
/* ###--------------------------------------------------------------### */
/* file		: utl_SetIndexDelimiter.c				*/
/* date		: Feb 14 2007						*/
/* version	: v200							*/
/* authors	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SetIndexDelimiter					*/
/* description	: set the index delimiter character for vectors		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_SetIndexDelimiter (opn_del)

char opn_del;

  {
  unsigned int i;

  for (i=0 ; i<UTL_DLM__OTHERS ; i++)
    {
    if (UTL_DLM_LEFT [i] == opn_del)
      break;
    }

  UTL_DLM_LEFT      [i] = opn_del;
  UTL_IDX_DELIMITER     = i      ;

  return (i);
  }
