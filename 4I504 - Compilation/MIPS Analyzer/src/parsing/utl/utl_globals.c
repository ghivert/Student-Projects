
/* ###--------------------------------------------------------------### */
/* file		: utl_globals.c						*/
/* date		: Apr 29 2006						*/
/* version	: v102							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* description	: global variables					*/
/* ###--------------------------------------------------------------### */

unsigned int    UTL_TRC_LEVEL     =  0                ;	/* debug	*/
unsigned int    UTL_DBG_LEVEL     =  0                ;	/* debug	*/

unsigned int    UTL_ERR_LEVEL     =  0xffffffff       ;	/* visible lvls	*/

unsigned int    UTL_STR_MODE      =  UTL_STR__LOWER   ;	/* lower case	*/

struct uttyp  **UTL_STRTAB        =  NULL             ;	/*      str tab	*/
struct uttyp  **UTL_FREBTAB       =  NULL             ;	/* free str tab	*/
struct uttyp   *UTL_BYTBLOC       =  NULL             ;

struct utchn   *UTL_FRECHN        =  NULL             ;	/* free utchn	*/
struct uttyp   *UTL_FRETYP        =  NULL             ;	/* free uttyp	*/
struct uttdc   *UTL_FRETDC        =  NULL             ;	/* free uttdc	*/
struct uttpd   *UTL_FRETPD        =  NULL             ;	/* free uttpd	*/

struct utdic   *UTL_FREDIC        =  NULL             ;	/* free dict	*/
struct uttyp   *UTL_FREDIT        =  NULL             ;	/* free dict tab*/

unsigned int    UTL_IDX_DELIMITER = UTL_DLM__PARENTHESIS;

unsigned char   UTL_DLM_LEFT  [  5]                     ;
unsigned char   UTL_DLM_RIGHT [  5]                     ;

unsigned int    UTL_CHR_TYPE  [256]                     ;
unsigned int    UTL_CHR_VALUE [256]                     ;

unsigned int    UTL_MEMSIZE       =  0                ;	/* mem alloc	*/
unsigned int    UTL_STATUS        =  0                ;	/* status	*/
