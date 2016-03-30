
/* ###--------------------------------------------------------------### */
/* file		: utl_Open.c						*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_Open						*/
/* description	: open a file. `path` is an envionment variable that	*/
/*		  gives the list of searched directories. `extn` is	*/
/*		  the suffix string to be added to the file name.	*/
/*									*/
/* called func.	: fopen, utl_error					*/
/* ###--------------------------------------------------------------### */

FILE *utl_Open (name, path, extn, mode)

char *name;
char *path;
char *extn;
char *mode;

  {
  char          buf [UTL_STR__MAXLEN] ;
  struct utchn *pt_chn                = NULL;
  FILE         *fp                    = NULL;

  if (path != NULL)
    path = getenv (path);

  if (path == NULL)
    {
    if (extn == NULL)
      sprintf (buf, "%s"   , name      );
    else
      sprintf (buf, "%s.%s", name, extn);

    fp = fopen (buf, mode);
    }
  else
    {
    pt_chn = utl_SplitString (path, ':');
    while (pt_chn != NULL)
      {
      if (extn == NULL)
        sprintf (buf, "%s/%s"   , (char *) pt_chn->DATA.VPNT, name      );
      else
        sprintf (buf, "%s/%s.%s", (char *) pt_chn->DATA.VPNT, name, extn);

      if ((fp = fopen (buf, mode)) != NULL)
        break;

      pt_chn = pt_chn->NEXT;
      }
    }

  if (fp == NULL)
    utl_error (2, "utl_Open", buf, 0);

  return (fp);
  }
