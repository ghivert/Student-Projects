
/* ###--------------------------------------------------------------### */
/* file		: utl_CutString.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_CutString						*/
/* description	: cut a string into a header and a tailer.		*/
/*		  The string is scanned from the beginning looking for	*/
/*		  the separator. The the first characters of the string	*/
/*		  including the separator are put into the header. The	*/
/*		  last characters are put into the tailer.		*/
/*		  If the separator is not found the header is null and	*/
/*		  the tailer contains all the character of the input	*/
/*		  string.						*/
/* called func.	: utl_SaveString, utl_SaveNString			*/
/* ###--------------------------------------------------------------### */

void utl_CutString (str, pt_head, pt_tail, separ)

char  *str    ;
char **pt_head;
char **pt_tail;
char   separ  ;

  {
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
      {
      *pt_head = utl_SaveNString (str , i    );
      *pt_tail = utl_SaveString  (str + i + 1);
      }
    else
      {
      *pt_head = NULL;
      *pt_tail = utl_SaveString  (str        );
      }
    }
  }
