
/* ###--------------------------------------------------------------### */
/* file		: utl_GetSlicedNameList.c				*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetSlicedNameList					*/
/* description	: build a list of name from a sliced name		*/
/* called func.	: utl_addutchn, utl_SaveString				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_GetSlicedNameList (str, left, right)

char *str  ;
int   left ;
int   right;

  {
  int           i                     ;
  unsigned int  idx                   ;
  char          buf [UTL_STR__MAXLEN] ;
  char         *name                  ;
  struct utchn *pt_chn                = NULL;

  idx = sprintf (buf, "%s ", str);

  if (right >= left)
    {
    for (i=right ; i>=left ; i--)
      {
      sprintf (buf + idx, "%d", i);
      name   = utl_SaveString (buf                  );
      pt_chn = utl_addutchn   (pt_chn, (union utdat)(void *) name);
      }
    }
  else
    {
    for (i=right ; i<=left ; i++)
      {
      sprintf (buf + idx, "%d", i);
      name   = utl_SaveString (buf                  );
      pt_chn = utl_addutchn   (pt_chn, (union utdat)(void *) name);
      }
    }

  return (pt_chn);
  }
