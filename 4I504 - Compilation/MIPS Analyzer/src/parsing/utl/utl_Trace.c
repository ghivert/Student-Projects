
/* ###--------------------------------------------------------------### */
/* file		: utl_Trace.c						*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_Trace						*/
/* description	: print the name of the current function		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_Trace (name, flag)

char *name;
int   flag;

  {
  static char space [16] = "               ";
  static int  level      = 1                ;

  if (flag == UTL_FUN__IN)
    {
    if (level <= UTL_TRC_LEVEL)
      printf ("%s-->> (%.2d) %s\n", &space [16-level], level, name);
    level ++;
    }
  else
    {
    level --;
    if (level <= UTL_TRC_LEVEL)
      printf ("%s<<-- (%.2d) %s\n", &space [16-level], level, name);
    }
  }
