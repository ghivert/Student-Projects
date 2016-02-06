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
 *   intereval.ml : interprère interactif                               *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 15:35:26 $                                     *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Types;;
open Alex;;
open Asyn;;
open Typeur;;

open Env_typeur;;
open Intertypeur;;
open Eval;;
open Env_eval;;

open Printexc;;


let main () = 
try
  let lexbuf = Lexing.from_channel stdin in 
  while true do 
    try 
    print_string "$ ";flush stdout;
    let result = Asyn.implementation Alex.main lexbuf in  
    begin
      match result with 
        Expr e ->  let v,qt = type_check_and_eval e in 
                   begin print_string "- : "; print_quantified_type qt; 
                         print_string " = "; print_ml_val v;
                         print_newline(); flush stdout
                   end
      
      | Decl (Let(b,s,e)) -> 
          let e = 
            if not b then e 
            else (Letin(b,s,e,Var s)) in 
          begin
            let v,qt =  type_check_and_eval e in
            print_string (s^" : "); print_quantified_type qt;
            print_string " = ";print_ml_val v;
            print_newline(); flush stdout;
            initial_typing_env:=(s,qt)::!initial_typing_env;
            initial_eval_env:=(s,v)::!initial_eval_env;
          end
    end   
    with Failure "type_check" -> ()
       | Failure s -> print_string ("Exception "^(s)^" non recuperee")
       | Eval_failure s -> print_string ("Argument invalide "^s);print_newline()
       | Toplevel -> ()

    
  done
with End_of_file -> ();;



print_string "Master STL - M1 - Module CA - 2005/2006 ";
print_newline();;
print_newline();;
print_string "evaluateur d'un mini-ML";;
print_newline();;
print_newline();;

 main();;


