
/* ###--------------------------------------------------------------### */
/* file		: utl_GetName.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetName						*/
/* description	: return an indexed name ('name <delimiter> index')	*/
/*									*/
/*		  any string can be used as input. If the input string	*/
/*		  represent a name followed by an index, the function	*/
/*		  returns 'name <delimiter> index'. Otherwise, the	*/
/*		  input string is returned				*/
/*									*/
/* called func.	: utl_SaveString					*/
/* ###--------------------------------------------------------------### */

char *utl_GetName (str, opn_del, new_opn)

char *str    ;
char  opn_del;
char  new_opn;

  {
  char   buf [UTL_STR__MAXLEN] ;
  char   cls_del               =  0  ;
  char   new_cls               =  0  ;
  int    state                 =  0  ;
  int    idx                   =  0  ;
  int    pos                   =  0  ;
  int    i                     =  0  ;
  int    c                     ;
  char  *name                  = NULL;

	/* ###------------------------------------------------------### */
	/*   any string can be used as input. If the input string	*/
	/* represent a name followed by an index, the function returns	*/
	/* 'name <delimiter> index'.					*/
	/* Otherwise, the input string is returned			*/
	/*								*/
	/*   Any character may be used as the delimiter between the	*/
	/* name and the index.						*/
	/*								*/
	/*   If the delimiter is '{', '[', '(', or '>' the index will	*/
	/* be followed by the dual character : '}', ']', ')' or '>' in	*/
	/* the returned string.						*/
	/* ###------------------------------------------------------### */

  if (str != NULL)
    {
    if      (opn_del == '{') cls_del = '}';
    else if (opn_del == '[') cls_del = ']';
    else if (opn_del == '(') cls_del = ')';
    else if (opn_del == '<') cls_del = '>';

    if      (new_opn == '{') new_cls = '}';
    else if (new_opn == '[') new_cls = ']';
    else if (new_opn == '(') new_cls = ')';
    else if (new_opn == '<') new_cls = '>';

    while ((c = str [i]) != '\0')
      {
      buf [i] = c;
      switch (state)
        {
        case 0 :
          if        (c == opn_del)                 { pos = i ; state = 1; }
          break;

        case 1 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   =               c - '0' ;
            state = 2;
            }
          else if   (c == opn_del)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 1;
          else                                                 state = 0;
          break;

        case 2 :
          if       ((c >= '0'    ) && (c <= '9' ))
            {
            idx   = (idx * 10) + (c - '0');
            state = 2;
            }
          else if   (c == opn_del)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_del)                             state = 4;
          else                                                 state = 0;
          break;

        case 3 :
          if        (c == opn_del)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 3;
          else if   (c == cls_del)                             state = 4;
          else                                                 state = 0;
          break;

        case 4 :
          if        (c == opn_del)                 { pos = i ; state = 1; }
          else if  ((c == ' '    ) || (c == '\t'))             state = 4;
          else                                                 state = 0;
          break;
        }

      i ++;
      }

    if ( ((state == 4)                )                   ||
        (((state == 3) || (state == 2)) && (cls_del == 0))  )
      {
      if (new_cls == 0)
        sprintf (buf + pos, "%c%d"  , new_opn, idx         );
      else
        sprintf (buf + pos, "%c%d%c", new_opn, idx, new_cls);
      }
    else
      buf [i] = '\0' ;

    name = utl_SaveString (buf);
    }

  return (name);
  }
