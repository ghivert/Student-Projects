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
 *   eval.ml : évaluation des expressions du langage                    *
 *                                                                      *
 *   version : $Version$     $Date: 2006/05/01 15:35:26 $                                     *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Types;;


type ml_val =
    V_const of v_mlconst
 |  V_list  of ml_val * ml_val
 |  V_pair  of ml_val * ml_val
 |  V_closure of (string * ml_val) list * ml_expr
 |  V_ref of ml_val ref

and v_mlconst = 
  V_int of int
| V_float of float
| V_bool of bool
| V_string of string
| V_emptylist
| V_unit;;

exception Rec_def;;
exception Eval_failure of string;;



let print_v_ml_const c = match c with 
  V_int i -> print_int i
| V_float f -> print_float f
| V_bool true -> print_string "true"
| V_bool false -> print_string "false"
| V_string s -> print_string ("\""^s^"\"")
| V_emptylist -> print_string "[]"
| V_unit -> print_string "()"
;;

let rec print_ml_val v = match v with 
  V_const c -> print_v_ml_const c
| V_list (t,q) -> print_ml_val t;print_string "::";print_ml_val q
| V_pair (f,s) -> print_string "(";print_ml_val f;print_string ",";
                  print_ml_val s;print_string ")"
| V_closure _ -> print_string "<valeur fonctionnelle>"  
| V_ref e -> print_string "(";print_ml_val !e; print_string " ref";print_string ")"
;;

let eval_ml_const c = match c with 
  Int i -> V_int i
| Float f -> V_float f
| Bool b -> V_bool b
| String s -> V_string s
| Emptylist -> V_emptylist
| Unit -> V_unit
;;


let rec eval_unop u v = match (u,v) with 
  ("!", V_ref v) -> !v
| ("_ML_hd", V_list(a,_)) -> a
| ("_ML_hd", V_const V_emptylist) -> raise (Eval_failure "hd")
| ("_ML_tl", V_list(_,b)) -> b
| ("_ML_tl",  V_const V_emptylist) -> raise (Eval_failure "tl")
| ("_ML_fst",V_pair(a,_)) -> a
| ("_ML_snd",V_pair(_,b)) ->  b
| (s,_) -> failwith  ("primitive unaire inconnue : "^s)
;;

let eval_binop f a b = match (f,a,b) with
  ("+",V_const(V_int a),V_const(V_int b)) -> V_const(V_int(a+b))
| ("-",V_const(V_int a),V_const(V_int b)) -> V_const(V_int(a-b))
| ("*",V_const(V_int a),V_const(V_int b)) -> V_const(V_int(a*b))

| ("/",V_const(V_int a),V_const(V_int b)) -> 
    begin
      try V_const(V_int(a/b)) with Division_by_zero -> raise (Eval_failure "Div0")
    end
|  ("=",a,b) -> V_const(V_bool(a = b))

| ("<",V_const(V_int a),V_const(V_int b)) -> V_const(V_bool(a < b))
| (">",V_const(V_int a),V_const(V_int b)) -> V_const(V_bool(a > b))
| ("<=",V_const(V_int a),V_const(V_int b)) -> V_const(V_bool(a <= b))
| (">=",V_const(V_int a),V_const(V_int b)) -> V_const(V_bool(a >= b))
| ("<",a,b) -> V_const(V_bool(a < b))
| ("+.",V_const(V_float a),V_const(V_float b)) -> V_const(V_float(a+.b))
| ("-.",V_const(V_float a),V_const(V_float b)) -> V_const(V_float(a-.b))
| ("*.",V_const(V_float a),V_const(V_float b)) -> V_const(V_float(a*.b))
| ("/.",V_const(V_float a),V_const(V_float b)) -> V_const(V_float(a/.b))

| ("^",V_const(V_string a),V_const(V_string b)) -> V_const(V_string(a^b))
| (":=",V_ref v1, v2) -> v1:=v2;V_const(V_unit)
| (s,_,_) -> failwith  ("primitive binaire inconnue : "^s)
;;


let rec eval_ml_expr  env expr = match expr with 
  Const c -> V_const (eval_ml_const c)
| Var v   -> List.assoc v env
| Pair (e1,e2) -> V_pair(eval_ml_expr env e1,eval_ml_expr env e2)
| Cons (e1,e2) -> V_list(eval_ml_expr env e1,eval_ml_expr env e2)
| Cond (e1,e2,e3) -> 
    begin
      match eval_ml_expr env e1 with 
        V_const (V_bool b) -> 
           if b then eval_ml_expr env e2 else eval_ml_expr env e3 
      |   _  -> failwith "eval_ml_expr : erreur interne : pas de bool"
    end
|  Unop (s,e) -> let v = eval_ml_expr env e in eval_unop s v
|  Binop(s,e1,e2) -> let v1 = eval_ml_expr env e1
                     and v2 = eval_ml_expr env e2 in 
                     eval_binop s v1 v2              
|  App(e1,e2) ->  
    begin
      match (eval_ml_expr env e1, eval_ml_expr env e2) with
        (V_closure(clos_env,Abs(x,body)),v) ->
                eval_ml_expr ((x,v)::clos_env) body
      |   _  -> failwith "eval_ml_expr : erreur interne : pas de fun"
    end
|  Abs(p,e)   ->  V_closure(env,expr)
|  Letin(b,s,e1,e2) ->
   if not b then 
     let v = eval_ml_expr env e1 in
       eval_ml_expr ((s,v)::env) e2
  else 
     begin
       match e1 with 
         Abs _ -> 
           let rec new_env = (s, V_closure(new_env,e1))::env
           in
             eval_ml_expr new_env e2
       |  _    -> raise Rec_def
     end
| Ref e -> let v = eval_ml_expr env e in V_ref (ref v)
| Straint(e,t) -> eval_ml_expr env e;;
    









