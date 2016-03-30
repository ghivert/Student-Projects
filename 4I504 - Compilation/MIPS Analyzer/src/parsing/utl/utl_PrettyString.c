
/* ###--------------------------------------------------------------### */
/* file		: utl_PrettyString.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_PrettyString					*/
/* description	: replace some space characters by '\n' in a string.	*/
/*		  This function modifies the input string		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

char *utl_PrettyString (str, max)

char         *str;
unsigned int  max;

  {
  unsigned int count = 0;
  unsigned int i     = 0;

  while (str [i] != '\0')
    {
    if ((count > max) && ((str [i] == ' ') || (str [i] == '\t')))
      {
      str [i] = '\n';
      count   = 0   ;
      }
    count ++;
    i     ++;
    }

  return (str);
  }
