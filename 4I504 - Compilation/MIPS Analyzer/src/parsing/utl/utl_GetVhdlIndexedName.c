
/* ###--------------------------------------------------------------### */
/* file		: utl_GetVhdlIndexedName.c				*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetVhdlIndexedName				*/
/* description	: return an indexed name from a name			*/
/*									*/
/* called func.	: utl_GetNameIndex, utl_GetRHeaderString,		*/
/*		  utl_SaveString  , utl_GetVhdlName			*/
/* ###--------------------------------------------------------------### */

char *utl_GetVhdlIndexedName (name)

char *name;

  {
  int           indx                  ;
  char         *indx_name             = NULL;
  char          buf [UTL_STR__MAXLEN] ;

	/* ###------------------------------------------------------### */
	/*    a pointer on a name is given as argument. The input name	*/
	/* may be a simple name - "toto" - or an indexed name -		*/
	/* "toto 4".							*/
	/*								*/
	/*    The function returns the VHDL indexed name - either	*/
	/* "toto" or "toto (4)".					*/
	/* ###------------------------------------------------------### */

  indx = utl_GetNameIndex (name, ' ');

  if (indx == -1)
    indx_name = utl_GetVhdlName (name);
  else
    {
    name = utl_GetRHeaderString (name, ' ');
    sprintf (buf, "%s (%d)", utl_GetVhdlName (name), indx);
    indx_name = utl_SaveString (buf);
    }

  return (indx_name);
  }
