
/* ###--------------------------------------------------------------### */
/* file		: utl_DelString.c					*/
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
/* function	: utl_DelString						*/
/* description	: remove a string from the set of stored strings	*/
/* called func.	: utl_Trace, utl_hash2, utl_frebyt, utl_freuttyp,	*/
/*		  utl_alloc						*/
/* ###--------------------------------------------------------------### */

char *utl_DelString (str)

char *str;

  {
  char          buf [UTL_STR__MAXLEN] ;
  char         *svd_str               = NULL;
  struct uttyp *pt_typ                = NULL;
  struct uttyp *prv_typ               = NULL;
  unsigned int  hsh_cod1              ;
  unsigned int  hsh_cod2              ;
  unsigned int  tab_idx               ;
  unsigned int  size                  = 0   ;
  int           i                     ;

	/* ###------------------------------------------------------### */
	/*   This function is used to remove a string from the memory.	*/
	/* The function returns the location where the string has been	*/
	/* found. If the string has not been found, it returns NULL.	*/
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
	/* scanning. If the string is found in the hash table, its is	*/
	/* removed from the hash table and its location is returned.	*/
	/* Otherwise, the function returns NULL.			*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_DelString", UTL_FUN__IN);

	/* ###------------------------------------------------------### */
	/*   initialize the hash table if it does not exists		*/
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
      while ((buf [size] = str [size]) != '\0')
        {
        if ((buf [size] <= 'z') && (buf [size] >= 'a')) 
          buf [size] = buf [size] - 'a' + 'A';

        size ++;
        }
      }

    if ((UTL_STR_MODE & UTL_STR__LOWER) != 0)
      {
      while ((buf [size] = str [size]) != '\0')
        {
        if ((buf [size] <= 'Z') && (buf [size] >= 'A')) 
          buf [size] = buf [size] - 'A' + 'a';

        size ++;
        }
      }

    if ((UTL_STR_MODE & UTL_STR__NOP  ) != 0)
      {
      while ((buf [size] = str [size]) != '\0')
        size ++;
      }

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

      prv_typ = pt_typ      ;
      pt_typ  = pt_typ->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   if the string has been found, remove it from the hash	*/
	/* table							*/
	/* ###------------------------------------------------------### */

    if (pt_typ != NULL)
      {
      svd_str =  (char *) pt_typ->DAT1.VPNT;
      utl_frebyt (svd_str, size);

      if (prv_typ == NULL)
        UTL_STRTAB [tab_idx] = pt_typ->NEXT;
      else
        prv_typ->NEXT        = pt_typ->NEXT;

      utl_freuttyp (pt_typ);
      }
    }

  utl_Trace ("utl_DelString", UTL_FUN__OUT);

  return (svd_str);
  }
