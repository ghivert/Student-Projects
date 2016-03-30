
/* ###--------------------------------------------------------------### */
/* file		: utl_GetNameWithIndex.c				*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetNameWithIndex					*/
/* description	: return an indexed name ('name index')			*/
/*									*/
/*		  any string can be used as input. If the input string	*/
/*		  represent a name followed by an index, the function	*/
/*		  returns 'name index'. Otherwise, the input string is	*/
/*		  returned						*/
/*									*/
/* called func.	: utl_SaveString					*/
/* ###--------------------------------------------------------------### */

char *utl_GetNameWithIndex (str, opn_sep)

char *str    ;
char  opn_sep;

  {
  char   buf [UTL_STR__MAXLEN] ;
  char   cls_sep               =  0  ;
  int    state                 =  0  ;
  int    idx                   =  0  ;
  int    pos                   =  0  ;
  int    i                     =  0  ;
  int    c                     ;
  char  *name                  = NULL;

	/* ###------------------------------------------------------### */
	/*   any string can be used as input. If the input string	*/
	/* represent a name followed by an index, the function returns	*/
	/*'name index'. Otherwise, the input string is returned.	*/
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
      buf [i] = c;
      switch (state)
        {
        case 0 :
          if        (c == opn_sep)                 { pos = i ; state = 1; }
          break;

        case 1 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   =               c - '0' ;
            state = 2;
            }
          else if   (c == opn_sep)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 1;
          else                                                 state = 0;
          break;

        case 2 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   = (idx * 10) + (c - '0');
            state = 2;
            }
          else if   (c == opn_sep)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_sep)                             state = 4;
          else                                                 state = 0;
          break;

        case 3 :
          if        (c == opn_sep)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_sep)                             state = 4;
          else                                                 state = 0;
          break;

        case 4 :
          if        (c == opn_sep)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 4;
          else                                                 state = 0;
          break;
        }

      i ++;
      }

    if ( ((state == 4)                )                   ||
        (((state == 3) || (state == 2)) && (cls_sep == 0))  )
      sprintf (buf + pos, " %d", idx);
    else
      buf [i] = '\0' ;

    name = utl_SaveString (buf);
    }

  return (name);
  }
