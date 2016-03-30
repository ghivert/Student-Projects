
/* ###--------------------------------------------------------------### */
/* file		: utl_error.c						*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_error						*/
/* description	: print an error message				*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

#define UTL_ERR__NBR   5

unsigned int utl_error (code, func, s1, n1)

int    code;
char  *func;
char  *s1  ;
int    n1  ;

  {
  static char         *msg [] =
    {
    "unknown error%.0s%.0u\n"                                 ,	/*    0	*/
    "no more space for %.0s%u\n"                              ,	/*    1	*/
    "cannot open file `%s`%.0u\n"                             ,	/*    2	*/
    "overwriting not allowed%.0s%.0u\n"                       ,	/*    3	*/
    "illegal print format : `%s`%.0u\n"                        	/*    4 */
    } ;

  static unsigned int  lvl [] =
    {
    0x00000001                                                ,	/*    0	*/
    0x00000001                                                ,	/*    1	*/
    0x00000001                                                ,	/*    2	*/
    0x00000004                                                ,	/*    3	*/
    0x00000004                                                 	/*    4	*/
    } ;

  UTL_STATUS |= UTL_STS__ERROR;

  if (code >= UTL_ERR__NBR)
    code = 0;

  if ((lvl [code] & UTL_ERR_LEVEL) != 0)
    {
    fprintf (stderr, "UTL Error: %s: ", func    );
    fprintf (stderr,  msg [code]      , s1  , n1);

    if (lvl [code] == 0x00000001)
      {
      fprintf (stderr, "\n\tFatal error\n");
      exit    (-1);
      }
    }

  return (1);
  }
