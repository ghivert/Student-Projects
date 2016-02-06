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
 *   env_eval : environnement d'évaluation                              *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 15:35:26 $                                     *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Types;;
open Typeur;;
open Env_typeur;;

open Eval;;

let initial_eval_env = 
  let make_new_unop name = name, V_closure([], Abs("x", Unop (("_ML_"^name),Var "x"))) in 
  let new_unop = List.map make_new_unop ["hd";"tl";"fst";"snd"] 
  and s_env = 
 
 [
  "true", V_const(V_bool true);
  "false", V_const(V_bool false)
        ]
 in ref (new_unop@s_env);;

let type_check_and_eval  e = 
  let et = typing_handler type_expr !initial_typing_env e 
  in 
    let t = acces_type et in  
    let v = eval_ml_expr !initial_eval_env e 
    in 
    let qt = snd(List.hd(generalize_types !initial_typing_env ["it",t]))
    in 
      v,qt
(*print_ml_val v; print_string " : ";  print_quantified_type qt; print_newline() *)
	       ;;


