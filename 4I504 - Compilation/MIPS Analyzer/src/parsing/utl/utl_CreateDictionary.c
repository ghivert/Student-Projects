
/* ###--------------------------------------------------------------### */
/* file		: utl_CreateDictionary.c				*/
/* date		: Arp 19 2004						*/
/* version	: v200							*/
/* author	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <stdlib.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: adddat						*/
/* description	: do nothing						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

static void *adddat (data)

void *data;

  {
  return (data);
  }

/* ###--------------------------------------------------------------### */
/* function	: fredat						*/
/* description	: do nothing						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

static void fredat (data)

void *data;

  {
  }

/* ###--------------------------------------------------------------### */
/* function	: eqldat						*/
/* description	: return 0 if two integers are equal			*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

static int eqldat (d1, d2)

void *d1;
void *d2;

  {
  return ((int) d1 - (int) d2);
  }

/* ###--------------------------------------------------------------### */
/* function	: utl_CreateDictionary					*/
/* description	: create a dictionary					*/
/* called func.	: utl_freuttyp, utl_alloc, eqldat, adddat, fredat	*/
/* ###--------------------------------------------------------------### */

struct utdic *utl_CreateDictionary (size , speed, add_k, fre_k, eql_k,
                                    add_d, fre_d, hash , flag )

unsigned short    size     ;
unsigned short    speed    ;
void           *(*add_k) ();
void            (*fre_k) ();
int             (*eql_k) ();
void           *(*add_d) ();
void            (*fre_d) ();
unsigned int    (*hash ) ();
unsigned int      flag     ;

  {
  unsigned int  i       ;
  struct utdic *pt_dic  = NULL;
  struct utdit *pt_tab  = NULL;
  struct uttyp *pt_typ  = NULL;
  struct uttyp *prv_typ = NULL;

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
	/* ###------------------------------------------------------### */

  utl_Trace ("utl_CreateDictionary", UTL_FUN__IN);

	/* ###------------------------------------------------------### */
	/*   make an allocation for the dictionary			*/
	/* ###------------------------------------------------------### */

  if (UTL_FREDIC == NULL)
    {
    UTL_FREDIC = (struct utdic *)
                  utl_alloc (sizeof (struct utdic) * UTL_BLC__DIC);

    pt_dic = UTL_FREDIC;
    for (i=1 ; i<UTL_BLC__DIC ; i++)
      {
      pt_dic->NEXT = pt_dic + 1;
      pt_dic ++;
      }
    pt_dic->NEXT = NULL;
    }

  pt_dic     = UTL_FREDIC      ;
  UTL_FREDIC = UTL_FREDIC->NEXT;

	/* ###------------------------------------------------------### */
	/*   make an allocation for the dictionary's hash table		*/
	/* ###------------------------------------------------------### */

  prv_typ = NULL      ;
  pt_typ  = UTL_FREDIT;

  while (pt_typ != NULL)
    {
    if (pt_typ->DAT2.UINT == size)
      break;

    prv_typ = pt_typ      ;
    pt_typ  = pt_typ->NEXT;
    }

  if (pt_typ != NULL)
    {
    pt_tab = (struct utdit *) pt_typ->DAT1.VPNT;

    if (prv_typ == NULL)
      UTL_FREDIT    = pt_typ->NEXT;
    else
      prv_typ->NEXT = pt_typ->NEXT;

    utl_freuttyp (pt_typ);
    }
  else
    pt_tab = (struct utdit *) utl_alloc (sizeof (struct utdit) * size);

	/* ###------------------------------------------------------### */
	/*   initialize the dictionary					*/
	/* ###------------------------------------------------------### */

  for (i=0 ; i<size ; i++)
    pt_tab [i].ITEM = NULL;

  if (add_k == NULL) pt_dic->ADD_K = adddat     ; else pt_dic->ADD_K = add_k;
  if (fre_k == NULL) pt_dic->FRE_K = fredat     ; else pt_dic->FRE_K = fre_k;
  if (eql_k == NULL) pt_dic->CMP_K = eqldat     ; else pt_dic->CMP_K = eql_k;
  if (add_d == NULL) pt_dic->ADD_D = adddat     ; else pt_dic->ADD_D = add_d;
  if (fre_d == NULL) pt_dic->FRE_D = fredat     ; else pt_dic->FRE_D = fre_d;
  if (hash  == NULL) pt_dic->HSH_K = utl_hashkey; else pt_dic->HSH_K = hash ;

  pt_dic->NEXT   = NULL            ;
  pt_dic->TABLE  = pt_tab          ;
  pt_dic->FLAG   = flag            ;
  pt_dic->SIZE   = size            ;
  pt_dic->SPEED  = speed           ;
  pt_dic->INIT   = rand () % size  ;
  pt_dic->STATUS = UTL_DIC__SUCCEED;

  utl_Trace ("utl_CreateDictionary", UTL_FUN__OUT);

  return (pt_dic);
  }
