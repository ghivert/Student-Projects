class Node
  attr_reader   :children
  attr_accessor :tag

  def initialize(terminal, tag, children = [])
    @tag = tag
    @terminal = terminal
    @children = children
  end

  def terminal?
    @terminal == true
  end

  def size
    return 1 if terminal?
    return 1 if children == []
    return 1 + children.map { |node| node.size }.reduce(:+)
  end

  def tag
    tag_them(prefix_nodes)
  end

  def depth
    return 1 if terminal?
    return 1 if children == []
    return 1 + children.map { |node| node.depth }.max
  end

  def average_depth
    sum = 0
    traverse_tree(-> (node) {
      sum += node.depth
    })
    sum / size
  end

  def generate_dot(name)
    File.open(name, "w") do |file|
      file.write("digraph tree {\n")
      traverse_tree(-> (node, out = file) {
        node.children.each do |child|
          out.write("#{node.tag} -> #{child.tag};\n")
        end
      })
      file.write("}\n")
    end
  end

  def traverse_tree(fun)
    fun.call(self)
    children.each do |node|
      node.traverse_tree(fun)
    end
  end

  private

  def prefix_nodes
    nodes, stack = @children.clone, []
    while nodes.size != 0
      stack << nodes.shift
      nodes += stack.last.children
    end
    stack
  end

  def tag_them(stack)
    i = 1
    stack.each do |node|
      node.tag = i
      i += 1
    end
  end
end
