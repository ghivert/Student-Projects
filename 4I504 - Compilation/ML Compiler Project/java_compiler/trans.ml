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
 *   trans.ml : traduction ml_expr -> li_instr                          *
 *                                                                      *
 *   version : 0.1           11/04/06                                   *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Util;;
open Types;;
open Typeur;;
open Env_trans;;
open Langinter;;


(* fonctions utilitaires sur les noms des symboles pour les expressions
 *  globales 
 *)



let decl_name = decl_symbol;;

let is_decl_name s = 
  if string_length s < string_length decl_name then false
  else 
     (sub_string s 0 (string_length decl_name)) = decl_name 
;;


(* des fonctions utilitaires sur les expressions et leurs types *)

(* suis-je une abstraction? *)

let rec is_abs e = match e with 
  Abs(_,_) -> true
| Straint(e,t) -> is_abs e 
| _ -> false;;

(* mon type est-il fonctionnel? *)

let is_fun t = match t with 
  Fun_type _ -> true
|  _ -> false
;;

let param_type t = match t with 
  Fun_type (t1,t2) -> t1
| _ -> failwith "param_type : cas impossible d'un type non fonctionnel"
;;

(* 
 * le traducteur ml_expr -> li_instr
 *     translate_const : pour les constantes
 *     instr_of_expr   : pour tenir compte des flags : return et decl
 *     translate_expr : la fonction principale
 *)

let translate_const  e = match e with
  Int i -> INT i
| Float f -> FLOAT f
| String s -> STRING s
| Bool b -> prerr_endline "bool ***";BOOL b
| Unit  -> UNIT 
| Emptylist -> EMPTYLIST 
;;


let type_pair (t1,t2) = Pair_type(t1,t2);;



(* traduction d'une ml_const en li_const *)
 
let instr_of_expr flags i = match flags with 
  (false,"") -> i
| (true,"") -> RETURN i
| (false,s) -> AFFECT(s,i)
| (_,_)  -> failwith "instr_of_expr : cas impossible"
;;

                     
(* 
   la grande fonction qui convertit une ml_expr en li_instr
     d'une expression mini-ML en instruction du langage interme'diaire

   traduit toutes les expressions sauf les lambdas, qui ont e'te' 
   globalise'es et sont traduites par ailleurs.

   gamma : l'environnement
      fr : est-ce  return
      sd : le nom d'une decl 
       t : le type de l'expression
*)

let rec translate_expr (gamma,fr,sd,t)  e  = match e with 
  Const c -> instr_of_expr (fr,sd) (CONST(translate_const c))
| Var v   -> ( try 
                 let w,t = assoc v gamma in 
                 let w = 
                 if (List.mem_assoc v !initial_trans_env) &&
                    (is_fun t)
                 then (!module_name)^"."^w
                 else w
                 in
                 instr_of_expr (fr,sd) (VAR(w , li_type_of_ml_type t))
               with Not_found -> failwith ("translate_expr : "^v^" unknown")
             )

| Unop (s,e) -> 
  begin
    let w,t =  ( try assoc s gamma  
                 with Not_found -> 
                   failwith ("translate_expr : "^s^" unknown in Binop"))
    in
     let lit = li_type_of_ml_type t in
     let (v1,t1,i1) as l1  = open_block (gamma,"") e in
        BLOCK([l1], instr_of_expr (fr,sd) 
                           (PRIM((w,lit),[VAR(v1,t1)])))
  end
| Binop (s,e1,e2) -> 
  begin
    let w,t =  ( try assoc s gamma  
                 with Not_found -> 
                   failwith ("translate_expr : "^s^" unknown in Binop"))
    in
     let lit = li_type_of_ml_type t in
     let (v1,t1,i1) as l1  = open_block (gamma,"") e1
     and (v2,t2,i2) as l2  = open_block (gamma,"") e2 in
        BLOCK((l1::[l2]), instr_of_expr (fr,sd) 
                           (PRIM((w,lit),[VAR(v1,t1);VAR(v2,t2)]))) 
  end
| Pair (e1,e2)  -> translate_expr (gamma,fr,sd,t) (Binop(!pair_symbol,e1,e2))
| Cons (e1,e2)  -> translate_expr (gamma,fr,sd,t) (Binop(!cons_symbol,e1,e2))
| Cond(e1,e2,e3) -> let (v1,t1,i1) as l1  = open_block (gamma,"") e1 
                    and (v2,t2,i2) as l2  = open_block (gamma,"") e2
                    and (v3,t3,i3) as l3  = open_block (gamma,"") e3 in 
                    BLOCK([l1], 
                       IF(VAR(v1,t1),
                          BLOCK([l2], instr_of_expr (fr,sd) (VAR(v2,t2))),
                          BLOCK([l3], instr_of_expr (fr,sd) (VAR(v3,t3)))))
| Abs(s,e) -> failwith ("translate_expr :  abstraction anonyme")
| App(e1,e2) -> 
  begin
   let (v1,t1,i1) as l1  = open_block (gamma,"") e1
   and (v2,t2,i2) as l2  = open_block (gamma,"") e2 in
      BLOCK((l1::[l2]), instr_of_expr (fr,sd) 
                         (APPLY(VAR(v1,t1),VAR(v2,t2)))) 
  end
| Letin(b,v,e1,e2) -> 
    if is_abs e1 then failwith "translate_expr : Letin : fun"
    else
    begin
      if b then failwith ("recursive definition in no functional value")
      else
        let (v1,t1,i1) as l1 = open_block (gamma,v) e1 in 
        BLOCK([l1], translate_expr ( (v,(v1,(acces_type e1)))::gamma,
                                      fr,sd,t) e2)
    end
| Ref e -> translate_expr (gamma,fr,sd,t) (Unop(!ref_symbol,e))
| Straint(e,t) -> translate_expr (gamma,fr,sd,t)  e  
and 
 open_block  (gamma,sd)  e  = 
   let v = if sd = "" then new_temp() else new_name sd in   
   let t = acces_type e in 
   let nt = li_type_of_ml_type t in 
   let i = translate_expr (gamma,false,v,t) e in
     (v,nt,i)
;;




(* quelsques fonctions utilitaires pour connaitre : 
     count_param : le nombre d'arguments
     name_param  : le nm des parame`tres
     body_expr   : le corps de la fonction
     body_type   : le type du corps (re'sultat)
     
*)

let rec count_param e = match e with 
  Abs(s,e1) -> 1 + count_param e1
| Straint (e1,t) -> count_param e1
|  _ -> 0;;

let rec name_param e = match e with 
  Abs(s,e1) -> s:: name_param e1
| Straint (e1,t) -> name_param e1 
|  _ -> [];;

let rec body_expr e = match e with 
  Abs(s,e) -> body_expr e
| Straint(e,t) -> body_expr e 
|  _ -> e
;;

let  body_type e t = 
  let rec aux e t = match e with 
    Abs(s,e) -> aux e (acces_type e)
  | Straint(e,t) -> aux e t 
  |  _ -> t
  in aux e t
;;

let rec body_env l e t = match e,t with 
  (Abs(s,e),Fun_type (t1,t2)) -> (s,((List.hd l),t1))::body_env (List.tl l) e t2
| (Straint(e,t),_) -> body_env l e t 
|    _ -> []
;;
 
(* 
 * fonction principale de traduction des fonctions 
 *   met a` jour l'environnement de traduction
 *)

let translate_fun_decl l =
  let rec aux one = match one with 
     Expr e -> failwith "translate_fun_decl : no fun "
  |  Decl (Let(b,s,e)) -> 
       let ns = new_name s in 
         let t = (acces_type e) in 
         let ti = li_type_of_ml_type t in
           if b then add_trans_env (s,(ns,t));
         let arity = count_param e in
         let lparam = name_param e in 
         let new_lparam = map (fun x -> new_name x) lparam in 
         let body = body_expr e in 
         let _ (* rtype *) = body_type e in 
           let r = FUNCTION(ns,ti,arity, (new_lparam,ti),
             translate_expr ((body_env new_lparam e t) @ 
                              ((!initial_trans_env)@(!initial_special_env)),
                             true,"",t) body)
           in 
             if not b then add_trans_env (s,(ns,t));
             r 
 in 
  (map (aux) l)
;; 

let translate_nofun_decl v e t = 
  let gamma = (!initial_trans_env)@(!initial_special_env) in 
  let w = new_name v in 
  let ti = li_type_of_ml_type t in 
  let r = [VAR (w,ti);translate_expr (gamma,false,w,t) e]
  in 
    add_trans_env (v,(w,t));
    r
@(
   if true then 
     let w2 = new_name "bidon" in 
     [BLOCK([w2,CONSTTYPE UNITTYPE,CONST UNIT],AFFECT(w2,PRIM(("MLruntime.MLprint", ti),[VAR(w,ALPHA)])))]
   else []
);;

let translate_decl b s e t = 
  if is_abs e then translate_fun_decl [Decl(Let(b,s,e))]
  else translate_nofun_decl s e t
;;

 

let main_decl = ref ([]: (string * ml_expr * ml_type) list);;
let add_main_decl name expr typ = main_decl := (name,expr,typ)::!main_decl;;
let init_main_decl () = main_decl := [];;
let empty_main_decl () = if !main_decl = [] then true else false;;
let get_main_decl () = !main_decl;;







