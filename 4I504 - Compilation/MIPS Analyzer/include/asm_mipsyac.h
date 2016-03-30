/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _ALIGN_ = 258,
     _ASCII_ = 259,
     _ASCIIZ_ = 260,
     _BYTE_ = 261,
     _COMM_ = 262,
     _END_ = 263,
     _ENT_ = 264,
     _EQU_ = 265,
     _EXTERN_ = 266,
     _GLOBAL_ = 267,
     _LCOMM_ = 268,
     _NOREORDER_ = 269,
     _REORDER_ = 270,
     _SECTION_ = 271,
     _SET_ = 272,
     _SKIP_ = 273,
     _SPACE_ = 274,
     _WORD_ = 275,
     ARegister = 276,
     Ampersand = 277,
     Bar = 278,
     CarriageReturn = 279,
     Circomflex = 280,
     Codop_hint_mem = 281,
     Codop_label = 282,
     Codop_n = 283,
     Codop_od_rs = 284,
     Codop_rd = 285,
     Codop_rd_si16 = 286,
     Codop_rd_rs = 287,
     Codop_rd_rs_rt = 288,
     Codop_rd_rt_sham = 289,
     Codop_rd_rt_rs = 290,
     Codop_rd_rs_si16 = 291,
     Codop_rd_rs_ui16 = 292,
     Codop_rd_mem = 293,
     Codop_rs = 294,
     Codop_rs_label = 295,
     Codop_rs_rt = 296,
     Codop_rs_rt_label = 297,
     Codop_rs_si16 = 298,
     Codop_rt_cop0r = 299,
     Codop_rt_cop2r = 300,
     Codop_rt_mem = 301,
     Codop_ui20 = 302,
     Colon = 303,
     Comma = 304,
     Cop0Register = 305,
     DoubleGreat = 306,
     DoubleLess = 307,
     Identifier = 308,
     IntegerRegister = 309,
     LeftParen = 310,
     Litteral = 311,
     Macro_label = 312,
     Macro_n = 313,
     Macro_rd_i32 = 314,
     Macro_rd_rs = 315,
     Macro_rd_rt = 316,
     Macro_rd_label = 317,
     Macro_rs_label = 318,
     Minus = 319,
     Plus = 320,
     Register = 321,
     RightParen = 322,
     Slash = 323,
     Star = 324,
     String = 325,
     String2 = 326,
     GCC_operator = 327,
     Tilda = 328,
     Arobase = 329
   };
#endif
/* Tokens.  */
#define _ALIGN_ 258
#define _ASCII_ 259
#define _ASCIIZ_ 260
#define _BYTE_ 261
#define _COMM_ 262
#define _END_ 263
#define _ENT_ 264
#define _EQU_ 265
#define _EXTERN_ 266
#define _GLOBAL_ 267
#define _LCOMM_ 268
#define _NOREORDER_ 269
#define _REORDER_ 270
#define _SECTION_ 271
#define _SET_ 272
#define _SKIP_ 273
#define _SPACE_ 274
#define _WORD_ 275
#define ARegister 276
#define Ampersand 277
#define Bar 278
#define CarriageReturn 279
#define Circomflex 280
#define Codop_hint_mem 281
#define Codop_label 282
#define Codop_n 283
#define Codop_od_rs 284
#define Codop_rd 285
#define Codop_rd_si16 286
#define Codop_rd_rs 287
#define Codop_rd_rs_rt 288
#define Codop_rd_rt_sham 289
#define Codop_rd_rt_rs 290
#define Codop_rd_rs_si16 291
#define Codop_rd_rs_ui16 292
#define Codop_rd_mem 293
#define Codop_rs 294
#define Codop_rs_label 295
#define Codop_rs_rt 296
#define Codop_rs_rt_label 297
#define Codop_rs_si16 298
#define Codop_rt_cop0r 299
#define Codop_rt_cop2r 300
#define Codop_rt_mem 301
#define Codop_ui20 302
#define Colon 303
#define Comma 304
#define Cop0Register 305
#define DoubleGreat 306
#define DoubleLess 307
#define Identifier 308
#define IntegerRegister 309
#define LeftParen 310
#define Litteral 311
#define Macro_label 312
#define Macro_n 313
#define Macro_rd_i32 314
#define Macro_rd_rs 315
#define Macro_rd_rt 316
#define Macro_rd_label 317
#define Macro_rs_label 318
#define Minus 319
#define Plus 320
#define Register 321
#define RightParen 322
#define Slash 323
#define Star 324
#define String 325
#define String2 326
#define GCC_operator 327
#define Tilda 328
#define Arobase 329




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 63 "asm_mips.yac"
{
  struct utchn  *pchn    ;
  unsigned int   uval    ;
  char          *text    ;
  }
/* Line 1529 of yacc.c.  */
#line 203 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



