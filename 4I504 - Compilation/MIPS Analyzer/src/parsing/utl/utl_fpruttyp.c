
/* ###--------------------------------------------------------------### */
/* file		: utl_fpruttyp.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_fpruttyp						*/
/* description	: print a list of structures and return the number of	*/
/*		  characters printed					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

unsigned int utl_fpruttyp (fp, format, pt_typ, f_d1, f_d2)

FILE           *fp      ;
char           *format  ;
struct uttyp   *pt_typ  ;
char         *(*f_d1) ();
char         *(*f_d2) ();

  {
  unsigned int  idx   = 0;
  char         *dt1   ;
  char         *dt2   ;
  char         *head  ;
  char         *midd  ;
  char         *tail  ;
  char         *m_hd  ;
  char         *m_tl  ;
  char         *mt_hd ;
  char         *mt_tl ;
  char          m_f1  ;
  char          m_f2  ;

  if (utl_SplitFormat (format, &head, &midd, &tail) != 0)
    {
    idx   += fprintf             (fp  , head          );
    m_f1   = utl_SplitFlatFormat (midd, &m_hd , &m_tl );
    m_f2   = utl_SplitFlatFormat (m_tl, &mt_hd, &mt_tl);

    if ((f_d1 != NULL) && (f_d2 != NULL))
      {
      while (pt_typ != NULL)
        {
        dt1     = (*f_d1   ) (pt_typ->DAT1      );
        dt2     = (*f_d2   ) (pt_typ->DAT2      );
        idx    +=   fprintf  (fp, midd, dt1, dt2);

        pt_typ  = pt_typ->NEXT;
        }
      }

    if ((f_d1 != NULL) && (f_d2 == NULL))
      {
      while (pt_typ != NULL)
        {
        dt1   = (*f_d1   ) (pt_typ->DAT1      );
        idx  +=   fprintf  (fp, "%s%s%s", m_hd, dt1, mt_hd);

        if (m_f2 == 's') idx += fprintf (fp, "%s"  ,(char *) pt_typ->DAT2.VPNT);
        if (m_f2 == 'u') idx += fprintf (fp, "%u"    ,       pt_typ->DAT2.UINT);
        if (m_f2 == 'x') idx += fprintf (fp, "0x%.8x",       pt_typ->DAT2.UINT);
        if (m_f2 == 'd') idx += fprintf (fp, "%d"    ,       pt_typ->DAT2.SINT);
        if (m_f2 == 'c') idx += fprintf (fp, "%c"    ,       pt_typ->DAT2.CHAR);
        if (m_f2 == 'e') idx += fprintf (fp, "%e"    ,       pt_typ->DAT2.FLOT);

        idx    += fprintf  (fp, mt_tl);
        pt_typ  = pt_typ->NEXT;
        }
      }

    if ((f_d1 == NULL) && (f_d2 != NULL))
      {
      while (pt_typ != NULL)
        {
        idx  += fprintf  (fp, m_hd);

        if (m_f1 == 's') idx += fprintf (fp, "%s"  ,(char *) pt_typ->DAT1.VPNT);
        if (m_f1 == 'u') idx += fprintf (fp, "%u"    ,       pt_typ->DAT1.UINT);
        if (m_f1 == 'x') idx += fprintf (fp, "0x%.8x",       pt_typ->DAT1.UINT);
        if (m_f1 == 'd') idx += fprintf (fp, "%d"    ,       pt_typ->DAT1.SINT);
        if (m_f1 == 'c') idx += fprintf (fp, "%c"    ,       pt_typ->DAT1.CHAR);
        if (m_f1 == 'e') idx += fprintf (fp, "%e"    ,       pt_typ->DAT1.FLOT);

        dt2     = (*f_d2   ) (pt_typ->DAT2 );
        idx    +=   fprintf  (fp, m_tl, dt2);

        pt_typ  = pt_typ->NEXT;
        }
      }

    if ((f_d1 == NULL) && (f_d2 == NULL))
      {
      while (pt_typ != NULL)
        {
        idx  += fprintf  (fp, m_hd);

        if (m_f1 == 's') idx += fprintf (fp, "%s"  ,(char *) pt_typ->DAT1.VPNT);
        if (m_f1 == 'u') idx += fprintf (fp, "%u"    ,       pt_typ->DAT1.UINT);
        if (m_f1 == 'x') idx += fprintf (fp, "0x%.8x",       pt_typ->DAT1.UINT);
        if (m_f1 == 'd') idx += fprintf (fp, "%d"    ,       pt_typ->DAT1.SINT);
        if (m_f1 == 'c') idx += fprintf (fp, "%c"    ,       pt_typ->DAT1.CHAR);
        if (m_f1 == 'e') idx += fprintf (fp, "%e"    ,       pt_typ->DAT1.FLOT);

        idx  += fprintf  (fp, mt_hd);

        if (m_f2 == 's') idx += fprintf (fp, "%s"  ,(char *) pt_typ->DAT2.VPNT);
        if (m_f2 == 'u') idx += fprintf (fp, "%u"    ,       pt_typ->DAT2.UINT);
        if (m_f2 == 'x') idx += fprintf (fp, "0x%.8x",       pt_typ->DAT2.UINT);
        if (m_f2 == 'd') idx += fprintf (fp, "%d"    ,       pt_typ->DAT2.SINT);
        if (m_f2 == 'c') idx += fprintf (fp, "%c"    ,       pt_typ->DAT2.CHAR);
        if (m_f2 == 'e') idx += fprintf (fp, "%e"    ,       pt_typ->DAT2.FLOT);

        idx    += fprintf  (fp, mt_tl);
        pt_typ  = pt_typ->NEXT;
        }
      }

    idx += fprintf (fp, tail);
    }

  return (idx);
  }
