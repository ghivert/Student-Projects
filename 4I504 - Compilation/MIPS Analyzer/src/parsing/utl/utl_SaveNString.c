
/* ###--------------------------------------------------------------### */
/* file		: utl_SaveNString.c					*/
/* date		: Apr 19 2004						*/
/* version	: v200							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: utility function library				*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_SaveNString					*/
/* description	: make memory allocation for a character string		*/
/* called func.	: utl_Trace, utl_hash2, utl_alcbyt, utl_adduttyp.	*/
/*		  utl_alloc						*/
/* ###--------------------------------------------------------------### */

char *utl_SaveNString (str, n)

char         *str;
unsigned int  n  ;

  {
  char          buf [UTL_STR__MAXLEN] ;
  char         *svd_str               = NULL;
  struct uttyp *pt_typ                ;
  unsigned int  size                  = 0   ;
  unsigned int  hsh_cod1              ;
  unsigned int  hsh_cod2              ;
  unsigned int  tab_idx               ;
  int           i                     ;

	/* ###------------------------------------------------------### */
	/*   This function is used to save a string in the memory. It	*/
	/* returns the location where the string has been saved. On the	*/
	/* first call, a space is allocated and the string is saved.	*/
	/* For the subsequential calls, the function simply returns	*/
	/* the location where the string has been saved.		*/
	/*								*/
	/*   The set of saved strings are accessed from a hash table. A	*/
	/* hash function is used to generate a hash code from the list	*/
	/* of characters that compose the string.			*/
	/*								*/
	/*   The input string is first converted depending on the	*/
	/* current conversion mode (upper case, lower case or none).	*/
	/*								*/
	/*   The resulted string is hashed to ease the scanning of	*/
	/* stored strings. Two hash codes are produced to speedup the	*/
	/* scanning. If the string is found in the hash table, its	*/
	/* pointer is returned. Otherwise, a space is allocated and the	*/
	/* string is stored in the hash table.				*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_SaveNString", UTL_FUN__IN);

	/* ###------------------------------------------------------### */
	/*   initialize the hash table					*/
	/* ###------------------------------------------------------### */

  if (UTL_STRTAB == NULL)
    {
    UTL_STRTAB = (struct uttyp **)
                 utl_alloc (sizeof (struct uttyp *) * UTL_STR__TABLESIZE);

    for (i=0 ; i<UTL_STR__TABLESIZE ; i++)
      UTL_STRTAB [i] = NULL;
    }

	/* ###------------------------------------------------------### */
	/*   conversion (lower or upper case)				*/
	/* ###------------------------------------------------------### */

  if (str != NULL)
    {
    if ((UTL_STR_MODE & UTL_STR__UPPER) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        {
        if ((buf [size] <= 'z') && (buf [size] >= 'a')) 
          buf [size] = buf [size] - 'a' + 'A';

        size ++;
        }
      }

    if ((UTL_STR_MODE & UTL_STR__LOWER) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        {
        if ((buf [size] <= 'Z') && (buf [size] >= 'A')) 
          buf [size] = buf [size] - 'A' + 'a';

        size ++;
        }
      }

    if ((UTL_STR_MODE & UTL_STR__NOP  ) != 0)
      {
      while (((buf [size] = str [size]) != '\0') && (size < n))
        size ++;
      }

    buf [size] = '\0';
    size ++;

	/* ###------------------------------------------------------### */
	/*   hash code							*/
	/* ###------------------------------------------------------### */

    utl_hash2 (buf, &hsh_cod1, &hsh_cod2);

	/* ###------------------------------------------------------### */
	/*   check if the string has already been saved in the table	*/
	/* ###------------------------------------------------------### */

    tab_idx = hsh_cod1 % UTL_STR__TABLESIZE;
    pt_typ  = UTL_STRTAB [tab_idx];
    while (pt_typ != NULL)
      {
      if ((pt_typ->DAT2.UINT == hsh_cod2            ) &&
          (!strcmp (buf, (char *) pt_typ->DAT1.VPNT))   )
        break;
      pt_typ = pt_typ->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   if the string has never been saved, create a string and	*/
	/* save it in the table						*/
	/* ###------------------------------------------------------### */

    if (pt_typ == NULL)
      {
      svd_str = utl_alcbyt (size);
      strcpy (svd_str, buf);

      pt_typ               = utl_adduttyp (NULL, (void *) svd_str, hsh_cod2);
      pt_typ->NEXT         = UTL_STRTAB [tab_idx];
      UTL_STRTAB [tab_idx] = pt_typ;
      }
    else
      svd_str = (char *) pt_typ->DAT1.VPNT;
    }

  utl_Trace ("utl_SaveNString", UTL_FUN__OUT);

  return (svd_str);
  }
