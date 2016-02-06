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
 *   prodjava.ml  : traducteur LI_instr -> texte Java                   *
 *                                                                      *
 *   version : 0.1           12/04/06                                   *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Types;;
open Typeur;;
open Env_typeur;;
open Env_trans;;
open Langinter;;


(* des symboles globaux bien utiles par la suite *)

let compiler_name = ref "ml2java";;
let object_suffix = ref ".java";;

(* des valeurs pour certains symboles de env_trans *)

pair_symbol:=",";;
cons_symbol:="::";;
ref_symbol:="ref";;

(* l'environnement initial du traducteur en liaison avec la Runtime *)

let build (s,equiv)  = 
  let t = 
      try List.assoc s !initial_typing_env  
      with Not_found -> 
        failwith ("building initial_trans_env : for symbol : "^s)
  in (s,(equiv,type_instance t));;

(*
let get_param_type fun_t =  match fun_t with 
  Fun_type (Pair_type (t1,t2),tr) -> [t1;t2],tr
| Fun_type ( t1,tr) -> [t1],tr
| _ -> failwith "get_param_type"
;;
*)

initial_special_env := 
 List.map build [
      "hd","MLruntime.MLhd";
      "tl","MLruntime.MLtl";
      "fst","MLruntime.MLfst";
      "snd","MLruntime.MLsnd"
];;


initial_trans_env:= 

let alpha = max_unknown () in
[",",("MLruntime.MLpair", Fun_type (Pair_type (alpha,alpha),
                                    Pair_type (alpha,alpha)))]@
["::",("MLruntime.MLlist", Fun_type (Pair_type (alpha,alpha),
                                    List_type (alpha)))]@

(
List.map build 
     ["true" ,"MLruntime.MLtrue";
      "false","MLruntime.MLfalse";
      "+","MLruntime.MLaddint";
      "-","MLruntime.MLsubint";
      "*","MLruntime.MLmulint";
      "/","MLruntime.MLdivint";
      "=","MLruntime.MLequal";
      "<","MLruntime.MLltint";
      "<=","MLruntime.MLleint";
      ">","MLruntime.MLgtint";
      ">=","MLruntime.MLgeint";
      "^", "MLruntime.MLconcat"
      
]
)
;;

(* des fonctions d'I/O *)

let output_channel = ref stdout;;
let change_output_channel oc = output_channel := oc;;

let shift_string = String.make 256 ' ';;
let out s = output_string !output_channel s;;
let out_start s nb = out ("\n"^(String.sub shift_string 0 (2*nb))^s);;
let out_end s nb = out ("\n"^(String.sub shift_string 0 nb)^"}\n");;
let out_line s = out (s^"\n");;

let out_before (fr,sd,nb) = 
  if sd<>"" then out_start (sd^"=") nb
  else if fr then out_start ("return ") nb;;


let out_after  (fr,sd,nb) = 
  if sd<>"" then 
  begin
      out ";";
      if fr then out (("return "^sd^";"))
  end
  else if fr then out ";";;


(* des fonctions utilitaires pour commenter un peu la production *)

let header_main  s = 
  List.iter out 
   ["/**\n";
    " *  "^ s ^ ".java" ^ " engendre par ml2java \n";
    " */\n"]
;;

let footer_main  s = 
  List.iter out
   ["// fin du fichier " ^ s ^ ".java\n"]
;;

let header_one  s = 
   List.iter out
     [];;


let footer_one  s = ();;

let header_two  s = 
  List.iter out
  [ "/**\n";
    " * \n";
    " */\n";
    "class "^s^" {\n"
  ]
;;

let footer_two  s = ();;

let header_three  s = 
  List.iter out
  [  "\n\n";
     "public static void main(String []args) {\n"]
;;

let footer_three  s = 
  List.iter out
  [ "\n}}\n\n"]
;;

(* on recuoere le  type pour une declaration precise *)

let string_of_const_type ct = match ct with   
  INTTYPE    -> "MLint "
| FLOATTYPE  -> "MLdouble "
| STRINGTYPE -> "MLstring "
| BOOLTYPE   -> "MLbool "
| UNITTYPE   -> "MLunit "
;;
 
let rec string_of_type typ = match typ with 
  CONSTTYPE t -> string_of_const_type t
| ALPHA    ->  "MLvalue " 
| PAIRTYPE -> "MLpair "
| LISTTYPE -> "MLlist "
| FUNTYPE  -> "MLfun "
| REFTYPE  -> "MLref "
;;


let prod_global_var instr = match instr with
  VAR (v,t) -> out_start ("static "^"MLvalue "^(*(string_of_type t)*)v^";") 1 
| FUNCTION (ns,t1,ar,(p,t2), instr) ->
    out_start ("static MLvalue "(*"fun_"^ns^" "*)^ns^"= new MLfun_"^ns^"("^(string_of_int ar)^");") 1
| _ -> ()
;;

let prod_two  ast_li = 
  List.iter prod_global_var ast_li
;;

let get_param_type lv = 
  List.map (function (VAR(name,typ)) -> typ 
        | _ -> failwith "get_param_type" ) lv;;


let prod_const c = match c with 
  INT i -> out ("new MLint("^(string_of_int i)^")")
| FLOAT f -> out ("new MLdouble("^(string_of_float f)^")")
| BOOL b  -> out ("new MLbool("^(if b then "true" else "false")^")")
| STRING s -> out ("new MLstring("^"\""^s^"\""^")")
| EMPTYLIST -> out ("MLruntime.MLnil")
| UNIT ->      out ("MLruntime.MLlrp")
;;

let rec prod_local_var (fr,sd,nb) (v,t) = 
  out_start ("MLvalue "(*(string_of_type t)*)^v^";") nb;;

let rec prod_instr (fr,sd,nb) instr  = match instr with 
  CONST c -> out_before (fr,sd,nb);
             prod_const c;
             out_after (fr,sd,nb)
| VAR (v,t)
          -> if (nb = 0) && ( sd = "") then ()
             else 
             begin 
               out_before (fr,sd,nb);
               out v;
               out_after (fr,sd,nb)           
             end
| IF(i1,i2,i3) -> 
              out_start "if (" nb;
              out ("((MLbool)");
              prod_instr (false,"",nb) i1 ;
              out ")";
              out".MLaccess()";
              out ")";
              prod_instr (fr,sd,nb+1) i2 ;
              out_start "else" (nb);
              prod_instr (fr,sd,nb+1) i3
| RETURN i -> prod_instr (true,"",nb) i
| AFFECT (v,i) -> prod_instr (false,v,nb) i
| BLOCK(l,i) -> out_start "{ " nb;
                  List.iter (fun (v,t,i) -> prod_local_var (false,"",nb+1) 
                                           (v,t)) l;
                  List.iter (fun (v,t,i) -> prod_instr (false,v,nb+1) i) l;
                  prod_instr (fr,sd,nb+1) i;
                out_start "}" nb
             
| APPLY(i1,i2) -> 
   out_before(fr,sd,nb);
     out ("((MLfun)");
     prod_instr (false,"",nb) i1;
     out ")";
     out ".invoke(";
     prod_instr (false,"",nb) i2;     
     out")";
   out_after(fr,sd,nb)
| PRIM ((name,typ),instrl) ->
   let ltp = get_param_type instrl in 
   out_before (fr,sd,nb);
   out (name^"( ("^(string_of_type (List.hd ltp))^")");
   prod_instr (false,"",nb+1) (List.hd instrl);
   List.iter2 (fun x y -> out (",("^(string_of_type y)^")");
                        prod_instr (false,"",nb+1) x) 
            (List.tl instrl) (List.tl ltp);
   out ")" ;
   out_after(fr,sd,nb)                     

| FUNCTION _ -> ()
;;

let fun_header fn cn  = 
  List.iter out 
    ["\n\n";
     "/**\n";
     " *  de'claration de la fonction "^fn^"\n";
     " *    vue comme la classe : "^cn^"\n";
     " */ \n"]
;;

let prod_invoke cn  ar = 
  List.iter out_line 
     ["  public MLvalue invoke(MLvalue MLparam){";
      "    if (MLcounter == (MAX-1)) {"
     ];

  out "      return invoke_real(";
  for i=0 to ar-2 do 
    out ("MLenv["^(string_of_int i)^"], ")
  done;
  out_line "MLparam);";     

  List.iter out_line 
     ["    }";
      "    else {";
      "      "^cn^" l = new "^cn^"(MLcounter+1);l.MLaddenv(MLenv,MLparam); return l;";
      "    }";
      "  }"
      ]
;;

let prod_invoke_fun cn ar t lp instr = 
  out_start "MLvalue invoke_real(" 1;
  out ("MLvalue "^(List.hd lp));
  List.iter (fun x -> out (", MLvalue "^x)) (List.tl lp);
  out_line ") {";
  prod_instr (true,"",2) instr;
  
  out_start "}" 1;
  out_line ""
;;

let prod_fun instr = match instr with 
  FUNCTION (ns,t1,ar,(lp,t2),instr) -> 
      let class_name = "MLfun_"^ns in
      fun_header ns class_name ;
      out_line ("class "^class_name^" extends MLfun {");
      out_line "";
      out_line ("  private static int MAX = "^(string_of_int ar)^";") ;
      out_line "";
      out_line ("  "^class_name^"() {super();}") ;
      out_line "";
      out_line ("  "^class_name^"(int n) {super(n);}") ;      
      out_line "";
      prod_invoke class_name ar;
      out_line "";
      prod_invoke_fun class_name ar t1 lp instr;
      out_line "";           
      out_line "}";
      out_line ("// fin de la classe "^class_name)
      
      
|  _ -> ()
;;


let prod_one  ast_li = 
  List.iter prod_fun ast_li
;;




let prod_three  ast_li = 
 List.iter (prod_instr  (false,"",0) ) ast_li
;;



let prod_file filename ast_li = 
  let obj_name = filename ^ !object_suffix in 
  let oc = open_out obj_name in 
  change_output_channel oc;  
  module_name:=filename;
  try 
    header_main  filename;
    header_one  filename;
    prod_one  ast_li;
    footer_one  filename;
    header_two  filename;
    prod_two  ast_li;
    footer_two  filename;
    header_three  filename;
    prod_three  ast_li;
    footer_three  filename;
    footer_main  filename;
    close_out oc
  with x -> close_out oc; raise x;;



