
/* ###--------------------------------------------------------------### */
/* file		: asm_addmemtab.c					*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_addmemtab						*/
/* description	: create a new memory table				*/
/* called func.	: utl_alloc, utl_adduttyp				*/
/* ###--------------------------------------------------------------### */

struct uttyp *asm_addmemtab (mem_tab, addr)

struct uttyp *mem_tab;
unsigned int  addr   ;

  {
  struct uttyp  *pt_typ  = NULL;
  struct uttyp  *prv_typ = NULL;
  struct uttyp  *pt_tab  = NULL;
  unsigned char *pt_dat  = NULL;
  unsigned char *pt_flg  = NULL;
  unsigned int   i       ;

	/* ###------------------------------------------------------### */
	/*   align the address						*/
	/* ###------------------------------------------------------### */

  addr = addr & (~ (ASM_BLC__MEMORY - 1));

	/* ###------------------------------------------------------### */
	/*   the memory tables are organized in ascending address	*/
	/* range. Search the position where the new table should be	*/
	/* inserted.							*/
	/* ###------------------------------------------------------### */

  pt_typ = mem_tab;
  while (pt_typ != NULL)
    {
    if (addr < pt_typ->DAT1.UINT)
      break;

    prv_typ = pt_typ      ;
    pt_typ  = pt_typ->NEXT;
    }

	/* ###------------------------------------------------------### */
	/*   create and initialize the new table			*/
	/* ###------------------------------------------------------### */

  pt_dat = (unsigned char *)
            utl_alloc (sizeof (unsigned char) * ASM_BLC__MEMORY);
  pt_flg = (unsigned char *)
            utl_alloc (sizeof (unsigned char) * ASM_BLC__MEMORY);

  for (i=0 ; i<ASM_BLC__MEMORY ; i++)
    {
    pt_dat [i] = 0;
    pt_flg [i] = 0;
    }

  pt_tab = utl_adduttyp (NULL  , pt_dat, pt_flg);
  pt_typ = utl_adduttyp (pt_typ, addr  , pt_tab);

  if (prv_typ == NULL)
    mem_tab       = pt_typ;
  else
    prv_typ->NEXT = pt_typ;

  return (mem_tab);
  }
