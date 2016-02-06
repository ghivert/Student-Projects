type token =
  | IDENT of (string)
  | PREFIX of (string)
  | INFIX of (string)
  | INT of (int)
  | FLOAT of (float)
  | STRING of (string)
  | EOF
  | EQUAL
  | LPAREN
  | RPAREN
  | COMMA
  | MINUSGREATER
  | COLONCOLON
  | COLONEQUAL
  | SEMI
  | SEMISEMI
  | LBRACKET
  | RBRACKET
  | ELSE
  | FUNCTION
  | IF
  | IN
  | LET
  | REC
  | REF
  | THEN

val implementation :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Types.ml_phrase
