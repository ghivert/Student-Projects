@exemple = "A quel genial professeur de dactylographie sommes-nous redevables de la superbe phrase ci-dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?"

def empty_tree
  BriandaisNode.new
end

class BriandaisNode
  attr_reader   :key
  attr_accessor :sons

  def initialize(key = nil, word = nil)
    @key   = key
    @empty = true
    @sons = []

    if word.length == 0
      @final = true
    else
      @final = false
      add_word(word)
    end if word
  end

  def add_word(word)
    if word.length == 0
      @final = true
      return 0
    end

    @sons.each do |tree|
      if tree.key == word[0]
        return tree.add_word(word[1...word.length])
      end
    end

    @sons << BriandaisNode.new(word[0], word[1...word.length])
    return 0
  end

  def to_s
    "Clé : #{@key}, fils : #{@sons.map do |s| s.to_s end}"
  end
end

tree = BriandaisNode.new
@exemple.split(' ').each do |word|
  tree.add_word word
end
puts tree.to_s
