require 'RLTK/Lexer'

# Create a Lexer for the mini ML language.
class Lexer < RLTK::Lexer
  # Spaces
  rule(/\s/)

  rule(/\(\*/) { push_state :comment }

  rule(/\(\*/, :comment) { push_state :comment }
  rule(/\*\)/, :comment) { pop_state           }
  rule(/./,    :comment)

  # Ident
  rule(/[a-z][A-Z]*/) { |id|  [:IDENT, id] }
  rule(/[0-9]+/)      { |int| [:INT, int.to_i]   }

  # Keywords
  rule(/true/)  { :TRUE   }
  rule(/false/) { :FALSE  }
  rule(/fun/)   { :FUN    }
  rule(/->/)    { :ARROW  }
  rule(/if/)    { :IF     }
  rule(/then/)  { :THEN   }
  rule(/else/)  { :ELSE   }
  rule(/let/)   { :LET    }
  rule(/rec/)   { :REC    }
  rule(/in/)    { :IN     }
  rule(/=/)     { :EQUAL  }
  rule(/Nil/)   { :NIL    }
  rule(/match/) { :MATCH  }
  rule(/with/)  { :WITH   }
  rule(/\|/)    { :PIPE   }

  # Operators
  rule(/::/) { :CONS   }
  rule(/\+/) { :ADD    }
  rule(/\*/) { :MUL    }
  rule(/\-/) { :SUB    }
  rule(/<=/) { :LEQ    }
  rule(/>=/) { :GEQ    }

  # Delimiters
  rule(/\(/) { :LPAREN }
  rule(/\)/) { :RPAREN }
  rule(/,/)  { :COMMA  }
  rule(/;/)  { :SCOLON }
end
