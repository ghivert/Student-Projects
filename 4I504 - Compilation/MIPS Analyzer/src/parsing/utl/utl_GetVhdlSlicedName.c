
/* ###--------------------------------------------------------------### */
/* file		: utl_GetVhdlSlicedName.c				*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetVhdlSlicedName					*/
/* description	: build a sliced name from a list			*/
/*									*/
/* called func.	: utl_GetNameIndex, utl_GetRHeaderString,		*/
/*		  utl_SaveString					*/
/* ###--------------------------------------------------------------### */

char *utl_GetVhdlSlicedName (pt_lst)

struct utchn **pt_lst;

  {
  struct utchn *pt_chn                = NULL;
  int           indx                  ;
  int           left                  ;
  int           right                 ;
  int           incr                  = 0   ;
  char         *name                  = NULL;
  char          buf [UTL_STR__MAXLEN] ;

	/* ###------------------------------------------------------### */
	/*    a pointer on a list is given as argument. Each element	*/
	/* contains a name. A name may be a simple name - "toto" - or	*/
	/* an indexed name - "toto 4".					*/
	/*								*/
	/*    The list is scanned as long as the name is an indexed	*/
	/* name, the base name remains the same and the indexes		*/
	/* represent a range (ascendent or descendent).			*/
	/*								*/
	/*    The function returns the result sliced name. The pointer	*/
	/* on the list is modified to points the first element that	*/
	/* is not part of the sliced name.				*/
	/* ###------------------------------------------------------### */

  if (pt_lst != NULL)
    {
    pt_chn = *pt_lst;
    if (pt_chn != NULL)
      {
      left = utl_GetNameIndex ((char *) pt_chn->DATA.VPNT, ' ');

      if (left == -1)
        {
        name   = (char *) pt_chn->DATA.VPNT;
        pt_chn =          pt_chn->NEXT     ;
        }
      else
        {
        name   = utl_GetRHeaderString ((char *) pt_chn->DATA.VPNT, ' ');
        pt_chn = pt_chn->NEXT;

        while (pt_chn != NULL)
          {
          if (name != utl_GetRHeaderString ((char *) pt_chn->DATA.VPNT, ' '))
            break;

          indx = utl_GetNameIndex ((char *) pt_chn->DATA.VPNT, ' ');
          if (incr == 0)
            {
            right = indx;

            if      (indx == (left + 1)) incr =  1;
            else if (indx == (left - 1)) incr = -1;
            else                         break    ;
            }
          else
            {
            if (indx == (right + incr))
              right = indx;
            else
              break;
            }

          pt_chn = pt_chn->NEXT;
          }

        if (incr ==  0) sprintf (buf, "%s (%d)"          , name, left       );
        if (incr ==  1) sprintf (buf, "%s (%d to %d)"    , name, left, right);
        if (incr == -1) sprintf (buf, "%s (%d downto %d)", name, left, right);

        name = utl_SaveString (buf);
        }

      *pt_lst = pt_chn;
      }
    }

  return (name);
  }
