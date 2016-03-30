
/* ###--------------------------------------------------------------### */
/* file		: asm200.h						*/
/* date		: Jun 21 2010						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

#ifndef ASM_ASMDEF
#define ASM_ASMDEF

	/* ###------------------------------------------------------### */
	/*    defines							*/
	/* ###------------------------------------------------------### */

#define ASM_BLC__MEMORY                    4096	/* memory block		*/
#define ASM_BLC__OBJ                          1	/* memory block		*/
#define ASM_BLC__OSC                          8	/* memory block		*/
#define ASM_BLC__ISC                          8	/* memory block		*/
#define ASM_BLC__ISS                          8	/* memory block		*/

#define ASM_ERR__MAX                         30	/* max number of errors	*/

#define ASM_LDP__BUILD                        1	/* ldscript  pass	*/
#define ASM_LDP__SYMBOLS                      2	/* ldscript  pass	*/

#define ASM_ASP__SIZEOF                       1	/* assembler pass	*/
#define ASM_ASP__LABELS                       2	/* assembler pass	*/
#define ASM_ASP__SYMBOLS                      3	/* assembler pass	*/
#define ASM_ASP__CODE                         4	/* assembler pass	*/

#define ASM_SET__REORDER             0x00000001	/* set : reorder	*/
#define ASM_SET__NOREORDER           0x00000002	/* set : noreorder	*/

#define ASM_ISS__LOCFIXED            0x00000001	/* location fixed	*/

#define ASM_FIG__ERROR               0x00000002	/* error		*/

#define ASM_STS__INITIALIZED         0x00000001	/* initialized		*/
#define ASM_STS__ERROR               0x00000002	/* error		*/

#define ASM_ERR__UNMASKABLE          0x00000003	/* unmaskable error lvl	*/

#define ASM_ARC__MIPS1               0x00000001	/* archi mips r3000	*/
#define ASM_ARC__MIPS32              0x00000002	/* archi mips 32	*/

#define ASM_MEM__LITTLE              0x00000001	/* little endian	*/
#define ASM_MEM__BIG                 0x00000002	/* big    endian	*/

	/* ### ---------------------------------------------------- ### */
	/*    expression operators in assembly				*/
	/* ### ---------------------------------------------------- ### */

#define ASM_OPR__PLUS                         0	/* add			*/
#define ASM_OPR__MINUS                        1	/* subtract		*/
#define ASM_OPR__SHL                          2	/* shift left		*/
#define ASM_OPR__SHR                          3	/* shift right		*/
#define ASM_OPR__OR                           4	/* bitwise or		*/
#define ASM_OPR__AND                          5	/* bitwise and		*/
#define ASM_OPR__XOR                          6	/* bitwise exclusive or	*/
#define ASM_OPR__MUL                          7	/* integer multiply	*/
#define ASM_OPR__DIV                          8	/* integer divide	*/

	/* ### ---------------------------------------------------- ### */
	/*    Mips instruction set:					*/
	/*								*/
	/*     Opcods in   lower case         are Mips    instructions	*/
	/*     Opcods in   lower case and *   are Mips  1 instructions	*/
	/*     Opcods in   lower case and %   are Mips 32 instructions	*/
	/*     Opcods in   upper case         are application specific	*/
	/*								*/
	/*     primary opcod (31 downto 26) :				*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 |speci|bcond|  j  | jal | beq | bne |blez |bgtz |	*/
	/*     1 |addi |addiu|slti |sltiu|andi | ori |xori | lui |	*/
	/*     2 |cop0 |  +  |cop2 |spec2|  +  |  +  |  +  |  +  |	*/
	/*     3 |     |     |     |     |  +  |  +  |     |  +  |	*/
	/*     4 | lb  | lh  | lwl | lw  | lbu | lhu | lwr |     |	*/
	/*     5 | sb  | sh  |  +  | sw  |     |     |  +  |  +  |	*/
	/*     6 | ll  |  +  |  +  |pref |     |  +  |  +  |     |	*/
	/*     7 | sc  |  +  |  +  |  +  |     |  +  |  +  |     |	*/
	/*								*/
	/*								*/
	/*     special opcod extension (5 downto 0) :			*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 | *** |  +  | srl | sra |sllv |     |srlv |srav |	*/
	/*     1 | jr  |jalr |  +  |  +  |sysca|break|     |sync |	*/
	/*     2 |mfhi |mthi |mflo |mtlo |     |     |     |     |	*/
	/*     3 |mult |multu| div |divu |     |     |     |     |	*/
	/*     4 | add |addu | sub |subu | and | or  | xor | nor |	*/
	/*     5 |     |     | slt |sltu |     |     |     |     |	*/
	/*     6 |  +  |  +  |  +  |  +  |  +  |     |  +  |     |	*/
	/*     7 |     |     |     |     |  +  |  +  |  +  |  +  |	*/
	/*  								*/
	/*     *** : Specific rt, rd, and sham make the distinction	*/
	/*           between sll					*/
	/*                  nop : sll r0, r0, 0				*/
	/*                  ehb : sll r0, r0, 3				*/
	/*								*/
	/*     special2 opcod extension (5 downto 0) :			*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 |madd |maddu| mul |     |msub |msubu|     |     |	*/
	/*     1 |     |     |     |     |     |     |     |     |	*/
	/*     2 |     |     |     |     |     |     |     |     |	*/
	/*     3 |     |     |     |     |     |     |     |     |	*/
	/*     4 | clz | clo |     |     |     |     |     |     |	*/
	/*     5 |     |     |     |     |     |     |     |     |	*/
	/*     6 |     |     |     |     |     |     |           |	*/
	/*     7 |     |     |     |     |     |     |     |  +  |	*/
	/*								*/
	/*     bcond opcod extension (20 downto 16) :			*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 |bltz |bgez |  +  |  +  |     |     |     |     |	*/
	/*     1 |  +  |  +  |  +  |  +  |  +  |     |  +  |     |	*/
	/*     2 |bltza|bgeza|  +  |  +  |     |     |     |     |	*/
	/*     3 |     |     |     |     |     |     |     |  +  |	*/
	/*  								*/
	/*  								*/
	/*     cop0 opcod extension (25 downto 21) :			*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 | mfc0|     |  +  |  +  | mtc0|     |  +  |  +  |	*/
	/*     1 |  +  |  +  |  +  |  +  |  +  |  +  |  +  |  +  |	*/
	/*     2 | c0  | c0  | c0  | c0  | c0  | c0  | c0  | c0  |	*/
	/*     3 | c0  | c0  | c0  | c0  | c0  | c0  | c0  | c0  |	*/
	/*  								*/
	/*  								*/
	/*     c0 cop0 extension extension (5 downto 0) :		*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 |     |  +  |  +  |     |     |     |  +  |     |	*/
	/*     1 |  +  |     |     |     |     |     |     |     |	*/
	/*     2 |rfe *|     |     |     |     |     |     |     |	*/
	/*     3 |eret%|     |     |     |     |     |     |  +  |	*/
	/*     4 |wait%|     |     |     |     |     |     |     |	*/
	/*     5 |     |     |     |     |     |     |     |     |	*/
	/*     6 |     |     |     |     |     |     |     |     |	*/
	/*     7 |     |     |     |     |     |     |     |     |	*/
	/*  								*/
	/*  								*/
	/*     cop2 opcod extension (25 downto 21) :			*/
	/*       |  0     1     2     3     4     5     6     7		*/
	/*     --+-----+-----+-----+-----+-----+-----+-----+-----+	*/
	/*     0 | mfc2|     |  +  |  +  | mtc2|     |  +  |  +  |	*/
	/*     1 |  +  |  +  |  +  |  +  |  +  |  +  |  +  |  +  |	*/
	/*     2 |  +  |  +  |  +  |  +  |  +  |  +  |  +  |  +  |	*/
	/*     3 |  +  |  +  |  +  |  +  |  +  |  +  |  +  |  +  |	*/
	/*  								*/
	/* ### ---------------------------------------------------- ### */

#define ASM_MPS__ADD                 0x00000020 /* Mips			*/
#define ASM_MPS__ADDI                0x20000000 /* Mips			*/
#define ASM_MPS__ADDU                0x00000021 /* Mips			*/
#define ASM_MPS__ADDIU               0x24000000 /* Mips			*/
#define ASM_MPS__AND                 0x00000024 /* Mips			*/
#define ASM_MPS__ANDI                0x30000000 /* Mips			*/
#define ASM_MPS__BEQ                 0x10000000 /* Mips			*/
#define ASM_MPS__BGEZ                0x04010000 /* Mips			*/
#define ASM_MPS__BGEZAL              0x04110000 /* Mips			*/
#define ASM_MPS__BGTZ                0x1c000000 /* Mips			*/
#define ASM_MPS__BLEZ                0x18000000 /* Mips			*/
#define ASM_MPS__BLTZ                0x04000000 /* Mips			*/
#define ASM_MPS__BLTZAL              0x04100000 /* Mips			*/
#define ASM_MPS__BNE                 0x14000000 /* Mips			*/
#define ASM_MPS__BREAK               0x0000000d /* Mips			*/
#define ASM_MPS__CLO                 0x70000021 /* Mips 32		*/
#define ASM_MPS__CLZ                 0x70000020 /* Mips 32		*/
#define ASM_MPS__DIV                 0x0000001a /* Mips	32		*/
#define ASM_MPS__DIVU                0x0000001b /* Mips	32		*/
#define ASM_MPS__EHB                 0x000000c0 /* Mips 32		*/
#define ASM_MPS__ERET                0x42000018 /* Mips 32		*/
#define ASM_MPS__J                   0x08000000 /* Mips			*/
#define ASM_MPS__JAL                 0x0c000000 /* Mips			*/
#define ASM_MPS__JALR                0x00000009 /* Mips			*/
#define ASM_MPS__JR                  0x00000008 /* Mips			*/
#define ASM_MPS__LB                  0x80000000 /* Mips			*/
#define ASM_MPS__LBU                 0x90000000 /* Mips			*/
#define ASM_MPS__LL                  0xc0000000 /* Mips 32		*/
#define ASM_MPS__LH                  0x84000000 /* Mips			*/
#define ASM_MPS__LHU                 0x94000000 /* Mips			*/
#define ASM_MPS__LUI                 0x3c000000 /* Mips			*/
#define ASM_MPS__LW                  0x8c000000 /* Mips			*/
#define ASM_MPS__LWL                 0x88000000 /* Mips			*/
#define ASM_MPS__LWR                 0x98000000 /* Mips			*/
#define ASM_MPS__MADD                0x70000000 /* Mips 32		*/
#define ASM_MPS__MADDU               0x70000001 /* Mips 32		*/
#define ASM_MPS__MFC0                0x40000000 /* Mips			*/
#define ASM_MPS__MFC2                0x48000000 /* Mips 32		*/
#define ASM_MPS__MFHI                0x00000010 /* Mips			*/
#define ASM_MPS__MFLO                0x00000012 /* Mips			*/
#define ASM_MPS__MOVN                0x0000000b /* Mips 32		*/
#define ASM_MPS__MOVZ                0x0000000a /* Mips 32		*/
#define ASM_MPS__MSUB                0x70000004 /* Mips 32		*/
#define ASM_MPS__MSUBU               0x70000005 /* Mips 32		*/
#define ASM_MPS__MTC0                0x40800000 /* Mips			*/
#define ASM_MPS__MTC2                0x48800000 /* Mips 32		*/
#define ASM_MPS__MTHI                0x00000011 /* Mips			*/
#define ASM_MPS__MTLO                0x00000013 /* Mips			*/
#define ASM_MPS__MUL                 0x70000002 /* Mips			*/
#define ASM_MPS__MULT                0x00000018 /* Mips			*/
#define ASM_MPS__MULTU               0x00000019 /* Mips			*/
#define ASM_MPS__NOR                 0x00000027 /* Mips			*/
#define ASM_MPS__OR                  0x00000025 /* Mips			*/
#define ASM_MPS__ORI                 0x34000000 /* Mips			*/
#define ASM_MPS__PREF                0xcc000000 /* Mips 32		*/
#define ASM_MPS__RFE                 0x42000010 /* Mips 1		*/
#define ASM_MPS__SB                  0xa0000000 /* Mips			*/
#define ASM_MPS__SC                  0xe0000000 /* Mips 32		*/
#define ASM_MPS__SH                  0xa4000000 /* Mips			*/
#define ASM_MPS__SLL                 0x00000000 /* Mips			*/
#define ASM_MPS__SLLV                0x00000004 /* Mips			*/
#define ASM_MPS__SLT                 0x0000002a /* Mips			*/
#define ASM_MPS__SLTI                0x28000000 /* Mips			*/
#define ASM_MPS__SLTU                0x0000002b /* Mips			*/
#define ASM_MPS__SLTIU               0x2c000000 /* Mips			*/
#define ASM_MPS__SRA                 0x00000003 /* Mips			*/
#define ASM_MPS__SRAV                0x00000007 /* Mips			*/
#define ASM_MPS__SRL                 0x00000002 /* Mips			*/
#define ASM_MPS__SRLV                0x00000006 /* Mips			*/
#define ASM_MPS__SUB                 0x00000022 /* Mips			*/
#define ASM_MPS__SUBU                0x00000023 /* Mips			*/
#define ASM_MPS__SW                  0xac000000 /* Mips			*/
#define ASM_MPS__SYNC                0x0000000f /* Mips 32		*/
#define ASM_MPS__SYSCALL             0x0000000c /* Mips			*/
#define ASM_MPS__TEQ                 0x00000034	/* Mips 32		*/
#define ASM_MPS__TEQI                0x040c0000	/* Mips 32		*/
#define ASM_MPS__TGE                 0x00000030	/* Mips 32		*/
#define ASM_MPS__TGEI                0x04080000	/* Mips 32		*/
#define ASM_MPS__TGEIU               0x04090000	/* Mips 32		*/
#define ASM_MPS__TGEU                0x00000031	/* Mips 32		*/
#define ASM_MPS__TLT                 0x00000032	/* Mips 32		*/
#define ASM_MPS__TLTI                0x040a0000	/* Mips 32		*/
#define ASM_MPS__TLTIU               0x040b0000	/* Mips 32		*/
#define ASM_MPS__TLTU                0x00000033	/* Mips 32		*/
#define ASM_MPS__TNE                 0x00000036	/* Mips 32		*/
#define ASM_MPS__TNEI                0x040e0000	/* Mips 32		*/
#define ASM_MPS__WAIT                0x42000020 /* Mips 32		*/
#define ASM_MPS__XOR                 0x00000026 /* Mips			*/
#define ASM_MPS__XORI                0x38000000 /* Mips			*/

#define ASM_MPS__B                   0x10000000 /* Mips macro (beq)	*/
#define ASM_MPS__BEQZ                0x10000000 /* Mips macro (beq)	*/
#define ASM_MPS__BNEZ                0x14000000 /* Mips macro (bne)	*/
#define ASM_MPS__NEG                 0x00000022 /* Mips macro (sub)	*/
#define ASM_MPS__NEGU                0x00000023 /* Mips macro (subu)	*/
#define ASM_MPS__NOP                 0x00000000 /* Mips macro (sll)	*/
#define ASM_MPS__MOVE                0x00000021 /* Mips macro (addu)	*/
#define ASM_MPS__LI                  0x00000001 /* Mips macro (lui, ori)*/

#define ASM_MPS__BADVADDR            0x00004000 /* Mips cop0 register	*/
#define ASM_MPS__COUNT               0x00004800 /* Mips cop0 register	*/
#define ASM_MPS__CAUSE               0x00006800 /* Mips cop0 register	*/
#define ASM_MPS__EBASE               0x00007801 /* Mips cop0 register	*/
#define ASM_MPS__EEPC                0x0000f000 /* Mips cop0 register	*/
#define ASM_MPS__EPC                 0x00007000 /* Mips cop0 register	*/
#define ASM_MPS__PRID                0x00007800 /* Mips cop0 register	*/
#define ASM_MPS__STATUS              0x00006000 /* Mips cop0 register	*/
#define ASM_MPS__TCCONTEXT           0x00001005 /* Mips cop0 register	*/

#define ASM_MPS__I_MSK               0xfc000000 /* Mips i       fmt	*/
#define ASM_MPS__R_MSK               0xfc00003f /* Mips r       fmt	*/
#define ASM_MPS__J_MSK               0xfc000000 /* Mips j       fmt	*/
#define ASM_MPS__IB_MSK              0xfc1f0000 /* Mips i bcond fmt	*/

	/* ###------------------------------------------------------### */
	/*    data structures						*/
	/* ###------------------------------------------------------### */

typedef struct asfig				/* description		*/
  {
  struct utdic      *GLB_DIC                  ;	/* global symbols	*/
  struct uttyp      *GLB_SYM                  ;	/* global symbols	*/
  struct uttyp      *MEM_TAB                  ;	/* memory table		*/
  struct asosc      *OUT_SEC                  ;	/* output sections	*/
  struct asisc      *IN_SEC                   ;	/* input  sections	*/
  struct asobj      *OBJECTS                  ;	/* object files		*/
  unsigned int       FLAG                     ;	/* flags		*/
  }
asm_asfig;

typedef struct asosc				/* output section	*/
  {
  struct asosc      *NEXT                     ;	/* next section		*/
  char              *IDENT                    ;	/* identifier		*/
  unsigned int       INS_NBR                  ;	/* in section number	*/
  struct asiss     **CUR_ISS                  ;	/* current sub-section	*/
  struct asiss     **SUB_SEC                  ;	/* sub-section adr-size	*/
  unsigned int       ADDR                     ;	/* address		*/
  unsigned int       SIZE                     ;	/* size			*/
  unsigned int       FLAG                     ;	/* flags		*/
  }
asm_asosc;

typedef struct asisc				/* input section	*/
  {
  struct asisc      *NEXT                     ;	/* next section		*/
  char              *IDENT                    ;	/* identifier		*/
  struct asosc      *OUT_SEC                  ;	/* output section	*/
  unsigned int       POSITION                 ;	/* position		*/
  unsigned int       FLAG                     ;	/* flags		*/
  }
asm_asisc;

typedef struct asobj				/* object file		*/
  {
  struct asobj      *NEXT                     ;	/* next			*/
  char              *IDENT                    ;	/* identifier		*/
  struct utdic      *SYM_DIC                  ;	/* symbols		*/
  struct uttyp      *SEC_SYM                  ;	/* out sections symbols	*/
  unsigned int       FLAG                     ;	/* flags		*/
  }
asm_asobj;

typedef struct asiss				/* input sub-section	*/
  {
  struct asiss      *NEXT                     ;	/* next			*/
  unsigned int       ADDR                     ;
  unsigned int       SIZE                     ;
  unsigned int       FLAG                     ;
  }
asm_asiss;

	/* ###------------------------------------------------------### */
	/*    global variables						*/
	/* ###------------------------------------------------------### */

extern unsigned int   ASM_ERR_LEVEL  ;		/* visible error levels	*/
extern unsigned int   ASM_STATUS     ;		/* status		*/

extern unsigned int   ASM_SET_FLAGS  ;		/* set directive	*/

extern unsigned int   ASM_LINENO     ;
//unsigned int   ASM_LINENO     ;
extern unsigned int   ASM_MAXERR     ;

extern unsigned int   ASM_ARCHI      ;
//unsigned int   ASM_ARCHI      ;

extern struct asosc  *ASM_FREOSC     ;
extern struct asisc  *ASM_FREISC     ;
extern struct asobj  *ASM_FREOBJ     ;
extern struct asiss  *ASM_FREISS     ;

	/* ###------------------------------------------------------### */
	/*    functions							*/
	/* ###------------------------------------------------------### */

//extern unsigned int   asm_error                  ();
extern unsigned int   asm_error                  (int           code, char         *func, int           line, char         *s1, int           n1);

extern struct asfig  *asm_addasfig               ();
extern struct asosc  *asm_addasosc               ();
extern struct asisc  *asm_addasisc               ();
extern struct asobj  *asm_addasobj               ();
extern struct asiss  *asm_addasiss               ();

extern struct asisc  *asm_revasisc               ();
extern struct asosc  *asm_revasosc               ();
extern struct asiss  *asm_revasiss               ();

extern struct uttyp  *asm_addmemtab              ();
extern struct uttyp  *asm_fndmemtab              ();

extern int            asm_cmpisssz               ();
extern int            asm_cmpissad               ();
extern int            asm_cmpissit               ();

extern void           asm_Initialize             ();

extern struct asisc  *asm_GetInputSection        ();
extern struct asosc  *asm_GetOutputSection       ();
extern struct asosc  *asm_GetInputOutSection     ();
//extern struct asobj  *asm_GetObject              ();
extern struct asobj  *asm_GetObject              (struct asfig *pt_fig,char         *ident);
extern struct uttyp  *asm_GetObjectSymbolList    ();

extern struct asfig  *asm_ReadMipsAsmFiles       ();
extern struct asfig  *asm_LoadMemory             ();

extern struct asfig  *asm_ldldscript             ();
extern struct asfig  *asm_ldmipsasm              ();

extern struct asosc  *asm_SetSectionsAddress     ();
extern struct asfig  *asm_InitCurSubSections     ();

extern unsigned int   asm_PrintMemory            ();
extern unsigned int   asm_PrintSymbols           ();

extern struct uttyp  *asm_SetMemory              ();
extern struct uttyp  *asm_SetWordMemory          ();

#endif
