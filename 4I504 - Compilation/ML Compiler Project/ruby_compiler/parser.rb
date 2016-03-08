require 'RLTK/Parser'
require_relative 'AST'
require_relative 'Lexer'

class Parser < RLTK::Parser
  left :ADD
  left :MUL

  production(:beginning, 'expression') { |expr| expr }

  production(:expression) do
    clause('FUN .IDENT ARROW .expression') do |name, expr|
      Function.new([name], expr)
    end
    clause('LET .IDENT EQUAL .expression IN .expression') do |id, res, body|
      Let.new(id, res, body)
    end
    clause('LET REC .IDENT EQUAL .expression IN .expression') do |id, res, body|
      Rec.new(id, res, body)
    end

    clause('NIL')   { |null|  Nil.new            }
    clause('TRUE')  { |bool|  Boolean.new(1)     }
    clause('FALSE') { |bool|  Boolean.new(0)     }
    clause('IDENT') { |name|  Variable.new(name) }
    clause('INT')   { |value| Int.new(value)     }

    clause('expression expression')        { |expr1, expr2|   Apply.new(expr1, expr2)  }
    clause('.expression CONS .expression') { |head, tail|     Cons.new(head, tail)     }
    clause('MATCH .expression WITH .list') { |expr, list|     Matching.new(expr, list) }

    clause('.expression ADD .expression')  { |left, right|    Add.new(left, right) }
    clause('.expression MUL .expression')  { |left, right|    Mul.new(left, right) }
    clause('.expression SUB .expression')  { |left, right|    Sub.new(left, right) }
    clause('.expression LEQ .expression')  { |left, right|    Leq.new(left, right) }
    clause('.expression GEQ .expression')  { |left, right|    Geq.new(left, right) }

    clause('IF .expression THEN .expression ELSE .expression') do |cond, csq, alt|
      Conditionnal.new(cond, csq, alt)
    end
  end

  production(:list) do
    clause('PIPE NIL ARROW .expression PIPE .IDENT CONS .IDENT ARROW .expression') do |expr, head, tail, body|
      FullList.new(NilList.new(expr), ConsList.new(Cons.new(head, tail), body))
    end
    clause('NIL ARROW .expression') do |body|
      NilList.new(body)
    end
    clause('.IDENT CONS .IDENT ARROW .expression') do |head, tail, body|
      ConsList.new(head, tail, body)
    end
  end
  finalize({:use => 'parser.tbl'})
end

puts Parser.parse(Lexer.lex_file('simple.ml'), {:parse_tree => true, :accept => :all})[2]
