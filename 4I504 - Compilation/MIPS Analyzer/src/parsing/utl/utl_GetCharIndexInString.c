
/* ###--------------------------------------------------------------### */
/* file		: utl_GetCharIndexInString.c				*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetCharIndexInString				*/
/* description	: scanning the string from its first character, return	*/
/*		  the index of the first occurance of a character.	*/
/*		  The function returns -1 if the character is not found	*/
/*									*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_GetCharIndexInString (str, separ)

char *str  ;
char  separ;

  {
  int found = 0   ;
  int i     = 0   ;

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

    if (found == 0)
      i = -1;
    }

  return (i);
  }
