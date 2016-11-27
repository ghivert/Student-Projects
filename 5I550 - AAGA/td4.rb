require 'readline'
require 'pry'

class WeightedException < Exception; end

class Node
  attr_accessor :index, :left, :right, :parent

  # Class methods.
  def self.sum_weights(node)
    sum, fifo = 0, [node]
    while !fifo.empty?
      node = fifo.shift
      next if node.nil?
      sum += node.weight
      fifo.push(node.left, node.right)
    end
    sum
  end

  def self.random_weighted(node)
    rnd, fifo = rand(sum_weights(node)), [node]
    while !fifo.empty?
      node = fifo.shift
      next if node.nil?
      return node if rnd < node.weight
      rnd -= node.weight
      fifo.push(node.left, node.right)
    end
    raise WeightedException
  end

  def self.set_parent(node, child)
    if !node.parent.nil?
      if node.parent.left == child
        node.parent.left = node
      else
        node.parent.right = child
      end
    end
  end

  # Instance methods.
  def initialize(ind, left: nil, right: nil, parent: nil)
    @index  = ind
    @left   = left
    @right  = right
    @parent = parent
  end

  def weight
    return 3 if left.nil? && right.nil?
    return 2 if left.nil? || right.nil?
    return 1
  end

  def to_s
    index
  end
end

class Tree
  def self.to_a(node)
    fifo, ret = [node], []
    while !fifo.empty?
      node = fifo.shift
      ret << node
      next if node.nil?
      fifo.push(node.left, node.right)
    end
    ret
  end

  def self.generate_incomplete(n)
    return nil if n == 0
    ind, tree = 2, Node.new(1)
    while ind <= n
      puts "#{Tree.to_a(tree).map { |x| x.to_s }}"
      node = Node.random_weighted(tree)
      puts "#{node.index}"
      case node.weight
      when 3
        case rand(3)
        when 0
          puts 1
          node.left  = Node.new(ind, parent: node)
        when 1
          puts 2
          node.right = Node.new(ind, parent: node)
        when 2
          puts 3
          if rand(2) == 0
            puts 3.5
            temp = Node.new(ind, left: node, parent: node.parent)
            tree = temp if node.parent.nil?
            Node.set_parent(temp, temp.left)
            node.parent = temp
          else
            puts 3.7
            temp = Node.new(ind, right: node, parent: node.parent)
            tree = temp if node.parent.nil?
            Node.set_parent(temp, temp.right)
            node.parent = temp
          end
        end
      when 2
        case rand(2)
        when 0
          puts 4
          if node.left.nil?
            node.left = Node.new(ind, parent: node)
          else
            node.right = Node.new(ind, parent: node)
          end
        when 1
          puts 5
          if rand(2) == 0
            puts 5.3
            temp = Node.new(ind, left: node, parent: node.parent)
            tree = temp if node.parent.nil?
            Node.set_parent(temp, temp.left)
            node.parent = temp
          else
            puts 5.6
            temp = Node.new(ind, right: node, parent: node.parent)
            tree = temp if node.parent.nil?
            Node.set_parent(temp, temp.right)
            node.parent = temp
          end
        end
      when 1
        puts 6
        if rand(2) == 0
          puts 6.3
          temp = Node.new(ind, left: node, parent: node.parent)
          tree = temp if node.parent.nil?
          Node.set_parent(temp, temp.left)
          node.parent = temp
        else
          puts 6.6
          temp = Node.new(ind, right: node, parent: node.parent)
          tree = temp if node.parent.nil?
          Node.set_parent(temp, temp.right)
          node.parent = temp
        end
      end
      ind += 1
    end
    tree
  end
end

puts "#{Tree.to_a(Tree.generate_incomplete(9)).map { |x| x.to_s }}"
