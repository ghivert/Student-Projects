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
 *   env_trans : environnement de traduction                            *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 15:35:26 $                                     *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Types;;

let temp_symbol = "T";;
let expr_symbol = "E";;
let fun_symbol  = "F";;
let anon_symbol = "A";;

let ml_prefix   = "ML";;
let decl_symbol = "value";;

let gensym_var = 
  let c = ref 0 in 
  function s -> 
    c:=!c+1;
    s^"___"^(string_of_int !c)
;;

let module_name = ref "noname";;
let new_temp ()     = gensym_var temp_symbol;;
let new_name s      = gensym_var s;;
let new_clos_name s = gensym_var s;;
let clos_name name = (!module_name)^"."^(gensym_var name);;
let anon_name () = gensym_var anon_symbol;;


let pair_symbol = ref ",";;
let cons_symbol = ref "::";;
let ref_symbol =  ref "ref";;

let initial_trans_env = 
ref( [] : (string * (string * ml_type)) list )
;;

let initial_special_env = ref (!initial_trans_env);;

let add_trans_env (a,b) = initial_trans_env:=(a,b):: !initial_trans_env;;

let type_unit = Const_type Unit_type;;



