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
 *   comp.ml : verifie les fichiers et lance le compilateur             *
 *             independant de Java                                      *
 *                                                                      *
 *   version : 0.1           13/04/06                                   *
 *                                                                      *
 *   auteur : Emmanuel Chailloux                                        *
 *                                                                      *
 ************************************************************************)

open Prod;;
open Comp;;



let syntax () = 
  List.iter prerr_endline
    [ "usage: " ^ !compiler_name ^" -d -i -v  filename"^".ml"]
;;

let  parse_command  () = 
let max  = Array.length  Sys.argv in 
 let rec parse i = 
   if i == max then [] 
   else 
     match Sys.argv.(i) with 
      "-i" ->  verbose_mode:=true; parse(i+1)
    | "-d" ->  debug_mode:=true; parse(i+1)
    | "-v" ->  print_endline (!compiler_name ^ " " ^ !version ^ " (" ^ !date ^")");
               parse(i+1)
    |  file -> file::parse(i+1)
  in 
    parse 1
;;

let check_filename s  = 
 if Filename.check_suffix s ".ml" then
    let filename = Filename.chop_suffix s ".ml" in
    compile filename ".ml"
  else
    ( prerr_endline (s ^ " n'est pas un fichier d'extension .ml");
    prerr_endline ""; syntax())
;;

let main () = 
  let filenames = parse_command () in 
  List.iter check_filename filenames
;;


Printexc.print main (); exit 0;;

