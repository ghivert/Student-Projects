
/* ###--------------------------------------------------------------### */
/* file		: utl_GetRHeaderString.c				*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetRHeaderString					*/
/* description	: return the header of a string (reverse)		*/
/* called func.	: utl_SaveString, utl_SaveNString			*/
/* ###--------------------------------------------------------------### */

char *utl_GetRHeaderString (str, separ)

char *str  ;
char  separ;

  {
  char *head  = NULL;
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
      head = utl_SaveNString (str, i);
    else
      head = utl_SaveString  (str   );
    }

  return (head);
  }
