
/* ###--------------------------------------------------------------### */
/* file		: utl_AddDicItem.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_AddDicItem					*/
/* description	: add a new item to a dictionary			*/
/* called func.	: utl_error, utl_adduttyp				*/
/* ###--------------------------------------------------------------### */

void utl_AddDicItem (pt_dic, key, data)

struct utdic *pt_dic;
void         *key   ;
void         *data  ;

  {
  unsigned int   idx      ;
  int          (*cmp_k) ();
  struct utdit  *pt_tab   = NULL;
  struct uttyp  *pt_typ   = NULL;

	/* ###------------------------------------------------------### */
	/*   this function is used to add a new item into a dictionary.	*/
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
	/* is scanned. If the key is not found a new item is created on	*/
	/* the top of the list. It the key is found and if overwriting	*/
	/* is allowd, the data is updated. Otherwise an error is	*/
	/* generated.							*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_AddDicItem", UTL_FUN__IN);

  if (pt_dic != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   hash the key and find the hash table's entry		*/
	/* ###------------------------------------------------------### */

    cmp_k   = pt_dic->CMP_K;
    pt_tab  = pt_dic->TABLE;

    idx     = pt_dic->HSH_K (key, pt_dic->INIT) % pt_dic->SIZE;

	/* ###------------------------------------------------------### */
	/*   scan the list of items					*/
	/* ###------------------------------------------------------### */

    pt_typ = pt_tab [idx].ITEM;

    while (pt_typ != NULL)
      {
      if ((*cmp_k) (pt_typ->DAT1.VPNT, key) == 0)
        break; 
      pt_typ = pt_typ->NEXT;
      }

	/* ###------------------------------------------------------### */
	/*   an error is detected if the item exists and overwriting is	*/
	/* not allowed.							*/
	/* ###------------------------------------------------------### */

    if ((pt_typ != NULL) && (pt_dic->FLAG & UTL_DIC__OVERWRITE) == 0)
      utl_error (3, "utl_AddDicItem", NULL, 0);
    else
      {
      if (pt_typ == NULL)
        {
        key               = pt_dic->ADD_K (key                         );
        pt_typ            = utl_adduttyp  (pt_tab [idx].ITEM, key, NULL);
        pt_tab [idx].ITEM = pt_typ;
        }
      else
        pt_dic->FRE_D (pt_typ->DAT2.VPNT);

      pt_typ->DAT2.VPNT = pt_dic->ADD_D (data);

      }

    }

  utl_Trace ("utl_AddDicItem", UTL_FUN__OUT);
  }
