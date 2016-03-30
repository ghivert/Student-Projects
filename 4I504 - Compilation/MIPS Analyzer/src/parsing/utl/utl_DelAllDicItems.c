
/* ###--------------------------------------------------------------### */
/* file		: utl_DelAllDicItems.c					*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_DelAllDicItems					*/
/* description	: delete all the items of a dictionary			*/
/* called func.	: utl_frluttyp						*/
/* ###--------------------------------------------------------------### */

void utl_DelAllDicItems (pt_dic)

struct utdic *pt_dic;

  {
  unsigned int  idx     ;
  struct utdit *pt_tab  = NULL;
  struct uttyp *pt_typ  = NULL;

	/* ###------------------------------------------------------### */
	/*   this function is used to delete all the items of a		*/
	/* dictionary.							*/
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
	/*   For each entry of the hash table, the list of items is	*/
	/* scanned. The data and the key are removed from the item.	*/
	/* Then, the list of items is released.				*/
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_DelAllDicItems", UTL_FUN__IN);

  if (pt_dic != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   for each entry of the has htable ...			*/
	/* ###------------------------------------------------------### */

    pt_tab = pt_dic->TABLE;

    for (idx=0 ; idx<pt_dic->SIZE ; idx++)
      {
	/* ###------------------------------------------------------### */
	/*   scan the list of items and remove the data. Then, remove	*/
	/* the list of items						*/
	/* ###------------------------------------------------------### */

      pt_typ = pt_tab [idx].ITEM;

      if (pt_typ != NULL)
        {
        while (pt_typ != NULL)
          {
          pt_dic->FRE_K (pt_typ->DAT1.VPNT);
          pt_dic->FRE_D (pt_typ->DAT2.VPNT);

          pt_typ = pt_typ->NEXT;
          }

        utl_frluttyp (pt_tab [idx].ITEM);
        pt_tab [idx].ITEM = NULL;
        }

      }
    pt_dic->STATUS = UTL_DIC__SUCCEED;

    }

  utl_Trace ("utl_DelAllDicItems", UTL_FUN__OUT);
  }
