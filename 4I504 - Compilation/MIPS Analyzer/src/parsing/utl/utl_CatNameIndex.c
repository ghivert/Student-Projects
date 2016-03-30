
/* ###--------------------------------------------------------------### */
/* file		: utl_CatNameIndex.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_CatNameIndex					*/
/* description	: return an indexed name ('name <delimiter> index')	*/
/*									*/
/*		  any string can be used as input. If the input string	*/
/*		  represent a name followed by an index, the function	*/
/*		  returns 'name <delimiter> index'. Otherwise, the	*/
/*		  input string is returned				*/
/*									*/
/* called func.	: utl_SaveString					*/
/* ###--------------------------------------------------------------### */

char *utl_CatNameIndex (str, opn_del, idx)

char         *str    ;
char          opn_del;
unsigned int  idx    ;

  {
  char   buf [UTL_STR__MAXLEN] ;
  char   cls_del               =  0  ;
  char  *name                  = NULL;

	/* ###------------------------------------------------------### */
	/*   any string can be used as input. The function returns	*/
	/* 'name <delimiter> index'.					*/
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

    if (cls_del != 0)
      sprintf (buf, "%s%c%d%c", str, opn_del, idx, cls_del);
    else
      sprintf (buf, "%s%c%d"  , str, opn_del, idx         );

    name = utl_SaveString (buf);
    }

  return (name);
  }
