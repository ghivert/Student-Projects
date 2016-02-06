(************************************************************************
 *                                                                      *
 *                       MASTER STL M2 anne'e 2005/06                   *
 *                                                                      *
 *                                  Cours TEP                           *
 *                                                                      *
 *                           typeur d'un mini-ml                        *
 *                                                                      *
 *                partie de intertypeur/intereval/ml2java               *
 *                                                                      *
 ************************************************************************
 *                                                                      *
 *   intertypeur.ml : typeur interactif                                 *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 23:58:34 $               *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Util;;
open Types;;
open Alex;;
open Asyn;;
open Typeur;;
open Env_typeur;;




let main () = 
try
  let lexbuf = Lexing.from_channel stdin in 
  while true do 
    try 
      print_string "$ ";flush stdout;
      let result = Asyn.implementation  Alex.main lexbuf in
      begin
        match result with 
          Expr e ->  
            let ne,qt = type_check e in 
            begin 
              print_string "- : "; print_quantified_type qt; 
              print_newline(); flush stdout
            end
        | Decl (Let(b,s,e)) -> 
            let e = 
             (* if not b then e
              else *) (Letin(b,s,e,Var s))
            in 
              let ne,qt = type_check e in
              begin 
                print_string (s^" : "); print_quantified_type qt; 
                print_newline(); flush stdout;
                add_initial_typing_env (s,qt)
              end
      end
    with Failure "type_check" -> print_string "Erreur de typage"; print_newline()
       | Toplevel -> ()
       | Failure s -> print_string ("Erreur " ^ s); print_newline()
       | Parsing.Parse_error -> print_string "Erreur de syntaxe"; print_newline()
       | _ -> () 
  done
with End_of_file -> ();;


print_string "Master STL - M2 - Module TEP - 2005/2006 ";
print_newline();;
print_newline();;
print_string "synthetiseur de types a` la ML (avec traits imperatifs)";;
print_newline();;
print_newline();;

main ();;
