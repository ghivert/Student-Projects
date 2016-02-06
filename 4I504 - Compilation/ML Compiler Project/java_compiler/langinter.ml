(************************************************************************
 *                                                                      *
 *                       MASTER STL M1 anne'e 2005/06                   *
 *                                                                      *
 *                     Cours Compilation Avanceels                      *
 *                                                                      *
 *                       Compilation -> Langage intermediaire           *
 *                                                                      *
 *                         partie de ml2java                            *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 *   langinter.ml : langage intermediaire pour la phase de compilation  *
 *                  independant de Java                                 *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 15:35:26 $                                     *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)


open Types;;

type li_const_type = 
  INTTYPE
| FLOATTYPE
| BOOLTYPE
| STRINGTYPE
| UNITTYPE
;;

type li_type = 
  ALPHA
| CONSTTYPE of li_const_type
| PAIRTYPE
| LISTTYPE
| FUNTYPE
| REFTYPE
;;


type li_const = 
  INT of int
| FLOAT of float
| BOOL of bool
| STRING of string
| EMPTYLIST
| UNIT;;


type li_instr = 
  CONST of li_const
| VAR   of string * li_type
| IF  of li_instr * li_instr * li_instr
| PRIM of (string * li_type) * li_instr list
| APPLY of li_instr * li_instr
| RETURN of li_instr
| AFFECT of string * li_instr
| BLOCK of (string  * li_type * li_instr) list  * li_instr
| FUNCTION of string * li_type * int * (string list * li_type) * li_instr 
;;


let li_const_of_ml_const c = match c with 
  Int_type -> INTTYPE
| Float_type -> FLOATTYPE
| String_type -> STRINGTYPE
| Bool_type -> BOOLTYPE
| Unit_type -> UNITTYPE
;;

  
let  li_type_of_ml_type  t = 
  let rec aux t = match t with 
     Var_type {contents = (Unknown _)} -> ALPHA
  |  Var_type {contents = (Instanciated t)} -> aux t
  |  Const_type t -> CONSTTYPE (li_const_of_ml_const t)
  |  Pair_type (_,_) -> PAIRTYPE
  |  List_type _     -> LISTTYPE
  |  Fun_type (_,_) -> FUNTYPE
  |  Ref_type _ -> REFTYPE
in aux t
;;



