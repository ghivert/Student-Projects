
/* ###--------------------------------------------------------------### */
/* file		: utl_GetTailerString.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetTailerString					*/
/* description	: return the tailer of a string				*/
/* called func.	: utl_SaveString					*/
/* ###--------------------------------------------------------------### */

char *utl_GetTailerString (str, separ)

char *str  ;
char  separ;

  {
  char *tail  = NULL;
  int   found = 0   ;
  int   len   ;
  int   i     ;

  if (str != NULL)
    {
    len = strlen (str);

    for (i=len-1 ; i>0 ; i--)
      {
      if (str [i] == separ)
        {
        found = 1;
        break;
        }
      }

    if (found != 0)
      tail = utl_SaveString (str + i + 1);
    else
      tail = utl_SaveString (str        );
    }

  return (tail);
  }
