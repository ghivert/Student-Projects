
/* ###--------------------------------------------------------------### */
/* file		: asm_fndmemtab.c					*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_fndmemtab						*/
/* description	: find the memory table corresponding to an address	*/
/*		  return NULL if the table does not exist		*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

struct uttyp *asm_fndmemtab (mem_tab, addr)

struct uttyp *mem_tab;
unsigned int  addr   ;

  {
	/* ###------------------------------------------------------### */
	/*   align the address						*/
	/* ###------------------------------------------------------### */

  addr = addr & (~ (ASM_BLC__MEMORY - 1));

	/* ###------------------------------------------------------### */
	/*   search the memory table					*/
	/* ###------------------------------------------------------### */

  while (mem_tab != NULL)
    {
    if (addr == mem_tab->DAT1.UINT)
      break;
    mem_tab = mem_tab->NEXT;
    }

  return (mem_tab);
  }
