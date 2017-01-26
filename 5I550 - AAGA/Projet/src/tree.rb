require_relative 'node'
require_relative 'math'

class Tree
  def initialize(nodes)
    @nodes = nodes
  end

  def size
    return 0 if @nodes.nil?
    return @nodes.size
  end

  def tag
    @nodes.tag
    self
  end

  def depth
    return 0 if @nodes.nil?
    return @nodes.depth
  end

  def average_depth
    return 0 if @nodes.nil?
    return @nodes.average_depth
  end

  def generate_dot(filename)
    @nodes.generate_dot(filename)
  end

  def self.generate(size, to_tag = true)
    tree = Tree.new(generate_rec(size))
    tree.tag if to_tag
    tree
  end

  private

  def self.generate_rec(size)
    case size
    when 0 then raise Error('ask zero size')
    when 1 then return Node.new(true, -1)
    when 2 then return Node.new(false, -1, [Node.new(true, -1)])
    end

    random, k, i = rand(Calc.g(size) - 1), 1, 0

    while k < size
      tmp = Calc.inner_sum(size - 1, k)
      break unless (random - tmp > 0)
      random, k = random - tmp, k + 1
    end

    compos = Calc.composition(size - 1, k)

    while i < compos.size
      tmp = Calc.compo_product(compos[i], size - 1)
      break unless (random - tmp > 0)
      random, i = random - tmp, i + 1
    end

    children = compos[i] ? compos[i].map { |w| generate_rec(w) } : []
    Node.new(false, -1, children)
  end
end
