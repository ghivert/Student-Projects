
/* ###--------------------------------------------------------------### */
/* file		: asm_SetMemory.c					*/
/* date		: Mar  2 2009						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H
#include ASM_H

/* ###--------------------------------------------------------------### */
/* function	: asm_SetMemory						*/
/* description	: set the memory content				*/
/* called func.	: asm_addmemtab, asm_fndmemtab				*/
/* ###--------------------------------------------------------------### */

struct uttyp *asm_SetMemory (mem_tab, addr, pt_data)

struct uttyp *mem_tab;
unsigned int  addr   ;
struct utchn *pt_data;

  {
  struct uttyp  *pt_mem  = NULL;
  unsigned int   offset  = 0   ;
  struct uttyp  *pt_tab  = NULL;
  unsigned char *pt_dat  = NULL;
  unsigned char *pt_flg  = NULL;

  while (pt_data != NULL)
    {
	/* ###------------------------------------------------------### */
	/*   find the memory table corresponding to the current address.*/
	/* If the table does not exist create it.			*/
	/* ###------------------------------------------------------### */

    pt_mem  = asm_fndmemtab (mem_tab, addr);
    if (pt_mem == NULL)
      {
      mem_tab = asm_addmemtab (mem_tab, addr);
      pt_mem  = asm_fndmemtab (mem_tab, addr);
      }
      
	/* ###------------------------------------------------------### */
	/*   fill the memory table with the data			*/
	/* ###------------------------------------------------------### */

    offset =                   addr % ASM_BLC__MEMORY;

    pt_tab = (struct uttyp  *) pt_mem->DAT2.VPNT     ;
    pt_dat = (unsigned char *) pt_tab->DAT1.VPNT     ;
    pt_flg = (unsigned char *) pt_tab->DAT2.VPNT     ;

    while ((pt_data != NULL) && (offset < ASM_BLC__MEMORY))
      {
      pt_dat [offset] = pt_data->DATA.UCHR;
      pt_flg [offset] = 1                 ;

      offset  ++             ;
      addr    ++             ;
      pt_data = pt_data->NEXT;
      }
    }
  
  return (mem_tab);
  }
