
/* ###--------------------------------------------------------------### */
/* file		: utl_alcbyt.c						*/
/* date		: Apr 19 2004						*/
/* version	: v101							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdlib.h>
#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_alcbyt						*/
/* description	: make memory allocation for an array of bytes		*/
/* called func.	: utl_alloc , utl_adduttyp, utl_freuttyp, utl_frebyt	*/
/* ###--------------------------------------------------------------### */

char *utl_alcbyt (size)

unsigned int size;

  {
  unsigned int   max_size;
  char          *pt_blc  ;
  struct uttyp  *prv_typ = NULL;
  struct uttyp  *pt_typ  = NULL;
  char          *pt_byt  ;
  unsigned int   i       ;

	/* ###------------------------------------------------------### */
	/*   This function makes a memory allocation to store an 'array	*/
	/* of bytes'.							*/
	/*								*/
	/*   A table is used to save the pointers of available spaces.	*/
	/* Each entry of the table saves the pointers for a given size	*/
	/* (modulo the size of the table).				*/
	/*								*/
	/*   When an allocation is requested, the corresponding table's	*/
	/* entry is checked. If the entry is not empty, the location,	*/
	/* is removed from the table and returned.			*/
	/*								*/
	/*   If the table's entry is empty, the 'free bytes block' is	*/
	/* splited to created the required storage size.		*/
	/*								*/
	/*   If there is not enough place in the 'free bytes block',	*/
	/* the 'free bytes block' is saved in the table and new block	*/
	/* is allocated.						*/
	/* ###------------------------------------------------------### */

	/* ###------------------------------------------------------### */
	/*   initialize the table of free 'byte arrays'			*/
	/* ###------------------------------------------------------### */

  if (UTL_FREBTAB == NULL)
    {
    UTL_FREBTAB = (struct uttyp **)
                  utl_alloc (sizeof (struct uttyp *) * UTL_BYT__TABLESIZE);

    for (i=0 ; i<UTL_BYT__TABLESIZE ; i++)
      UTL_FREBTAB [i] = NULL;
    }

	/* ###------------------------------------------------------### */
	/*   check the entry corresponding to the required size		*/
	/* ###------------------------------------------------------### */

  prv_typ = NULL;
  pt_typ  = UTL_FREBTAB [size % UTL_BYT__TABLESIZE];

  while (pt_typ != NULL)
    {
    if (pt_typ->DAT2.UINT == size)
      {
      if (prv_typ == NULL)
        UTL_FREBTAB [size % UTL_BYT__TABLESIZE] = pt_typ->NEXT;
      else
        prv_typ->NEXT = pt_typ->NEXT;
      break;
      }

    prv_typ = pt_typ      ;
    pt_typ  = pt_typ->NEXT;
    }

	/* ###------------------------------------------------------### */
	/*   if an space with the given size has been found return the	*/
	/* pointer							*/
	/* ###------------------------------------------------------### */

  if (pt_typ != NULL)
    {
    pt_byt = (char *) pt_typ->DAT1.VPNT;
    utl_freuttyp (pt_typ);
    }
  else
    {
	/* ###------------------------------------------------------### */
	/*   if no available space with the given size has been found,	*/
	/* make a new allocation					*/
	/* ###------------------------------------------------------### */

    if ((UTL_BYTBLOC != NULL) && (UTL_BYTBLOC->DAT2.UINT < size))
      {
      utl_frebyt   ((char *) UTL_BYTBLOC->DAT1.VPNT, UTL_BYTBLOC->DAT2.UINT);
      UTL_BYTBLOC =          utl_freuttyp (UTL_BYTBLOC);
      }

    if (UTL_BYTBLOC == NULL)
      {
      max_size = UTL_BLC__BYTE;
      if (size > max_size)
        max_size = size;

      pt_blc      = (char *) utl_alloc    (sizeof (char) * max_size);
      UTL_BYTBLOC =          utl_adduttyp (NULL, pt_blc,   max_size);
      }

	/* ###------------------------------------------------------### */
	/*   fatal error, if an entire page is not enough for the	*/
	/* required space.						*/
	/* ###------------------------------------------------------### */

    pt_byt                  =  (char *) UTL_BYTBLOC->DAT1.VPNT; 
    UTL_BYTBLOC->DAT1.VPNT  = ((char *) UTL_BYTBLOC->DAT1.VPNT) + size;
    UTL_BYTBLOC->DAT2.UINT -=                                     size;
    }

  return (pt_byt);
  }
