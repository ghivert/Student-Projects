
/* ###--------------------------------------------------------------### */
/* file		: utl_GetHeaderString.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetHeaderString					*/
/* description	: return the header of a string				*/
/* called func.	: utl_SaveString, utl_SaveNString			*/
/* ###--------------------------------------------------------------### */

char *utl_GetHeaderString (str, separ)

char *str  ;
char  separ;

  {
  char *head  = NULL;
  int   found = 0   ;
  int   i     = 0   ;

  if (str != NULL)
    {
    while (str [i] != '\0')
      {
      if (str [i] == separ)
        {
        found = 1;
        break;
        }
      i++;
      }

    if (found != 0)
      head = utl_SaveNString (str, i);
    else
      head = utl_SaveString  (str   );
    }

  return (head);
  }
