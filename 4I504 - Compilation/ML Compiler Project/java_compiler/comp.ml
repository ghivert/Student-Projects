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
 *   comp.ml : assemblage des phases de la compilation                  *
 *                                                                      *
 *   version : 0.1           12/04/06                                   *
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
open Env_trans;;
open Lift;;
open Trans;;
open Prod;;  (* ici ce sera un lien sur prodjava *)

(* des symboles globaux bien utiles par la suite *)

let version = ref "0.1";;
let date = ref "13/04/2006";;


(* deux modes de compilation pour tracer un peu ce qui se passe *)
let verbose_mode = ref false;;
let debug_mode = ref false;;


(* la classique fonction flat qui applatit une liste *)
let flat l = List.fold_left (fun x y -> x@y) [] l;;

(* la fonction de compilation d'une phrase qui fait dans l'ordre : 
      typage
      \-lifting (glabalisation des fonctions)
      traduction en langage interme'diaire

      les expressions globales deviennent des declarations globales
*)
     
      
let rec translate_phrase  phr = match phr with 
  Expr e ->
    (translate_phrase  (Decl(Let(false,(*new_name*)(decl_name),e))))
| Decl (Let(b,s,e)) -> 
    if b then 
      initial_typing_env:=(s,Forall([],new_unknown()))::!initial_typing_env;
    let et,qt = type_check e in 

    if b then  begin 
       let ite = (List.tl !initial_typing_env) in
       let (Forall (_, ti)) = qt in 
       let new_elt  = List.hd(generalize_types ite [s,ti]) in   
       initial_typing_env:=new_elt:: ( List.tl !initial_typing_env)
    end
    else initial_typing_env:=(s,qt)::!initial_typing_env;

    if !verbose_mode then print_string "+";
      let _ (* e1 *)= acces_expr et
      and t1 = acces_type et in 
        let l2,e2 = lift et in 
          ( ( translate_fun_decl l2))@
            (translate_decl  b s e2 t1 )
;;



(* la fonction de compilation de toutes les phrases du fichier d'entree :
 *    pour chaque phrase *)

let compile filename suffix = 
  let source_name = filename ^ suffix in 
  let ic = open_in_bin source_name in
  let lexbuf = Lexing.from_channel ic  in  

  module_name:=filename;

  if !verbose_mode then 
  begin 
    print_endline "Analyse syntaxique (.)";
    print_endline "Typage (+)";
    print_endline "Traduction vers LI (*)";
    print_newline()
  end;

  let instructions = ref [] in
  try 
    while true do 
      let ast = parse_impl_phrase lexbuf in 
      if !verbose_mode then print_string ".";
      instructions:=(translate_phrase(ast))::!instructions    done
  with 
    End_of_file ->
    begin 
      close_in ic;
      instructions:= List.rev (!instructions);
      prod_file filename (flat !instructions)
    end
  | x -> (close_in ic; raise x)
;;





  
