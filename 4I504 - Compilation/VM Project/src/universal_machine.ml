exception Stop_Computation;;
exception Not_Found;;
exception Orthography_Error;;

type register = { number : int; mutable content : int; };;

class universal_machine debug_value= object (self)
  (** Emulate an entire universal machine. *)
  val registers = [| { number = 0; content = 0; };
		     { number = 1; content = 0; };
		     { number = 2; content = 0; };
		     { number = 3; content = 0; };
		     { number = 4; content = 0; };
		     { number = 5; content = 0; };
		     { number = 6; content = 0; };
		     { number = 7; content = 0; } |]

  val mutable programm : bytes array = [||]
  val mutable instructions : Interpret.instruction array = [||]

  val mutable arrays : ((int * int array) list) = []

  val mutable pc = 0
  val debug = debug_value

  method charge_file file =
    (** Load an entire file into the internal programm variable. Need to change the endianess... *)
    let rec channel_file = open_in_bin file
    and loop = fun acc ->
      let buffer = Bytes.create 4 in
      if (input channel_file buffer 0 4) = 0
      then acc
      else loop (Array.append acc [| buffer |]) in
    programm <- loop (Array.make 0 (Bytes.create 4));
    close_in channel_file

  method to_instructions () =
    (** Transform the programm into instructions directly executable. *)
    let convert = fun x ->
      let number = Interpret.bytes_to_uint x in
      let instruction = fun name ->
	Interpret.Normal (name,
			  Interpret.register Interpret.A number,
			  Interpret.register Interpret.B number,
			  Interpret.register Interpret.C number) in
      match Interpret.operator number with
	Interpret.Orthography -> Interpret.Special
				   (Interpret.Orthography,
				    Interpret.register_special number,
				    Interpret.value_special number)
      | name -> instruction name in
    instructions <- Array.map convert programm

  method find_array ?array_list:(al = arrays) num =
    match al with
    | [] -> raise Not_Found
    | hd :: tl -> match hd with
		  | (number, arr) -> if number = num
				     then arr
				     else self#find_array ~array_list:tl num

  method remove_array ?array_list:(al = arrays) num =
    match al with
    | [] -> []
    | hd :: tl ->
       match hd with
       | (number, arr) -> if number = num
			  then tl
			  else hd :: self#remove_array ~array_list:tl num

  method to_uint ?value:(value = 1) ?acc:(acc = 0) num =
    if value = 4294967296 then
      acc
    else
      self#to_uint ~value:(value * 2) ~acc:(acc + (num land value)) num


  method interpret_instruction instrn =
    let instruction = Array.get instructions instrn
    and getr = fun reg -> (Array.get registers reg).content
    and setr = fun reg num -> (Array.get registers reg).content <-
				(self#to_uint num) in
    match instruction with
    | Interpret.Normal (name, reg_a, reg_b, reg_c) ->
       (match name with
	| Interpret.Conditionnal_Move ->
	   (if debug = 1
	    then Printf.printf "Instruction : Cdm %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   (if (getr reg_c) != 0
	    then setr reg_a (getr reg_b));
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       (getr reg_a) (getr reg_b) (getr reg_c));

	| Interpret.Array_Index ->
	   (if debug = 1
	    then Printf.printf "Instruction : Ari %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   setr reg_a (Array.get (self#find_array (getr reg_b))
				 (getr reg_c));
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));

	| Interpret.Array_Amendment ->
	   (if debug = 1
	    then Printf.printf "Instruction : Ara %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   Array.set (self#find_array (getr reg_a)) (getr reg_b)
		     (getr reg_c);
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Addition ->
	   (if debug = 1
	    then Printf.printf "Instruction : Add %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   setr reg_a (((getr reg_b) + (getr reg_c)) mod 4294967296);
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Multiplication ->
	   (if debug = 1
	    then Printf.printf "Instruction : Mul %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   setr reg_a (((getr reg_b) * (getr reg_c)) mod 4294967296);
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Division ->
	   (if debug = 1
	    then Printf.printf "Instruction : Div %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   setr reg_a ((getr reg_b) / (getr reg_c));
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Not_And ->
	   (if debug = 1
	    then Printf.printf "Instruction : NtA %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   setr reg_a (lnot ((getr reg_b) land (getr reg_c)));
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Halt ->
	   (if debug = 1
	    then Printf.printf "Instruction : Hat %d %d %d\n  \
				Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   raise Stop_Computation;
	| Interpret.Allocation ->
	   (if debug = 1
	    then Printf.printf "Instruction : All %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   arrays <- List.append arrays [(getr reg_b,
					  (Array.make (getr reg_c) 0))];
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Abandonment ->
	   (if debug = 1
	    then Printf.printf "Instruction : Abd %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   arrays <- self#remove_array reg_c;
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Output ->
	   (if debug = 1
	    then Printf.printf "Instruction : Opt %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   if (getr reg_c) < 256 && (getr reg_c) > -1
	   then print_int reg_c;
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Input ->
	   (if debug = 1
	    then Printf.printf "Instruction : Ipt %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   let inpt = ref (-1) in
	   while !inpt = -1 do
	     print_string "Enter a number between 0 and 255 : ";
	     inpt := read_int ();
	     if !inpt > 255 || !inpt < 0 then
	       inpt := -1
	   done;
	   setr reg_c !inpt;
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	| Interpret.Load_Program ->
	   (if debug = 1
	    then Printf.printf "Instruction : LdP %d %d %d\n  \
				Before : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   print_string "I'm there\n";
	   (if debug = 1
	    then Printf.printf "  After  : Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!" (getr reg_a)
			       (getr reg_b) (getr reg_c));
	(*Array.set programm 0 (Array.copy (self#find_array (getr reg_b)));
	   self#to_instructions () *)
	| Interpret.Orthography ->
	   (if debug = 1

	    then Printf.printf "Instruction : Ort %d %d %d\n  \
				Content of regs : reg_a : %d
				reg_b : %d reg_c : %d\n%!"
			       reg_a reg_b reg_c
			       (getr reg_a) (getr reg_b) (getr reg_c));
	   raise Orthography_Error;
       )
    | Interpret.Special (name, reg, value) ->
       (if debug = 1
	then Printf.printf "Instruction : Ort %d %d\n  \
			    Before : Content of reg and value : %d %d\n%!"
			   reg value (getr reg) value);
       (Array.get registers reg).content <- value;
       (if debug = 1
	then Printf.printf "  After  : Content of reg : %d\n%!"
			   (getr reg));

  method launch_um file =
    (** Charge the program into memory and translated into instructions. *)
    self#charge_file file; self#to_instructions ();
    try
      while true do
	self#interpret_instruction pc;
	pc <- pc + 1
      done
    with Stop_Computation ->
      print_string "Extinction.\n"

  method print_instructions () =
    (** Print an array of instructions. *)
    Array.map (fun x ->
	       (match x with
		  Interpret.Normal (name, reg_a, reg_b, reg_c) ->
		  Printf.printf "%s %d %d %d\n"
				(match name with
				   Interpret.Conditionnal_Move -> "CdM"
				 | Interpret.Array_Index -> "ArI"
				 | Interpret.Array_Amendment -> "ArA"
				 | Interpret.Addition -> "Add"
				 | Interpret.Multiplication -> "Mul"
				 | Interpret.Division -> "Div"
				 | Interpret.Not_And -> "Nad"
				 | Interpret.Halt -> "Hat"
				 | Interpret.Allocation -> "All"
				 | Interpret.Abandonment -> "Abd"
				 | Interpret.Output -> "Opt"
				 | Interpret.Input -> "Ipt"
				 | Interpret.Load_Program -> "Ldp"
				 | Interpret.Orthography -> raise Exit)
				reg_a reg_b reg_c
		| Interpret.Special (Interpret.Orthography, reg_a, value) ->
		   Printf.printf "%s %d %d\n" "Ort" reg_a value
		| _ -> raise Exit);
	       Printf.printf "%!") instructions

  method print_programm () =
    (** Print the programm in a chain of hexadecimal numbers. *)
    Array.map (fun x -> Printf.printf "%x %x %x %x\n" (Char.code (Bytes.get x 0))
				      (Char.code (Bytes.get x 1))
				      (Char.code (Bytes.get x 2))
				      (Char.code (Bytes.get x 3))) programm

end;;

let x = new universal_machine 1;;
  x#launch_um "../reference-implementation/universal-machine.um";;
