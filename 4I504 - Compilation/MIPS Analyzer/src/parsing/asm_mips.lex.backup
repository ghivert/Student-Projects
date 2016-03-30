
/* ###--------------------------------------------------------------### */
/* file		: asm_mips.lex						*/
/* date		: Jun 21 2010						*/
/* version	: v200							*/
/* author	: Pirouz Bazargan Sabet					*/
/* description	: assembler						*/
/* ###--------------------------------------------------------------### */

%{
#include <stdlib.h>
#include <stdio.h>
#include "utl200.h"
#include "asm200.h"
//#include UTL_H
//#include ASM_H
#include "asm_mipsyac.h"

static int          search_token ();
static unsigned int search_valu  ();

#ifdef YY_DECL
#undef YY_DECL
#endif


#define YY_DECL int asm_mipslex (YYSTYPE *lval_pnt)
#define yylval (*lval_pnt)

//#define YY_NO_INPUT

// Try to fixes arguments asm_mipslex problem
//#define YY_DECL int asm_mipslex (lval_pnt) YYSTYPE *lval_pnt;
//#define yylval  (*lval_pnt)

//#define YY_DECL int asm_mipslex ();
//#define yylval  ()
%}

binary_digit      [0-1]
octal_digit       [0-7]
hexa_digit        [0-9a-fA-F]
digit             [0-9]
letter            [a-zA-Z]

hexa_valu         0x{hexa_digit}+
octal_valu        0o{octal_digit}+
binary_valu       0b{binary_digit}+
decimal_valu      {digit}+

octal_char        (\\[0-7][0-7]?[0-7]?)
hexa_char         (\\x{hexa_digit}+)
all_char          [^\\\"]
escape_char       (\\[ntvbrfa\\\?\'\"])
string_char       ({all_char}|{escape_char}|{octal_char}|{hexa_char})

character         (\'{string_char}\')
string            (\"{string_char}*\")
letter_or_digit   {letter}|{digit}
special_char      [\.\_\$]
identifier        ({special_char}|{letter})({special_char}|{letter_or_digit})*

string2_char       ({hexa_digit}|{letter}|[\_])
string2            ({string2_char}+)


%%
\n			{ ASM_LINENO ++; return (CarriageReturn); }
\:			{                return (Colon         ); }
[ \t]			{                                         }
\&			{                return (Ampersand     ); }
\|			{                return (Bar           ); }
\~			{                return (Tilda         ); }
\^			{                return (Circomflex    ); }
\+			{                return (Plus          ); }
\/			{                return (Slash         ); }
\*			{                return (Star          ); }
\<\<			{                return (DoubleLess    ); }
\>\>			{                return (DoubleGreat   ); }
\-			{                return (Minus         ); }
\(			{                return (LeftParen     ); }
\)			{                return (RightParen    ); }
\,			{                return (Comma         ); }
{hexa_valu}		{
 		//yylval.uval = utl_HexToInt (yytext + 2, NULL);
		int rt ;
		rt = strtol(yytext+2,NULL,16) ;
 		yylval.uval = rt ;
		//printf("hex_value : %d",rt) ;
		return (Litteral);
			}
{octal_valu}		{
 		//yylval.uval = utl_OctToInt (yytext + 2, NULL);
		int rt ;
		rt = strtol(yytext+2,NULL,8) ;
 		yylval.uval = rt ;
		return (Litteral);
			}
{binary_valu}		{
 		yylval.uval = utl_BinToInt (yytext + 2, NULL);
		return (Litteral);
			}
{decimal_valu}		{
 		if (sscanf (yytext, "%u", &yylval.uval) == 0)
		  yylval.uval = 0;
		return (Litteral);
			}
\@ {
	return (Arobase) ;
}

{character}		{
		char         *str    = NULL;
		char          c_val  ;

		str         = yytext + 1;
		c_val       = utl_CharToAscii (str, NULL);
		yylval.uval = (unsigned int) c_val;
		return (Litteral);
			}
{string}		{
		char * str ;
		
		str = utl_SaveString (yytext);
	  	yylval.text = str;
		return (String);
		}

\${decimal_valu}	{
		yylval.uval = atoi (yytext + 1);
		return (ARegister);
			}


\%{string2}\({identifier}\) {
		char * str ;
		
		str = utl_SaveString (yytext);
	  	yylval.text = str;
		return (GCC_operator);
		}

{identifier}		{
		int           token;
		char         *ident;

		ident = utl_SaveString (yytext);
		token = search_token   (ident );

		if (token == 0)
		  {
		  yylval.text = ident;
		  return (Identifier);
		  }
		else
		  {
		  yylval.uval = search_valu (ident);
		  return (token);
		  }
		}


#.*$			{					}
;.*$			{					}


{string2}		{
		char * str ;
		
		str = utl_SaveString (yytext);
	  	yylval.text = str;
		return (String2);
		}

%%

/* ###--------------------------------------------------------------### */
/* function	: yywrap						*/
/* description	: return 1						*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

int yywrap ()
  {
  return (1);
  }

/* ###--------------------------------------------------------------### */
/* function	: search_token						*/
/* description	: check if an identifier is a key-word or not		*/
/*									*/
/* called func.	: utl_CreateSimpleDic, utl_AddDicItem, utl_GetDicItem,	*/
/*		  utl_SaveString					*/
/* ###--------------------------------------------------------------### */

static int search_token (str)

char *str;

  {
  int                  val  = 0   ;
  static struct utdic *t_ht = NULL;

  if (t_ht == NULL)
    {
    t_ht = utl_CreateSimpleDic (UTL_DIC__BIG);

	/* ###------------------------------------------------------### */
	/*   key words							*/
	/* ###------------------------------------------------------### */

    utl_AddDicItem (t_ht, utl_SaveString ("$zero"     ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$at"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$v0"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$v1"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$a0"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$a1"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$a2"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$a3"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t0"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t1"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t2"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t3"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t4"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t5"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t6"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t7"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s0"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s1"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s2"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s3"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s4"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s5"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s6"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s7"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t8"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$t9"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$k0"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$k1"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$gp"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$sp"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$s8"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("$ra"       ), IntegerRegister  );
	// ADD
    utl_AddDicItem (t_ht, utl_SaveString ("$fp"       ), IntegerRegister  );

    utl_AddDicItem (t_ht, utl_SaveString ("zero"      ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("at"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("v0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("v1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("a0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("a1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("a2"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("a3"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t2"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t3"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t4"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t5"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t6"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t7"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s2"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s3"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s4"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s5"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s6"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s7"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t8"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("t9"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("k0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("k1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("gp"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("sp"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("s8"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("ra"        ), IntegerRegister  );

    utl_AddDicItem (t_ht, utl_SaveString ("r0"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r1"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r2"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r3"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r4"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r5"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r6"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r7"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r8"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r9"        ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r10"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r11"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r12"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r13"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r14"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r15"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r16"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r17"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r18"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r19"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r20"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r21"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r22"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r23"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r24"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r25"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r26"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r27"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r28"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r29"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r30"       ), IntegerRegister  );
    utl_AddDicItem (t_ht, utl_SaveString ("r31"       ), IntegerRegister  );

    utl_AddDicItem (t_ht, utl_SaveString ("badvaddr"  ), Cop0Register     );
    utl_AddDicItem (t_ht, utl_SaveString ("cause"     ), Cop0Register     );
    utl_AddDicItem (t_ht, utl_SaveString ("count"     ), Cop0Register     );
    utl_AddDicItem (t_ht, utl_SaveString ("epc"       ), Cop0Register     );
    utl_AddDicItem (t_ht, utl_SaveString ("prid"      ), Cop0Register     );
    utl_AddDicItem (t_ht, utl_SaveString ("status"    ), Cop0Register     );

    utl_AddDicItem (t_ht, utl_SaveString (".align"    ), _ALIGN_          );
    utl_AddDicItem (t_ht, utl_SaveString (".ascii"    ), _ASCII_          );
    utl_AddDicItem (t_ht, utl_SaveString (".asciiz"   ), _ASCIIZ_         );
    utl_AddDicItem (t_ht, utl_SaveString (".byte"     ), _BYTE_           );
    utl_AddDicItem (t_ht, utl_SaveString (".comm"     ), _COMM_           );
    utl_AddDicItem (t_ht, utl_SaveString (".end"      ), _END_            );
    utl_AddDicItem (t_ht, utl_SaveString (".ent"      ), _ENT_            );
    utl_AddDicItem (t_ht, utl_SaveString (".equ"      ), _EQU_            );
    utl_AddDicItem (t_ht, utl_SaveString (".extern"   ), _EXTERN_         );
    utl_AddDicItem (t_ht, utl_SaveString (".globl"    ), _GLOBAL_         );
    utl_AddDicItem (t_ht, utl_SaveString (".global"   ), _GLOBAL_         );
    utl_AddDicItem (t_ht, utl_SaveString (".lcomm"    ), _LCOMM_          );
    utl_AddDicItem (t_ht, utl_SaveString (".section"  ), _SECTION_        );
    utl_AddDicItem (t_ht, utl_SaveString (".set"      ), _SET_            );
    utl_AddDicItem (t_ht, utl_SaveString (".skip"     ), _SKIP_           );
    utl_AddDicItem (t_ht, utl_SaveString (".space"    ), _SPACE_          );
    utl_AddDicItem (t_ht, utl_SaveString (".word"     ), _WORD_           );

    utl_AddDicItem (t_ht, utl_SaveString ("reorder"   ), _REORDER_        );
    utl_AddDicItem (t_ht, utl_SaveString ("noreorder" ), _NOREORDER_      );

    utl_AddDicItem (t_ht, utl_SaveString ("b"         ), Macro_label      );
    utl_AddDicItem (t_ht, utl_SaveString ("beqz"      ), Macro_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bnez"      ), Macro_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("la"        ), Macro_rd_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("li"        ), Macro_rd_i32     );
    utl_AddDicItem (t_ht, utl_SaveString ("loadi"     ), Macro_rd_i32     );
    utl_AddDicItem (t_ht, utl_SaveString ("move"      ), Macro_rd_rs      );
    utl_AddDicItem (t_ht, utl_SaveString ("neg"       ), Macro_rd_rt      );
    utl_AddDicItem (t_ht, utl_SaveString ("negu"      ), Macro_rd_rt      );
    utl_AddDicItem (t_ht, utl_SaveString ("nop"       ), Macro_n          );

    utl_AddDicItem (t_ht, utl_SaveString ("add"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("addi"      ), Codop_rd_rs_si16 );
    utl_AddDicItem (t_ht, utl_SaveString ("addu"      ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("addiu"     ), Codop_rd_rs_si16 );
    utl_AddDicItem (t_ht, utl_SaveString ("and"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("andi"      ), Codop_rd_rs_ui16 );

    utl_AddDicItem (t_ht, utl_SaveString ("beq"       ), Codop_rs_rt_label);
    utl_AddDicItem (t_ht, utl_SaveString ("bgez"      ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bgezal"    ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bgtz"      ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("blez"      ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bltz"      ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bltzal"    ), Codop_rs_label   );
    utl_AddDicItem (t_ht, utl_SaveString ("bne"       ), Codop_rs_rt_label);
    utl_AddDicItem (t_ht, utl_SaveString ("break"     ), Codop_ui20       );

    utl_AddDicItem (t_ht, utl_SaveString ("j"         ), Codop_label      );
    utl_AddDicItem (t_ht, utl_SaveString ("jal"       ), Codop_label      );
    utl_AddDicItem (t_ht, utl_SaveString ("jalr"      ), Codop_od_rs      );
    utl_AddDicItem (t_ht, utl_SaveString ("jr"        ), Codop_rs         );

    utl_AddDicItem (t_ht, utl_SaveString ("lb"        ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lbu"       ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lh"        ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lhu"       ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lui"       ), Codop_rd_si16    );
    utl_AddDicItem (t_ht, utl_SaveString ("lw"        ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lwl"       ), Codop_rd_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("lwr"       ), Codop_rd_mem     );

    utl_AddDicItem (t_ht, utl_SaveString ("mfc0"      ), Codop_rt_cop0r   );
    utl_AddDicItem (t_ht, utl_SaveString ("mfhi"      ), Codop_rd         );
    utl_AddDicItem (t_ht, utl_SaveString ("mflo"      ), Codop_rd         );
    utl_AddDicItem (t_ht, utl_SaveString ("mtc0"      ), Codop_rt_cop0r   );
    utl_AddDicItem (t_ht, utl_SaveString ("mthi"      ), Codop_rs         );
    utl_AddDicItem (t_ht, utl_SaveString ("mtlo"      ), Codop_rs         );
    utl_AddDicItem (t_ht, utl_SaveString ("mul"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("mult"      ), Codop_rs_rt      );
    utl_AddDicItem (t_ht, utl_SaveString ("multu"     ), Codop_rs_rt      );

    utl_AddDicItem (t_ht, utl_SaveString ("nor"       ), Codop_rd_rs_rt   );

    utl_AddDicItem (t_ht, utl_SaveString ("or"        ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("ori"       ), Codop_rd_rs_ui16 );

    utl_AddDicItem (t_ht, utl_SaveString ("sb"        ), Codop_rt_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("sh"        ), Codop_rt_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("sll"       ), Codop_rd_rt_sham );
    utl_AddDicItem (t_ht, utl_SaveString ("sllv"      ), Codop_rd_rt_rs   );
    utl_AddDicItem (t_ht, utl_SaveString ("slt"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("slti"      ), Codop_rd_rs_si16 );
    utl_AddDicItem (t_ht, utl_SaveString ("sltiu"     ), Codop_rd_rs_si16 );
    utl_AddDicItem (t_ht, utl_SaveString ("sltu"      ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("sra"       ), Codop_rd_rt_sham );
    utl_AddDicItem (t_ht, utl_SaveString ("srav"      ), Codop_rd_rt_rs   );
    utl_AddDicItem (t_ht, utl_SaveString ("srl"       ), Codop_rd_rt_sham );
    utl_AddDicItem (t_ht, utl_SaveString ("srlv"      ), Codop_rd_rt_rs   );
    utl_AddDicItem (t_ht, utl_SaveString ("sub"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("subu"      ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("sw"        ), Codop_rt_mem     );
    utl_AddDicItem (t_ht, utl_SaveString ("syscall"   ), Codop_n          );

    utl_AddDicItem (t_ht, utl_SaveString ("xor"       ), Codop_rd_rs_rt   );
    utl_AddDicItem (t_ht, utl_SaveString ("xori"      ), Codop_rd_rs_ui16 );

	/* ###------------------------------------------------------### */
	/*   architecture dependent key words				*/
	/* ###------------------------------------------------------### */

    //if (ASM_ARCHI == ASM_ARC__MIPS32)
    if (1)
      {
      utl_AddDicItem (t_ht, utl_SaveString ("clo"       ), Codop_rd_rs      );
      utl_AddDicItem (t_ht, utl_SaveString ("clz"       ), Codop_rd_rs      );
      utl_AddDicItem (t_ht, utl_SaveString ("div"       ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("divu"      ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("ebase"     ), Cop0Register     );
      utl_AddDicItem (t_ht, utl_SaveString ("eepc"      ), Cop0Register     );
      utl_AddDicItem (t_ht, utl_SaveString ("eret"      ), Codop_n          );
      utl_AddDicItem (t_ht, utl_SaveString ("ll"        ), Codop_rd_mem     );
      utl_AddDicItem (t_ht, utl_SaveString ("madd"      ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("maddu"     ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("mfc2"      ), Codop_rt_cop2r   );
      utl_AddDicItem (t_ht, utl_SaveString ("movn"      ), Codop_rd_rs_rt   );
      utl_AddDicItem (t_ht, utl_SaveString ("movz"      ), Codop_rd_rs_rt   );
      utl_AddDicItem (t_ht, utl_SaveString ("msub"      ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("msubu"     ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("mtc2"      ), Codop_rt_cop2r   );
      utl_AddDicItem (t_ht, utl_SaveString ("pref"      ), Codop_hint_mem   );
      utl_AddDicItem (t_ht, utl_SaveString ("sc"        ), Codop_rt_mem     );
      utl_AddDicItem (t_ht, utl_SaveString ("sync"      ), Codop_n          );
      utl_AddDicItem (t_ht, utl_SaveString ("tccontext" ), Cop0Register     );
      utl_AddDicItem (t_ht, utl_SaveString ("teq"       ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("teqi"      ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("tge"       ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("tgei"      ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("tgeiu"     ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("tgeu"      ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("tlt"       ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("tlti"      ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("tltiu"     ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("tltu"      ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("tne"       ), Codop_rs_rt      );
      utl_AddDicItem (t_ht, utl_SaveString ("tnei"      ), Codop_rs_si16    );
      utl_AddDicItem (t_ht, utl_SaveString ("wait"      ), Codop_n          );
      }

    //if (ASM_ARCHI == ASM_ARC__MIPS1 )
    if (1)
      {
      utl_AddDicItem (t_ht, utl_SaveString ("rfe"       ), Codop_n          );
      }

    }

  val = (int) utl_GetDicItem (t_ht, str);
  return (val);
  }

/* ###--------------------------------------------------------------### */
/* function	: search_valu						*/
/* description	: return the value corresponding to a token		*/
/*									*/
/* called func.	: utl_CreateSimpleDic, utl_AddDicItem, utl_GetDicItem,	*/
/*		  utl_SaveString					*/
/* ###--------------------------------------------------------------### */

static struct utdic *v_ht = NULL;

static unsigned int search_valu (str)

char *str;

  {
  unsigned int         val  = 0   ;
  //static struct utdic *v_ht = NULL;

  if (v_ht == NULL)
    {
    v_ht = utl_CreateSimpleDic (UTL_DIC__BIG);

	/* ###------------------------------------------------------### */
	/*   key words							*/
	/* ###------------------------------------------------------### */

    utl_AddDicItem (v_ht, utl_SaveString ("$zero"     ),                 0);
    utl_AddDicItem (v_ht, utl_SaveString ("$at"       ),                 1);
    utl_AddDicItem (v_ht, utl_SaveString ("$v0"       ),                 2);
    utl_AddDicItem (v_ht, utl_SaveString ("$v1"       ),                 3);
    utl_AddDicItem (v_ht, utl_SaveString ("$a0"       ),                 4);
    utl_AddDicItem (v_ht, utl_SaveString ("$a1"       ),                 5);
    utl_AddDicItem (v_ht, utl_SaveString ("$a2"       ),                 6);
    utl_AddDicItem (v_ht, utl_SaveString ("$a3"       ),                 7);
    utl_AddDicItem (v_ht, utl_SaveString ("$t0"       ),                 8);
    utl_AddDicItem (v_ht, utl_SaveString ("$t1"       ),                 9);
    utl_AddDicItem (v_ht, utl_SaveString ("$t2"       ),                10);
    utl_AddDicItem (v_ht, utl_SaveString ("$t3"       ),                11);
    utl_AddDicItem (v_ht, utl_SaveString ("$t4"       ),                12);
    utl_AddDicItem (v_ht, utl_SaveString ("$t5"       ),                13);
    utl_AddDicItem (v_ht, utl_SaveString ("$t6"       ),                14);
    utl_AddDicItem (v_ht, utl_SaveString ("$t7"       ),                15);
    utl_AddDicItem (v_ht, utl_SaveString ("$s0"       ),                16);
    utl_AddDicItem (v_ht, utl_SaveString ("$s1"       ),                17);
    utl_AddDicItem (v_ht, utl_SaveString ("$s2"       ),                18);
    utl_AddDicItem (v_ht, utl_SaveString ("$s3"       ),                19);
    utl_AddDicItem (v_ht, utl_SaveString ("$s4"       ),                20);
    utl_AddDicItem (v_ht, utl_SaveString ("$s5"       ),                21);
    utl_AddDicItem (v_ht, utl_SaveString ("$s6"       ),                22);
    utl_AddDicItem (v_ht, utl_SaveString ("$s7"       ),                23);
    utl_AddDicItem (v_ht, utl_SaveString ("$t8"       ),                24);
    utl_AddDicItem (v_ht, utl_SaveString ("$t9"       ),                25);
    utl_AddDicItem (v_ht, utl_SaveString ("$k0"       ),                26);
    utl_AddDicItem (v_ht, utl_SaveString ("$k1"       ),                27);
    utl_AddDicItem (v_ht, utl_SaveString ("$gp"       ),                28);
    utl_AddDicItem (v_ht, utl_SaveString ("$sp"       ),                29);
    utl_AddDicItem (v_ht, utl_SaveString ("$s8"       ),                30);
    utl_AddDicItem (v_ht, utl_SaveString ("$ra"       ),                31);
    // ADD 
	utl_AddDicItem (v_ht, utl_SaveString ("$fp"       ),                30);

    utl_AddDicItem (v_ht, utl_SaveString ("zero"      ),                 0);
    utl_AddDicItem (v_ht, utl_SaveString ("at"        ),                 1);
    utl_AddDicItem (v_ht, utl_SaveString ("v0"        ),                 2);
    utl_AddDicItem (v_ht, utl_SaveString ("v1"        ),                 3);
    utl_AddDicItem (v_ht, utl_SaveString ("a0"        ),                 4);
    utl_AddDicItem (v_ht, utl_SaveString ("a1"        ),                 5);
    utl_AddDicItem (v_ht, utl_SaveString ("a2"        ),                 6);
    utl_AddDicItem (v_ht, utl_SaveString ("a3"        ),                 7);
    utl_AddDicItem (v_ht, utl_SaveString ("t0"        ),                 8);
    utl_AddDicItem (v_ht, utl_SaveString ("t1"        ),                 9);
    utl_AddDicItem (v_ht, utl_SaveString ("t2"        ),                10);
    utl_AddDicItem (v_ht, utl_SaveString ("t3"        ),                11);
    utl_AddDicItem (v_ht, utl_SaveString ("t4"        ),                12);
    utl_AddDicItem (v_ht, utl_SaveString ("t5"        ),                13);
    utl_AddDicItem (v_ht, utl_SaveString ("t6"        ),                14);
    utl_AddDicItem (v_ht, utl_SaveString ("t7"        ),                15);
    utl_AddDicItem (v_ht, utl_SaveString ("s0"        ),                16);
    utl_AddDicItem (v_ht, utl_SaveString ("s1"        ),                17);
    utl_AddDicItem (v_ht, utl_SaveString ("s2"        ),                18);
    utl_AddDicItem (v_ht, utl_SaveString ("s3"        ),                19);
    utl_AddDicItem (v_ht, utl_SaveString ("s4"        ),                20);
    utl_AddDicItem (v_ht, utl_SaveString ("s5"        ),                21);
    utl_AddDicItem (v_ht, utl_SaveString ("s6"        ),                22);
    utl_AddDicItem (v_ht, utl_SaveString ("s7"        ),                23);
    utl_AddDicItem (v_ht, utl_SaveString ("t8"        ),                24);
    utl_AddDicItem (v_ht, utl_SaveString ("t9"        ),                25);
    utl_AddDicItem (v_ht, utl_SaveString ("k0"        ),                26);
    utl_AddDicItem (v_ht, utl_SaveString ("k1"        ),                27);
    utl_AddDicItem (v_ht, utl_SaveString ("gp"        ),                28);
    utl_AddDicItem (v_ht, utl_SaveString ("sp"        ),                29);
    utl_AddDicItem (v_ht, utl_SaveString ("s8"        ),                30);
    utl_AddDicItem (v_ht, utl_SaveString ("ra"        ),                31);

    utl_AddDicItem (v_ht, utl_SaveString ("r0"        ),                 0);
    utl_AddDicItem (v_ht, utl_SaveString ("r1"        ),                 1);
    utl_AddDicItem (v_ht, utl_SaveString ("r2"        ),                 2);
    utl_AddDicItem (v_ht, utl_SaveString ("r3"        ),                 3);
    utl_AddDicItem (v_ht, utl_SaveString ("r4"        ),                 4);
    utl_AddDicItem (v_ht, utl_SaveString ("r5"        ),                 5);
    utl_AddDicItem (v_ht, utl_SaveString ("r6"        ),                 6);
    utl_AddDicItem (v_ht, utl_SaveString ("r7"        ),                 7);
    utl_AddDicItem (v_ht, utl_SaveString ("r8"        ),                 8);
    utl_AddDicItem (v_ht, utl_SaveString ("r9"        ),                 9);
    utl_AddDicItem (v_ht, utl_SaveString ("r10"       ),                10);
    utl_AddDicItem (v_ht, utl_SaveString ("r11"       ),                11);
    utl_AddDicItem (v_ht, utl_SaveString ("r12"       ),                12);
    utl_AddDicItem (v_ht, utl_SaveString ("r13"       ),                13);
    utl_AddDicItem (v_ht, utl_SaveString ("r14"       ),                14);
    utl_AddDicItem (v_ht, utl_SaveString ("r15"       ),                15);
    utl_AddDicItem (v_ht, utl_SaveString ("r16"       ),                16);
    utl_AddDicItem (v_ht, utl_SaveString ("r17"       ),                17);
    utl_AddDicItem (v_ht, utl_SaveString ("r18"       ),                18);
    utl_AddDicItem (v_ht, utl_SaveString ("r19"       ),                19);
    utl_AddDicItem (v_ht, utl_SaveString ("r20"       ),                20);
    utl_AddDicItem (v_ht, utl_SaveString ("r21"       ),                21);
    utl_AddDicItem (v_ht, utl_SaveString ("r22"       ),                22);
    utl_AddDicItem (v_ht, utl_SaveString ("r23"       ),                23);
    utl_AddDicItem (v_ht, utl_SaveString ("r24"       ),                24);
    utl_AddDicItem (v_ht, utl_SaveString ("r25"       ),                25);
    utl_AddDicItem (v_ht, utl_SaveString ("r26"       ),                26);
    utl_AddDicItem (v_ht, utl_SaveString ("r27"       ),                27);
    utl_AddDicItem (v_ht, utl_SaveString ("r28"       ),                28);
    utl_AddDicItem (v_ht, utl_SaveString ("r29"       ),                29);
    utl_AddDicItem (v_ht, utl_SaveString ("r30"       ),                30);
    utl_AddDicItem (v_ht, utl_SaveString ("r31"       ),                31);

    utl_AddDicItem (v_ht, utl_SaveString ("badvaddr"  ), ASM_MPS__BADVADDR);
    utl_AddDicItem (v_ht, utl_SaveString ("cause"     ), ASM_MPS__CAUSE   );
    utl_AddDicItem (v_ht, utl_SaveString ("count"     ), ASM_MPS__COUNT   );
    utl_AddDicItem (v_ht, utl_SaveString ("epc"       ), ASM_MPS__EPC     );
    utl_AddDicItem (v_ht, utl_SaveString ("prid"      ), ASM_MPS__PRID    );
    utl_AddDicItem (v_ht, utl_SaveString ("status"    ), ASM_MPS__STATUS  );

    utl_AddDicItem (v_ht, utl_SaveString (".align"    ), _ALIGN_          );
    utl_AddDicItem (v_ht, utl_SaveString (".ascii"    ), _ASCII_          );
    utl_AddDicItem (v_ht, utl_SaveString (".asciiz"   ), _ASCIIZ_         );
    utl_AddDicItem (v_ht, utl_SaveString (".byte"     ), _BYTE_           );
    utl_AddDicItem (v_ht, utl_SaveString (".comm"     ), _COMM_           );
    utl_AddDicItem (v_ht, utl_SaveString (".end"      ), _END_            );
    utl_AddDicItem (v_ht, utl_SaveString (".ent"      ), _ENT_            );
    utl_AddDicItem (v_ht, utl_SaveString (".equ"      ), _EQU_            );
    utl_AddDicItem (v_ht, utl_SaveString (".extern"   ), _EXTERN_         );
    utl_AddDicItem (v_ht, utl_SaveString (".globl"    ), _GLOBAL_         );
    utl_AddDicItem (v_ht, utl_SaveString (".global"   ), _GLOBAL_         );
    utl_AddDicItem (v_ht, utl_SaveString (".lcomm"    ), _LCOMM_          );
    utl_AddDicItem (v_ht, utl_SaveString (".section"  ), _SECTION_        );
    utl_AddDicItem (v_ht, utl_SaveString (".set"      ), _SET_            );
    utl_AddDicItem (v_ht, utl_SaveString (".skip"     ), _SKIP_           );
    utl_AddDicItem (v_ht, utl_SaveString (".space"    ), _SPACE_          );
    utl_AddDicItem (v_ht, utl_SaveString (".word"     ), _WORD_           );

    utl_AddDicItem (v_ht, utl_SaveString ("reorder"   ), _REORDER_        );
    utl_AddDicItem (v_ht, utl_SaveString ("noreorder" ), _NOREORDER_      );

    utl_AddDicItem (v_ht, utl_SaveString ("b"         ), ASM_MPS__B       );
    utl_AddDicItem (v_ht, utl_SaveString ("beqz"      ), ASM_MPS__BEQZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("bnez"      ), ASM_MPS__BNEZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("la"        ), ASM_MPS__LI      );
    utl_AddDicItem (v_ht, utl_SaveString ("li"        ), ASM_MPS__LI      );
    utl_AddDicItem (v_ht, utl_SaveString ("loadi"     ), ASM_MPS__LI      );
    utl_AddDicItem (v_ht, utl_SaveString ("move"      ), ASM_MPS__MOVE    );
    utl_AddDicItem (v_ht, utl_SaveString ("neg"       ), ASM_MPS__NEG     );
    utl_AddDicItem (v_ht, utl_SaveString ("negu"      ), ASM_MPS__NEGU    );
    utl_AddDicItem (v_ht, utl_SaveString ("nop"       ), ASM_MPS__NOP     );

    utl_AddDicItem (v_ht, utl_SaveString ("add"       ), ASM_MPS__ADD     );
    utl_AddDicItem (v_ht, utl_SaveString ("addi"      ), ASM_MPS__ADDI    );
    utl_AddDicItem (v_ht, utl_SaveString ("addu"      ), ASM_MPS__ADDU    );
    utl_AddDicItem (v_ht, utl_SaveString ("addiu"     ), ASM_MPS__ADDIU   );
    utl_AddDicItem (v_ht, utl_SaveString ("and"       ), ASM_MPS__AND     );
    utl_AddDicItem (v_ht, utl_SaveString ("andi"      ), ASM_MPS__ANDI    );

    utl_AddDicItem (v_ht, utl_SaveString ("beq"       ), ASM_MPS__BEQ     );
    utl_AddDicItem (v_ht, utl_SaveString ("bgez"      ), ASM_MPS__BGEZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("bgezal"    ), ASM_MPS__BGEZAL  );
    utl_AddDicItem (v_ht, utl_SaveString ("bgtz"      ), ASM_MPS__BGTZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("blez"      ), ASM_MPS__BLEZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("bltz"      ), ASM_MPS__BLTZ    );
    utl_AddDicItem (v_ht, utl_SaveString ("bltzal"    ), ASM_MPS__BLTZAL  );
    utl_AddDicItem (v_ht, utl_SaveString ("bne"       ), ASM_MPS__BNE     );
    utl_AddDicItem (v_ht, utl_SaveString ("break"     ), ASM_MPS__BREAK   );

    utl_AddDicItem (v_ht, utl_SaveString ("j"         ), ASM_MPS__J       );
    utl_AddDicItem (v_ht, utl_SaveString ("jal"       ), ASM_MPS__JAL     );
    utl_AddDicItem (v_ht, utl_SaveString ("jalr"      ), ASM_MPS__JALR    );
    utl_AddDicItem (v_ht, utl_SaveString ("jr"        ), ASM_MPS__JR      );

    utl_AddDicItem (v_ht, utl_SaveString ("lb"        ), ASM_MPS__LB      );
    utl_AddDicItem (v_ht, utl_SaveString ("lbu"       ), ASM_MPS__LBU     );
    utl_AddDicItem (v_ht, utl_SaveString ("lh"        ), ASM_MPS__LH      );
    utl_AddDicItem (v_ht, utl_SaveString ("lhu"       ), ASM_MPS__LHU     );
    utl_AddDicItem (v_ht, utl_SaveString ("lui"       ), ASM_MPS__LUI     );
    utl_AddDicItem (v_ht, utl_SaveString ("lw"        ), ASM_MPS__LW      );
    utl_AddDicItem (v_ht, utl_SaveString ("lwl"       ), ASM_MPS__LWL     );
    utl_AddDicItem (v_ht, utl_SaveString ("lwr"       ), ASM_MPS__LWR     );

    utl_AddDicItem (v_ht, utl_SaveString ("mfc0"      ), ASM_MPS__MFC0    );
    utl_AddDicItem (v_ht, utl_SaveString ("mfhi"      ), ASM_MPS__MFHI    );
    utl_AddDicItem (v_ht, utl_SaveString ("mflo"      ), ASM_MPS__MFLO    );
    utl_AddDicItem (v_ht, utl_SaveString ("mtc0"      ), ASM_MPS__MTC0    );
    utl_AddDicItem (v_ht, utl_SaveString ("mthi"      ), ASM_MPS__MTHI    );
    utl_AddDicItem (v_ht, utl_SaveString ("mtlo"      ), ASM_MPS__MTLO    );
    utl_AddDicItem (v_ht, utl_SaveString ("mul"       ), ASM_MPS__MUL     );
    utl_AddDicItem (v_ht, utl_SaveString ("mult"      ), ASM_MPS__MULT    );
    utl_AddDicItem (v_ht, utl_SaveString ("multu"     ), ASM_MPS__MULTU   );

    utl_AddDicItem (v_ht, utl_SaveString ("nor"       ), ASM_MPS__NOR     );

    utl_AddDicItem (v_ht, utl_SaveString ("or"        ), ASM_MPS__OR      );
    utl_AddDicItem (v_ht, utl_SaveString ("ori"       ), ASM_MPS__ORI     );

    utl_AddDicItem (v_ht, utl_SaveString ("sb"        ), ASM_MPS__SB      );
    utl_AddDicItem (v_ht, utl_SaveString ("sh"        ), ASM_MPS__SH      );
    utl_AddDicItem (v_ht, utl_SaveString ("sll"       ), ASM_MPS__SLL     );
    utl_AddDicItem (v_ht, utl_SaveString ("sllv"      ), ASM_MPS__SLLV    );
    utl_AddDicItem (v_ht, utl_SaveString ("slt"       ), ASM_MPS__SLT     );
    utl_AddDicItem (v_ht, utl_SaveString ("slti"      ), ASM_MPS__SLTI    );
    utl_AddDicItem (v_ht, utl_SaveString ("sltiu"     ), ASM_MPS__SLTIU   );
    utl_AddDicItem (v_ht, utl_SaveString ("sltu"      ), ASM_MPS__SLTU    );
    utl_AddDicItem (v_ht, utl_SaveString ("sra"       ), ASM_MPS__SRA     );
    utl_AddDicItem (v_ht, utl_SaveString ("srav"      ), ASM_MPS__SRAV    );
    utl_AddDicItem (v_ht, utl_SaveString ("srl"       ), ASM_MPS__SRL     );
    utl_AddDicItem (v_ht, utl_SaveString ("srlv"      ), ASM_MPS__SRLV    );
    utl_AddDicItem (v_ht, utl_SaveString ("sub"       ), ASM_MPS__SUB     );
    utl_AddDicItem (v_ht, utl_SaveString ("subu"      ), ASM_MPS__SUBU    );
    utl_AddDicItem (v_ht, utl_SaveString ("sw"        ), ASM_MPS__SW      );
    utl_AddDicItem (v_ht, utl_SaveString ("syscall"   ), ASM_MPS__SYSCALL );

    utl_AddDicItem (v_ht, utl_SaveString ("xor"       ), ASM_MPS__XOR     );
    utl_AddDicItem (v_ht, utl_SaveString ("xori"      ), ASM_MPS__XORI    );

	/* ###------------------------------------------------------### */
	/*   architecture dependent key words				*/
	/* ###------------------------------------------------------### */

    //if (ASM_ARCHI == ASM_ARC__MIPS32)
    if (1)
      {
      utl_AddDicItem (v_ht, utl_SaveString ("clo"       ), ASM_MPS__CLO      );
      utl_AddDicItem (v_ht, utl_SaveString ("clz"       ), ASM_MPS__CLZ      );
      utl_AddDicItem (v_ht, utl_SaveString ("div"       ), ASM_MPS__DIV      );
      utl_AddDicItem (v_ht, utl_SaveString ("divu"      ), ASM_MPS__DIVU     );
      utl_AddDicItem (v_ht, utl_SaveString ("ebase"     ), ASM_MPS__EBASE    );
      utl_AddDicItem (v_ht, utl_SaveString ("eepc"      ), ASM_MPS__EEPC     );
      utl_AddDicItem (v_ht, utl_SaveString ("eret"      ), ASM_MPS__ERET     );
      utl_AddDicItem (v_ht, utl_SaveString ("ll"        ), ASM_MPS__LL       );
      utl_AddDicItem (v_ht, utl_SaveString ("madd"      ), ASM_MPS__MADD     );
      utl_AddDicItem (v_ht, utl_SaveString ("maddu"     ), ASM_MPS__MADDU    );
      utl_AddDicItem (v_ht, utl_SaveString ("mfc2"      ), ASM_MPS__MFC2     );
      utl_AddDicItem (v_ht, utl_SaveString ("movn"      ), ASM_MPS__MOVN     );
      utl_AddDicItem (v_ht, utl_SaveString ("movz"      ), ASM_MPS__MOVZ     );
      utl_AddDicItem (v_ht, utl_SaveString ("msub"      ), ASM_MPS__MSUB     );
      utl_AddDicItem (v_ht, utl_SaveString ("msubu"     ), ASM_MPS__MSUBU    );
      utl_AddDicItem (v_ht, utl_SaveString ("mtc2"      ), ASM_MPS__MTC2     );
      utl_AddDicItem (v_ht, utl_SaveString ("pref"      ), ASM_MPS__PREF     );
      utl_AddDicItem (v_ht, utl_SaveString ("sc"        ), ASM_MPS__SC       );
      utl_AddDicItem (v_ht, utl_SaveString ("sync"      ), ASM_MPS__SYNC     );
      utl_AddDicItem (v_ht, utl_SaveString ("tccontext" ), ASM_MPS__TCCONTEXT);
      utl_AddDicItem (v_ht, utl_SaveString ("teq"       ), ASM_MPS__TEQ      );
      utl_AddDicItem (v_ht, utl_SaveString ("teqi"      ), ASM_MPS__TEQI     );
      utl_AddDicItem (v_ht, utl_SaveString ("tge"       ), ASM_MPS__TGE      );
      utl_AddDicItem (v_ht, utl_SaveString ("tgei"      ), ASM_MPS__TGEI     );
      utl_AddDicItem (v_ht, utl_SaveString ("tgeiu"     ), ASM_MPS__TGEIU    );
      utl_AddDicItem (v_ht, utl_SaveString ("tgeu"      ), ASM_MPS__TGEU     );
      utl_AddDicItem (v_ht, utl_SaveString ("tlt"       ), ASM_MPS__TLT      );
      utl_AddDicItem (v_ht, utl_SaveString ("tlti"      ), ASM_MPS__TLTI     );
      utl_AddDicItem (v_ht, utl_SaveString ("tltiu"     ), ASM_MPS__TLTIU    );
      utl_AddDicItem (v_ht, utl_SaveString ("tltu"      ), ASM_MPS__TLTU     );
      utl_AddDicItem (v_ht, utl_SaveString ("tne"       ), ASM_MPS__TNE      );
      utl_AddDicItem (v_ht, utl_SaveString ("tnei"      ), ASM_MPS__TNEI     );
      utl_AddDicItem (v_ht, utl_SaveString ("wait"      ), ASM_MPS__WAIT     );
      }

    //if (ASM_ARCHI == ASM_ARC__MIPS1 )
    if (1 )
      {
      utl_AddDicItem (v_ht, utl_SaveString ("rfe"       ), ASM_MPS__RFE      );
      }

    }

  val = (unsigned int) utl_GetDicItem (v_ht, str);
  return (val);
  }
