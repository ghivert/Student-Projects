
/* ###--------------------------------------------------------------### */
/* file		: utl_GetVhdlName.c					*/
/* date		: May 24 2006						*/
/* version	: v102							*/
/* authors	: Pirouz Bazagan Sabet					*/
/* description	: Utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include <string.h>
#include UTL_H

#define  UTL_VHD__NAMNBR  82

/* ###--------------------------------------------------------------### */
/* function	: utl_GetVhdlName					*/
/* description	: make a legal VHDL name from a string			*/
/* called func.	:							*/
/* ###--------------------------------------------------------------### */

char *utl_GetVhdlName (name)

char *name;

  {
  char                  buf [UTL_STR__MAXLEN] ;
  char                 *legal_name            ;
  char                 *input_name            ;
  int                   number                ;
  int                   flag                  ;
  int                   i                     ;
  int                   idx                   ;
  char                  c                     ;

  static struct utdic  *input_dic             = NULL;
  static struct utdic  *legal_dic             = NULL;
  static char          *keywrd []             = {
                                                 "abs"          ,
                                                 "access"       ,
                                                 "after"        ,
                                                 "alias"        ,
                                                 "all"          ,
                                                 "and"          ,
                                                 "architecture" ,
                                                 "array"        ,
                                                 "assert"       ,
                                                 "attribute"    ,
                                                 "begin"        ,
                                                 "block"        ,
                                                 "body"         ,
                                                 "buffer"       ,
                                                 "bus"          ,
                                                 "case"         ,
                                                 "component"    ,
                                                 "configuration",
                                                 "constant"     ,
                                                 "disconnect"   ,
                                                 "downto"       ,
                                                 "else"         ,
                                                 "elsif"        ,
                                                 "end"          ,
                                                 "entity"       ,
                                                 "exit"         ,
                                                 "file"         ,
                                                 "for"          ,
                                                 "function"     ,
                                                 "generate"     ,
                                                 "generic"      ,
                                                 "guarded"      ,
                                                 "if"           ,
                                                 "in"           ,
                                                 "inout"        ,
                                                 "is"           ,
                                                 "label"        ,
                                                 "library"      ,
                                                 "linkage"      ,
                                                 "loop"         ,
                                                 "map"          ,
                                                 "mod"          ,
                                                 "nand"         ,
                                                 "new"          ,
                                                 "next"         ,
                                                 "nor"          ,
                                                 "not"          ,
                                                 "null"         ,
                                                 "of"           ,
                                                 "on"           ,
                                                 "open"         ,
                                                 "or"           ,
                                                 "others"       ,
                                                 "out"          ,
                                                 "package"      ,
                                                 "port"         ,
                                                 "procedure"    ,
                                                 "process"      ,
                                                 "range"        ,
                                                 "record"       ,
                                                 "register"     ,
                                                 "rem"          ,
                                                 "report"       ,
                                                 "return"       ,
                                                 "select"       ,
                                                 "severity"     ,
                                                 "signal"       ,
                                                 "stable"       ,
                                                 "subtype"      ,
                                                 "then"         ,
                                                 "to"           ,
                                                 "transport"    ,
                                                 "type"         ,
                                                 "units"        ,
                                                 "until"        ,
                                                 "use"          ,
                                                 "variable"     ,
                                                 "wait"         ,
                                                 "when"         ,
                                                 "while"        ,
                                                 "with"         ,
                                                 "xor"
                                                 };

	/* ###------------------------------------------------------### */
	/*   create a local dictionary. This dictionary is used to save	*/
	/* the VHDL keywords. In addition, it contains the strings	*/
	/* that has been changed into legal VHDL names and their	*/
	/* translation.							*/
	/* ###------------------------------------------------------### */

  if (input_dic == NULL)
    {
    input_dic = utl_CreateSimpleDic (UTL_DIC__MEDIUM);
    legal_dic = utl_CreateSimpleDic (UTL_DIC__MEDIUM);

    for (i=0 ; i<UTL_VHD__NAMNBR ; i++)
      {
      legal_name = utl_SaveString (keywrd [i]);

      utl_AddDicItem (input_dic, legal_name, legal_name);
      utl_AddDicItem (legal_dic, legal_name, legal_name);
      }
    }

	/* ###------------------------------------------------------### */
	/*   check if the string has already been seen. In this case,	*/
	/* just return the VHDL legal name attributed to the string	*/
	/* ###------------------------------------------------------### */

  input_name =          utl_SaveString (name);
  legal_name = (char *) utl_GetDicItem (input_dic, input_name);

	/* ###------------------------------------------------------### */
	/*   otherwise, make a legal VHDL name from the string by	*/
	/* replacing illegal characters by '_'. If two adjacent '_' are	*/
	/* found a 'v' character is inserted. If the last character is	*/
	/* '_', a '0' is added at the end of the name.			*/
	/* ###------------------------------------------------------### */

  if (legal_name == NULL)
    {
    i      = 0;
    idx    = 0;
    flag   = 1;

    c = input_name [0];
    if ((c >= '0') && (c <= '9'))
      {
      buf [0] = 'v';
      buf [1] = '_';
      buf [2] =  c ;

      i ++    ;
      idx  = 3;
      flag = 0;
      }

    while ((c = input_name [i]) != '\0')
      {
      buf [idx] = c;

      if (((c >= 'a') && (c <= 'z')) ||
          ((c >= 'A') && (c <= 'Z')) ||
          ((c >= '0') && (c <= '9'))   )
        flag = 0;
      else
        {
        if (flag == 1)
          buf [idx ++] = 'v';

        buf [idx] = '_';
        flag      =  1 ;
        }

      i   ++;
      idx ++;
      }

    if (buf [idx - 1] == '_')
      buf [idx ++] = '0';

    buf [idx] = '\0';

	/* ###------------------------------------------------------### */
	/*   check that the new name has not been already attributed to	*/
	/* another string. In such a case, add a '_number' at the end	*/
	/* of the word and check again. The number is incremented as	*/
	/* many times as needed to obtain a name that has never been	*/
	/* used.							*/
	/* ###------------------------------------------------------### */

    number     = 0;
    legal_name = utl_SaveString (buf);

    while (utl_GetDicItem (legal_dic, legal_name) != NULL)
      {
      sprintf (buf + idx, "_%d", number ++);
      legal_name = utl_SaveString (buf);
      }

    utl_AddDicItem (input_dic, input_name, legal_name);
    utl_AddDicItem (legal_dic, legal_name, input_name);
    }

  return (legal_name);
  }
