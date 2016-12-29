type register_name = A | B | C;;
type operators = Conditionnal_Move
	       | Array_Index
	       | Array_Amendment
	       | Addition
	       | Multiplication
	       | Division
	       | Not_And
	       | Halt
	       | Allocation
	       | Abandonment
	       | Output
	       | Input
	       | Load_Program
	       | Orthography;;
type instruction = Normal of operators * int * int * int
		 | Special of operators * int *int;;

let bytes_to_uint buffer =
  (** Convert a 4 length bytes to proper integer on 32 bits. *)
  ((Char.code (Bytes.get buffer 0)) lsl 24) +
    ((Char.code (Bytes.get buffer 1)) lsl 16) +
    ((Char.code (Bytes.get buffer 2)) lsl 8) +
    (Char.code (Bytes.get buffer 3));;
  
let operator buffer =
  (** Find the operator number of a 32 bits integer. *)
  match ((buffer lsr 28) land 0b1111) with
  | 0  -> Conditionnal_Move
  | 1  -> Array_Index
  | 2  -> Array_Amendment
  | 3  -> Addition
  | 4  -> Multiplication
  | 5  -> Division
  | 6  -> Not_And
  | 7  -> Halt
  | 8  -> Allocation
  | 9  -> Abandonment
  | 10 -> Output
  | 11 -> Input
  | 12 -> Load_Program
  | 13 -> Orthography
  | x  -> Printf.printf "Value too high. Error. %d" x; raise Exit;;

let register name buffer =
  (** Get the number of the desired register. Name must be A, B or C. *)
  match name with
  | A -> (buffer lsr 6) land 0b111
  | B -> (buffer lsr 3) land 0b111
  | C -> buffer land 0b111;;

let register_special buffer =
  (** Determine the number of register when special operator. *)
  (buffer lsr 25) land 0b111;;
let value_special buffer =
  (** Determine the value when special operator. *)
  buffer land 0b1111111111111111111111111;;
