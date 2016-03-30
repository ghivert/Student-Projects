
/* ###--------------------------------------------------------------### */
/* file		: utl_GetNameIndex.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetNameIndex					*/
/* description	: return the index ending a name if it exists or -1	*/
/*									*/
/*		  any string can be used as input. If the input string	*/
/*		  represent a name followed by an index, the function	*/
/*		  returns the index. Otherwise, -1 is returned		*/
/*									*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int utl_GetNameIndex (str, opn_sep)

char *str    ;
char  opn_sep;

  {
  char   cls_sep =  0  ;
  int    state   =  0  ;
  int    idx     = -1  ;
  int    i       =  0  ;
  int    c       ;

	/* ###------------------------------------------------------### */
	/*   any string can be used as input. If the input string	*/
	/* represent a name followed by an index, the function returns	*/
	/* the index. Otherwise, -1 is returned.			*/
	/*								*/
	/*   Any character may be used as the separator between the	*/
	/* name and the index.						*/
	/*								*/
	/*   If the separator is '{', '[', '(', or '>' the index must	*/
	/* be followed by the dual character : '}', ']', ')' or '>'.	*/
	/* ###------------------------------------------------------### */

  if (str != NULL)
    {
    if      (opn_sep == '{') cls_sep = '}';
    else if (opn_sep == '[') cls_sep = ']';
    else if (opn_sep == '(') cls_sep = ')';
    else if (opn_sep == '<') cls_sep = '>';

    while ((c = str [i]) != '\0')
      {
      switch (state)
        {
        case 0 :
          if        (c == opn_sep)                 { idx = -1; state = 1; }
          break;

        case 1 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   =               c - '0' ;
            state = 2;
            }
          else if   (c == opn_sep)                 { idx = -1; state = 1; }
          else if  ((c == ' '    ) || (c == '\t')) { idx = -1; state = 1; }
          else                                                 state = 0;
          break;

        case 2 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   = (idx * 10) + (c - '0');
            state = 2;
            }
          else if   (c == opn_sep)                 { idx = -1; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_sep)                             state = 4;
          else                                                 state = 0;
          break;

        case 3 :
          if        (c == opn_sep)                 { idx = -1; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_sep)                             state = 4;
          else                                                 state = 0;
          break;

        case 4 :
          if        (c == opn_sep)                 { idx = -1; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 4;
          else                                                 state = 0;
          break;
        }

      i ++;
      }
    }

  return (idx);
  }
