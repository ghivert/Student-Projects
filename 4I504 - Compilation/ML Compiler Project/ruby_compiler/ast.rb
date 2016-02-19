require 'RLTK/AST'

class Expression < RLTK::ASTNode; end
class List < RLTK::ASTNode; end
class Nil < Expression; end

class Boolean < Expression
  value :value, Integer
end

class Int < Expression
  value :value, Integer
end

class Variable < Expression
  value :name, String
end

class Function < Expression
  value :args, [String]
  child :body, Expression
end

class Apply < Expression
  child :fun, Expression
  child :arg, Expression
end

class Conditionnal < Expression
  child :cond, Expression
  child :then, Expression
  child :else, Expression
end

class Matching < Expression
  child :expr, Expression
  child :list, Expression
end

class Cons < Expression
  child :head, Expression
  child :tail, Expression
end

class Binary < Expression
  child :left,  Expression
  child :right, Expression
end

class Add < Binary; end
class Mul < Binary; end
class Sub < Binary; end
class Leq < Binary; end
class Geq < Binary; end

class Let < Expression
  value :name,  String
  child :value, Expression
  child :body,  Expression
end
class Rec < Let; end

class NilList < List
  child :body, Expression
end

class ConsList < List
  child :list, Cons
  child :body, Expression
end

class FullList < List
  child :first,  NilList
  child :second, ConsList
end
