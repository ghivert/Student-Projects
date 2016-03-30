
/* ###--------------------------------------------------------------### */
/* file		: utl_SplitFormat.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SplitFormat					*/
/*									*/
/* description	: split a print format string into three parts : header	*/
/*		  middle end tailer					*/
/*									*/
/* called func.	: utl_IsFormatLegal     , utl_SaveNStringWithMode,	*/
/*		  utl_SaveStringWithMode				*/
/* ###--------------------------------------------------------------### */

int utl_SplitFormat (str, head, midd, tail)

char  *str ;
char **head;
char **midd;
char **tail;

  {
  int           state   = 0   ;
  int           flag    = 0   ;
  int           h_len   = 0   ;
  int           m_len   = 0   ;
  int           m_idx   = 0   ;
  int           t_idx   = 0   ;
  int           i       = 0   ;
  char          c       ;

  if ((str != NULL) && (utl_IsFormatLegal (str) != 0))
    {
    while ((c = str [i]) != '\0')
      {
      i ++;

      switch (state)
        {
        case 0 :
          if   (c == '%') {state = 1;           }
          break;
        case 1 :
          if   (c == '(') {state = 2; m_idx = i;}
          else            {state = 0;           }
          break;

        case 2 :
          if   (c == '%') {state = 3;           }
          break;
        case 3 :
          if   (c == ')') {state = 2; t_idx = i;}
          else            {state = 2;           }
          break;
        }
      }

    h_len = m_idx         - 2;
    m_len = t_idx - m_idx - 2;

    if (h_len >= 0)
      {
      *head = utl_SaveNStringWithMode (str        , h_len, UTL_STR__NOP);
      *midd = utl_SaveNStringWithMode (str + m_idx, m_len, UTL_STR__NOP);
      *tail = utl_SaveStringWithMode  (str + t_idx,        UTL_STR__NOP);
      flag  = 3   ;
      }
    else
      {
      *head = utl_SaveStringWithMode  (str,            UTL_STR__NOP);
      *midd = NULL;
      *tail = NULL;
      flag  = 1   ;
      }
    }

  return (flag);
  }
