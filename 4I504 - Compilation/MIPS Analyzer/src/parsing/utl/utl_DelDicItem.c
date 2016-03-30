
/* ###--------------------------------------------------------------### */
/* file		: utl_DelDicItem.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_DelDicItem					*/
/* description	: delete an item saved in a dictionary			*/
/* called func.	: utl_freuttyp						*/
/* ###--------------------------------------------------------------### */

void *utl_DelDicItem (pt_dic, key)

struct utdic *pt_dic;
void         *key   ;

  {
  unsigned int   idx      ;
  int          (*cmp_k) ();
  struct utdit  *pt_tab   = NULL;
  struct uttyp  *pt_typ   = NULL;
  struct uttyp  *prv_typ  = NULL;

	/* ###------------------------------------------------------### */
	/*   this function is used to delete an item from a dictionary.	*/
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
	/*   The list of items pointed by the entry of the hash table	*/
	/* is scanned. If the key is found the corresponding item is	*/
	/* removed from the dictionary and a non NULL value is		*/
	/* returned. Otherwise a NULL is returned.			*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_DelDicItem", UTL_FUN__IN);

  if (pt_dic != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   hash the key to get an index to the hash table		*/
	/* ###------------------------------------------------------### */

    cmp_k   = pt_dic->CMP_K;
    pt_tab  = pt_dic->TABLE;

    idx     = pt_dic->HSH_K (key, pt_dic->INIT) % pt_dic->SIZE;

	/* ###------------------------------------------------------### */
	/*   scan the list of item searching the key			*/
	/* ###------------------------------------------------------### */

    prv_typ = NULL             ;
    pt_typ  = pt_tab [idx].ITEM;

    while (pt_typ != NULL)
      {
      if ((*cmp_k) (pt_typ->DAT1.VPNT, key) == 0)
        break; 

      prv_typ = pt_typ;
      pt_typ  = pt_typ->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   remove the item if found					*/
	/* ###------------------------------------------------------### */

    pt_dic->STATUS = UTL_DIC__FAILED;

    if (pt_typ != NULL)
      {
      if (prv_typ != NULL)
        prv_typ->NEXT     = pt_typ->NEXT;
      else
        pt_tab [idx].ITEM = pt_typ->NEXT;

      pt_dic->FRE_K (pt_typ->DAT1.VPNT);
      pt_dic->FRE_D (pt_typ->DAT2.VPNT);

      utl_freuttyp (pt_typ);
      pt_dic->STATUS = UTL_DIC__SUCCEED;
      }
    }

  utl_Trace ("utl_DelDicItem", UTL_FUN__OUT);

  return (pt_typ);
  }
