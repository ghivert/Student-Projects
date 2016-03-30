
/* ###--------------------------------------------------------------### */
/* file		: utl_CharToAscii.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_CharToAscii					*/
/* description	: convert a character (including escape sequences) into	*/
/*		  ascci code						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

char utl_CharToAscii (str, pt_str)

char  *str   ;
char **pt_str;

  {
  char code    = 0;

  if (str != NULL)
    {
    if (*str != '\\')
      {
      code   = *str    ;
      str ++ ;
      }
    else
      {
      str ++;
      switch (*str)
        {
        case 'a'  : code = '\a'; str ++; break;
        case 'b'  : code = '\b'; str ++; break;
        case 'f'  : code = '\f'; str ++; break;
        case 'n'  : code = '\n'; str ++; break;
        case 'r'  : code = '\r'; str ++; break;
        case 't'  : code = '\t'; str ++; break;
        case 'v'  : code = '\v'; str ++; break;
        case '\\' : code = '\\'; str ++; break;
        case '\"' : code = '\"'; str ++; break;
        case '\'' : code = '\''; str ++; break;
        case '\?' : code = '\?'; str ++; break;

        case 'x'  :
          str ++;
          while (utl_isxdigit (*str) != 0)
            {
            code = (code << 4) + utl_CharToInt (*str);
            str ++;
            }
          break ;

        case '0' :
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
          code = (code << 3) + utl_CharToInt (*str);
          str ++;

          if (utl_isodigit (*str) != 0)
            {
            code = (code << 3) + utl_CharToInt (*str);
            str ++;

            if (utl_isodigit (*str) != 0)
              {
              code = (code << 3) + utl_CharToInt (*str);
              str ++;
              }
            }
          break ;
        }
      }

    if (pt_str != NULL)
      *pt_str = str;
    }

  return (code);
  }
