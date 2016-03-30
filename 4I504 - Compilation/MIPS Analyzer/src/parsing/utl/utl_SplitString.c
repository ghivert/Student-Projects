
/* ###--------------------------------------------------------------### */
/* file		: utl_SplitString.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SplitString					*/
/* description	: split a string into a list of strings regarding a	*/
/*		  separator						*/
/* called func.	: utl_SaveNString, utl_addutchn				*/
/* ###--------------------------------------------------------------### */

struct utchn *utl_SplitString (str, separ)

char *str  ;
char  separ;

  {
  struct utchn *pt_chn  = NULL;
  char         *tmp_str = NULL;
  int           idx     = 0   ;
  int           i       = 0   ;

  if (str != NULL)
    {
    while (str [i] != '\0')
      {
      if (str [i] == separ)
        {
        if (i != idx)
          {
          tmp_str = utl_SaveNString (str + idx,          i - idx);
          pt_chn  = utl_addutchn    (pt_chn   , (union utdat)(void *) tmp_str);
          }
        idx = i + 1;
        }
      i++;
      }

    if (i != idx)
      {
      tmp_str = utl_SaveNString (str + idx,          i - idx);
      pt_chn  = utl_addutchn    (pt_chn   , (union utdat)(void *) tmp_str);
      }
    }

  return (pt_chn);
  }
