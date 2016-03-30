
/* ###--------------------------------------------------------------### */
/* file		: utl_fprutchn.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_fprutchn						*/
/* description	: print a list of structures and return the number of	*/
/*		  characters printed					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_fprutchn (fp, format, pt_chn, func)

FILE           *fp      ;
char           *format  ;
struct utchn   *pt_chn  ;
char         *(*func) ();

  {
  unsigned int  idx  = 0;
  char         *str  ;
  char         *head ;
  char         *midd ;
  char         *tail ;
  char         *m_hd ;
  char         *m_tl ;
  char          m_md ;

  if (utl_SplitFormat (format, &head, &midd, &tail) != 0)
    {
    idx += fprintf (fp, head);

    if (func != NULL)
      {
      while (pt_chn != NULL)
        {
        str     = (*func ) (pt_chn->DATA );
        idx    += fprintf  (fp, midd, str);
        pt_chn  = pt_chn->NEXT;
        }
      }
    else
      {
      m_md = utl_SplitFlatFormat (midd, &m_hd, &m_tl);
      while (pt_chn != NULL)
        {
        idx  += fprintf  (fp, m_hd);

        if (m_md == 's') idx += fprintf (fp, "%s"  ,(char *) pt_chn->DATA.VPNT);
        if (m_md == 'u') idx += fprintf (fp, "%u"    ,       pt_chn->DATA.UINT);
        if (m_md == 'x') idx += fprintf (fp, "0x%.8x",       pt_chn->DATA.UINT);
        if (m_md == 'd') idx += fprintf (fp, "%d"    ,       pt_chn->DATA.SINT);
        if (m_md == 'c') idx += fprintf (fp, "%c"    ,       pt_chn->DATA.CHAR);
        if (m_md == 'e') idx += fprintf (fp, "%e"    ,       pt_chn->DATA.FLOT);

        idx    += fprintf  (fp, m_tl);
        pt_chn  = pt_chn->NEXT;
        }
      }

    idx += fprintf (fp, tail);
    }

  return (idx);
  }
