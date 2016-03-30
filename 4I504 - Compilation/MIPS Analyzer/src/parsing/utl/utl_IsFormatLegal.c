
/* ###--------------------------------------------------------------### */
/* file		: utl_IsFormatLegal.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_IsFormatLegal					*/
/* description	: return non null value if a print format is legal	*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_IsFormatLegal (str)

char  *str;

  {
  int           o_prn   = 0   ;
  int           state   = 0   ;
  int           flag    = 0   ;
  int           i       = 0   ;
  char          c       ;

  if (str != NULL)
    {
    while (((c = str [i]) != '\0') && (o_prn >= 0))
      {
      i ++;

      switch (state)
        {
        case 0 :
          if      (c == '%') {state = 1;           }
          break;
        case 1 :
          if      (c == '(') {state = 0; o_prn ++; }
          else if (c == ')') {state = 0; o_prn --; }
          else               {state = 0;           }
          break;
        }
      }

    if (o_prn == 0)
      flag = 1;
    }

  return (flag);
  }
