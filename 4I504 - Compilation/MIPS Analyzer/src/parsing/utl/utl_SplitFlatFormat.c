
/* ###--------------------------------------------------------------### */
/* file		: utl_SplitFlatFormat.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SplitFlatFormat					*/
/* description	: split a flat print format into a header and a tailer.	*/
/*		  return the character that represent the format	*/ 
/* called func.	: utl_SaveStringWithMode				*/
/* ###--------------------------------------------------------------### */

char utl_SplitFlatFormat (str, head, tail)

char  *str ;
char **head;
char **tail;

  {
  int   i     = 0   ;
  int   state = 0   ;
  char  c     ;
  char  fmt   = 0   ;

  if (str != NULL)
    {
    while (((c = str [i]) != '\0') && (state != -1))
      {
      i ++;

      switch (state)
        {
        case 0 :
          if      (c == '%') {state =  1;         }
          break;
        case 1 :
          if      (c == '%') {state =  0;         }
          else               {state = -1; fmt = c;}
          break;
        } 
      }

    if (state == -1)
      {
      *head = utl_SaveNStringWithMode (str    , i - 2, UTL_STR__NOP);
      *tail = utl_SaveStringWithMode  (str + i,        UTL_STR__NOP);
      }
    else
      {
      *head = utl_SaveStringWithMode  (str    ,        UTL_STR__NOP);
      *tail = NULL;
      }
    }

  return (fmt);
  }
