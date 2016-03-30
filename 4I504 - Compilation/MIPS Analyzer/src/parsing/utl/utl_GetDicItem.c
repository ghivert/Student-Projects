
/* ###--------------------------------------------------------------### */
/* file		: utl_GetDicItem.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_GetDicItem					*/
/* description	: return an item saved in a dictionary			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void *utl_GetDicItem (pt_dic, key)

struct utdic *pt_dic;
void         *key   ;

  {
  unsigned int   idx      ;
  int          (*cmp_k) ();
  struct utdit  *pt_tab   = NULL;
  struct uttyp  *pt_typ   = NULL;
  void          *pt_dat   = NULL;

	/* ###------------------------------------------------------### */
	/*   this function is used to extract a data from a dictionary.	*/
	/*								*/
	/*   A dictionary is a hash table. The size of table is fixed.	*/
	/* Each entry of the table contains a list of items. Each item	*/
	/* is identified by a key.					*/
	/*								*/
	/*   Two functions are used to create and to destroy a data.	*/
	/*   Two functions are used to create and to destroy a key.	*/
	/*   A   function  is  used to hash the key.			*/
	/*   A   function  is  used to compare keys.			*/
	/*								*/
	/*   To access an item the key is hashed to obtain an index to	*/
	/* the hash table. The items that have the same hash code are	*/
	/* organized as a list and stored in the same entry of the hash	*/
	/* table.							*/
	/*								*/
	/*   The list of items pointed from the entry of the hash table	*/
	/* is scanned. If the key is found the corresponding data is	*/
	/* returned. Otherwise a NULL is returned.			*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_GetDicItem", UTL_FUN__IN);

  if (pt_dic != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   hash the key to get an index to the hash table		*/
	/* ###------------------------------------------------------### */

    cmp_k  = pt_dic->CMP_K;
    pt_tab = pt_dic->TABLE;

    idx    = pt_dic->HSH_K (key, pt_dic->INIT) % pt_dic->SIZE;

	/* ###------------------------------------------------------### */
	/*   scan the list of item searching the key. Return the	*/
	/* corresponding data if found.					*/
	/* ###------------------------------------------------------### */

    pt_dic->STATUS = UTL_DIC__FAILED  ;
    pt_typ         = pt_tab [idx].ITEM;

    while (pt_typ != NULL)
      {
      if ((*cmp_k) (pt_typ->DAT1.VPNT, key) == 0)
        {
        pt_dat         = pt_typ->DAT2.VPNT;
        pt_dic->STATUS = UTL_DIC__SUCCEED ;
        break; 
        }
      pt_typ = pt_typ->NEXT;
      }
    }

  utl_Trace ("utl_GetDicItem", UTL_FUN__OUT);

  return (pt_dat);
  }
