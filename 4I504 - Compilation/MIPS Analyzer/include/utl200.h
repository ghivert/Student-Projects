
/* ###--------------------------------------------------------------### */
/* file		: utl200.h						*/
/* date		: Apr 29 2006						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* contents	: Utility library header				*/
/* ###--------------------------------------------------------------### */

#ifndef UTL_UTLDEF
#define UTL_UTLDEF

	/* ###------------------------------------------------------### */
	/*    defines							*/
	/* ###------------------------------------------------------### */

#define UTL_FUN__IN                           1	/* debug : entring func	*/
#define UTL_FUN__OUT                          2	/* debug : leaving func	*/

#define UTL_BYT__TABLESIZE                  256	/* table of free str.	*/
#define UTL_STR__TABLESIZE                 4096	/* table of      str.	*/
#define UTL_STR__MAXLEN                    4096	/* max string length	*/

#define UTL_STR__NOP                 0x00000001	/* str convert : no	*/
#define UTL_STR__LOWER               0x00000002	/* str convert : lower	*/
#define UTL_STR__UPPER               0x00000004	/* str convert : upper	*/

#define UTL_BLC__BYTE                      4096	/* a block of bytes	*/
#define UTL_BLC__CHN                       1024	/* a block of utchn	*/
#define UTL_BLC__TYP                        256	/* a block of uttyp	*/
#define UTL_BLC__TDC                        256	/* a block of uttdc	*/
#define UTL_BLC__TPD                        256	/* a block of uttpd	*/
#define UTL_BLC__DIC                          1	/* a block of dict	*/

#define UTL_DIC__SMALL                       64	/* small  size dict	*/
#define UTL_DIC__MEDIUM                     256	/* medium size dict	*/
#define UTL_DIC__BIG                       1024	/* big    size dict	*/
#define UTL_DIC__HUGE                      4096	/* huge   size dict	*/

#define UTL_DIC__VERYSLOW                  1024	/* very slow access dic	*/
#define UTL_DIC__SLOW                       128	/*      slow access dic	*/
#define UTL_DIC__FAST                        16	/*      fast access dic	*/

#define UTL_DIC__WRITEONCE           0x00000001	/* no overwriting	*/
#define UTL_DIC__OVERWRITE           0x00000002	/*    overwriting	*/

#define UTL_DIC__SUCCEED             0x00000000	/* access succeed	*/
#define UTL_DIC__FAILED              0x00000001	/* access failed	*/

#define UTL_STC__OFF                          0	/* statistics off	*/
#define UTL_STC__ON                           1	/* statistics on	*/

#define UTL_DAT__FLOT                         1	/* real number		*/
#define UTL_DAT__UINT                         2	/* unsigned integer	*/
#define UTL_DAT__SINT                         3	/* signed   integer	*/
#define UTL_DAT__CHAR                         4	/* character		*/

#define UTL_DLM__PARENTHESIS                  0	/* delimiter : ()	*/
#define UTL_DLM__BRACE                        1	/* delimiter : {}	*/
#define UTL_DLM__BRACKET                      2	/* delimiter : []	*/
#define UTL_DLM__COMPARESIGN                  3	/* delimiter : <>	*/
#define UTL_DLM__OTHERS                       4	/* delimiter : any other*/

#define UTL_CHR__BLK                 0x00000001	/* blank		*/
#define UTL_CHR__SPC                 0x00000002	/* space		*/
#define UTL_CHR__LOW                 0x00000004	/* lower case		*/
#define UTL_CHR__UPP                 0x00000008	/* upper case		*/
#define UTL_CHR__BDG                 0x00000010	/* binary      digit	*/
#define UTL_CHR__ODG                 0x00000020	/* octal       digit	*/
#define UTL_CHR__DDG                 0x00000040	/* decimal     digit	*/
#define UTL_CHR__XDG                 0x00000080	/* hexadecimal digit	*/

#define UTL_TYP__DAT1                0x00000001	/* uttyp field		*/
#define UTL_TYP__DAT2                0x00000002	/* uttyp field		*/

#define UTL_STS__INITIALIZED         0x00000001	/* status : initialized	*/
#define UTL_STS__ERROR               0x00000002	/* status : error	*/

#define UTL_ERR__UNMASKABLE          0x00000003	/* unmaskable error lvl	*/

	/* ###------------------------------------------------------### */
	/*    complex defines						*/
	/* ###------------------------------------------------------### */

#define UTL_CHR__DX     (UTL_CHR__DDG | UTL_CHR__XDG)
#define UTL_CHR__ODX    (UTL_CHR__ODG | UTL_CHR__DX )
#define UTL_CHR__BODX   (UTL_CHR__BDG | UTL_CHR__ODX)

	/* ###------------------------------------------------------### */
	/*    data structures						*/
	/* ###------------------------------------------------------### */

union utdat
  {
  void              *VPNT                     ;	/* any pointer		*/
  float              FLOT                     ;	/* a real number	*/
  unsigned int       UINT                     ;	/* an unsigned integer	*/
  int                SINT                     ;	/* an          integer	*/
  char               CHAR                     ;	/* a           character*/
  unsigned char      UCHR                     ;	/* an unsigned character*/
  };

typedef struct utchn				/* chain		*/
  {
  struct utchn      *NEXT                     ;	/* next element		*/
  union utdat        DATA                     ;	/* data			*/
  }
utl_utchn;

typedef struct uttyp				/* chain		*/
  {
  struct uttyp      *NEXT                     ;	/* next element		*/
  union  utdat       DAT1                     ;	/* data			*/
  union  utdat       DAT2                     ;	/* data			*/
  }
utl_uttyp;

typedef struct uttdc				/* chain		*/
  {
  struct uttdc      *NEXT                     ;	/* next element		*/
  union  utdat       DAT1                     ;	/* data			*/
  union  utdat       DAT2                     ;	/* data			*/
  union  utdat       DAT3                     ;	/* data			*/
  }
utl_uttdc;

typedef struct uttpd				/* chain		*/
  {
  struct uttpd      *NEXT                     ;	/* next element		*/
  union  utdat       DAT1                     ;	/* data			*/
  double             DAT2                     ;	/* data			*/
  }
utl_uttpd;

typedef struct utdic				/* dictionary		*/
  {
  struct utdic      *NEXT                     ;	/* next dictionary	*/
  struct utdit      *TABLE                    ;	/* table of items	*/
  void           *( *ADD_K) ()                ;	/* key  alloc  function	*/
  void            ( *FRE_K) ()                ;	/* key  free   function	*/
  int             ( *CMP_K) ()                ;	/* key  compar function	*/
  void           *( *ADD_D) ()                ;	/* data alloc  function	*/
  void            ( *FRE_D) ()                ;	/* data free   function	*/
  unsigned int    ( *HSH_K) ()                ;	/* key  hash   function	*/
  unsigned short     SIZE                     ;	/* size of item's table	*/
  unsigned short     SPEED                    ;	/* access speed		*/
  unsigned int       INIT                     ;	/* hash code init	*/
  unsigned int       STATUS                   ;	/* status		*/
  unsigned int       FLAG                     ;	/* flags		*/
  }
utl_utdic;

typedef struct utdit				/* table of dic items	*/
  {
  struct uttyp      *ITEM                     ;	/* list of items	*/
  }
utl_utdit;

	/* ###------------------------------------------------------### */
	/*    global variables						*/
	/* ###------------------------------------------------------### */

extern unsigned int    UTL_TRC_LEVEL          ;	/* debug		*/
extern unsigned int    UTL_DBG_LEVEL          ;	/* debug		*/

extern unsigned int    UTL_ERR_LEVEL          ;	/* visible error levels	*/

extern unsigned int    UTL_STR_MODE           ;	/* str conversion mode	*/

extern struct uttyp  **UTL_STRTAB             ;	/*      strings table	*/
extern struct uttyp  **UTL_FREBTAB            ;	/* free byte arrays	*/
extern struct uttyp   *UTL_BYTBLOC            ;

extern struct utchn   *UTL_FRECHN             ;	/* free utchn		*/
extern struct uttyp   *UTL_FRETYP             ;	/* free uttyp		*/
extern struct uttdc   *UTL_FRETDC             ;	/* free uttdc		*/
extern struct uttpd   *UTL_FRETPD             ;	/* free uttpd		*/

extern struct utdic   *UTL_FREDIC             ;	/* free dictionaries	*/
extern struct uttyp   *UTL_FREDIT             ;	/* free dict tables	*/

extern unsigned int    UTL_MEMSIZE            ;	/* total memallocated	*/
extern unsigned int    UTL_STATUS             ;	/* status		*/

extern unsigned int    UTL_IDX_DELIMITER      ;

extern unsigned char   UTL_DLM_LEFT  [  5]    ;
extern unsigned char   UTL_DLM_RIGHT [  5]    ;

extern unsigned int    UTL_CHR_TYPE  [256]    ;
extern unsigned int    UTL_CHR_VALUE [256]    ;

	/* ###------------------------------------------------------### */
	/*    functions							*/
	/* ###------------------------------------------------------### */

extern void          *utl_alloc                  ();	/* mem alloc	*/
extern void           utl_free                   ();	/* mem free	*/

extern unsigned int   utl_error                  ();	/* error mesg	*/

extern void           utl_hash2                  ();	/* hash func	*/
extern unsigned int   utl_hashstr                ();	/* hash func	*/
extern unsigned int   utl_hashkey                ();	/* hash func	*/
extern unsigned int   utl_hshutchn               ();	/* hash func	*/

extern int            utl_cmpsint                ();	/* compare	*/
extern int            utl_cmpuint                ();	/* compare	*/

//extern struct utchn  *utl_addutchn               ();	/* add elm	*/
extern struct utchn  *utl_addutchn               (struct utchn *list,union  utdat  data);	/* add elm	*/
extern struct utchn  *utl_adqutchn               ();	/* add elm	*/
extern struct utchn  *utl_catutchn               ();	/* catenate	*/
extern struct utchn  *utl_ccputchn               ();	/* cond  copy	*/
extern struct utchn  *utl_cpyutchn               ();	/* copy  list	*/
extern int            utl_eqlutchn               ();	/* equal	*/
extern struct utchn  *utl_freutchn               ();	/* free elm	*/
extern struct utchn  *utl_frlutchn               ();	/* free list	*/
extern unsigned int   utl_fprutchn               ();	/* file print	*/
extern unsigned int   utl_lenutchn               ();	/* list length	*/
extern struct utchn  *utl_mvqutchn               ();	/* move queue	*/
//extern struct utchn  *utl_revutchn               ();	/* reverse list	*/
extern struct utchn  *utl_revutchn               (struct utchn *pt_chn);	/* reverse list	*/
extern struct utchn  *utl_rmvutchn               ();	/* remove  elm	*/
extern struct utchn  *utl_splutchn               ();	/* split   list	*/
extern struct utchn  *utl_insutchn               ();	/* insert  elm	*/
extern struct utchn  *utl_srtutchn               ();	/* sort    list	*/
extern struct utchn  *utl_qstutchn               ();	/* sort    list	*/

extern struct uttyp  *utl_adduttyp               ();	/* add elm	*/
extern struct uttyp  *utl_adquttyp               ();	/* add elm	*/
extern struct uttyp  *utl_catuttyp               ();	/* catenate	*/
extern struct uttyp  *utl_ccputtyp               ();	/* cond copy	*/
extern struct uttyp  *utl_cpyuttyp               ();	/* copy  list	*/
extern int            utl_eqluttyp               ();	/* equal	*/
extern struct uttyp  *utl_freuttyp               ();	/* free elm	*/
extern unsigned int   utl_fpruttyp               ();	/* file print	*/
extern struct uttyp  *utl_frluttyp               ();	/* free list	*/
extern unsigned int   utl_lenuttyp               ();	/* list length	*/
extern struct uttyp  *utl_mvquttyp               ();	/* move queue	*/
extern struct uttyp  *utl_revuttyp               ();	/* reverse list	*/
extern struct uttyp  *utl_rmvuttyp               ();	/* remove elm	*/
extern struct uttyp  *utl_spluttyp               ();	/* split list	*/
extern struct uttyp  *utl_srtuttyp               ();	/* sort    list	*/

extern struct utchn  *utl_typ2chn                ();	/* copy    list	*/
extern struct uttyp  *utl_chn2typ                ();	/* copy    list	*/

extern struct uttdc  *utl_adduttdc               ();	/* add elm	*/
extern struct uttdc  *utl_catuttdc               ();	/* catenate	*/
extern struct uttdc  *utl_cpyuttdc               ();	/* copy  list	*/
extern struct uttdc  *utl_freuttdc               ();	/* free one str	*/
extern struct uttdc  *utl_frluttdc               ();	/* free list	*/
extern struct uttdc  *utl_revuttdc               ();	/* reverse list	*/

extern struct uttpd  *utl_adduttpd               ();	/* add elm	*/
extern struct uttpd  *utl_catuttpd               ();	/* catenate	*/
extern struct uttpd  *utl_freuttpd               ();	/* free elm	*/
extern struct uttpd  *utl_frluttpd               ();	/* free list	*/
extern struct uttpd  *utl_revuttpd               ();	/* reverse list	*/
extern unsigned int   utl_lenuttpd               ();	/* list length	*/

extern char          *utl_alcbyt                 ();
extern void           utl_frebyt                 ();

extern unsigned int   utl_isbdigit               ();
extern unsigned int   utl_isodigit               ();
extern unsigned int   utl_isddigit               ();
extern unsigned int   utl_isxdigit               ();

extern void           utl_Initialize             ();

extern FILE          *utl_Open                   ();
extern void           utl_Trace                  ();
extern void           utl_SetTraceLevel          ();

extern void           utl_ClearError             ();
extern void           utl_SetErrorLevel          ();
extern unsigned int   utl_GetErrorLevel          ();

extern unsigned int   utl_GetStringMode          ();
extern void           utl_SetStringMode          ();

extern char          *utl_DelString              ();
extern char          *utl_SaveString             ();
extern char          *utl_SaveNString            ();
extern char          *utl_GetString              ();

extern char          *utl_DelStringWithMode      ();
extern char          *utl_SaveStringWithMode     ();
extern char          *utl_SaveNStringWithMode    ();
extern char          *utl_GetStringWithMode      ();

extern char          *utl_PrettyString           ();

extern char          *utl_GetHeaderString        ();
extern char          *utl_GetTailerString        ();
extern char          *utl_GetRHeaderString       ();

extern int            utl_GetCharIndexInString   ();
extern struct utchn  *utl_SplitString            ();
extern void           utl_CutString              ();

extern char           utl_SplitFlatFormat        ();
extern int            utl_SplitFormat            ();
extern int            utl_IsFormatLegal          ();

extern unsigned int   utl_SetIndexDelimiter      ();
extern char          *utl_CatNameIndex           ();
extern int            utl_GetNameIndex           ();
extern struct utchn  *utl_GetSlicedNameList      ();

extern char          *utl_GetName                ();
extern char          *utl_GetVhdlName            ();
extern char          *utl_GetVhdlIndexedName     ();
extern char          *utl_GetVhdlSlicedName      ();
extern char          *utl_GetNameWithIndex       ();

extern unsigned int   utl_GetMemSize             ();

extern struct utdic  *utl_CreateSimpleDic        ();
extern struct utdic  *utl_CreateDictionary       ();
extern void           utl_AddDicItem             ();
//extern void          *utl_GetDicItem             ();
extern void          *utl_GetDicItem             (struct utdic *pt_dic,void         *key);
extern void          *utl_DelDicItem             ();
extern void           utl_DelAllDicItems         ();
extern struct utdic  *utl_DelDictionary          ();
extern struct utdic  *utl_SetDicMode             ();
extern unsigned int   utl_GetDicItemStatus       ();
//extern unsigned int   utl_GetDicStatus           ();
extern unsigned int   utl_GetDicStatus           (struct utdic *pt_dic );

extern unsigned int   utl_GetIntegerSize         ();
extern int            utl_IsFloatInteger         ();
extern int            utl_IsFloatNatural         ();

extern unsigned int   utl_CharToInt              ();
extern char           utl_CharToAscii            ();
extern unsigned int   utl_BinToInt               ();
extern unsigned int   utl_OctToInt               ();
extern unsigned int   utl_HexToInt               ();

#endif
