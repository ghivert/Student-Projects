require "./heap"

class MaxHeap(T) < Heap(T)
  def initialize(*objs, compare : T, T -> Bool = ->(x : T, y : T) { x < y })
    @compare = compare
    @heap = [0] of T
    objs.each do |i|
      self.push(i)
    end
  end

  def initialize(objs : Enumerable(T), compare : T, T -> Bool = ->(x : T, y : T) { x < y })
    @compare = compare
    @heap = [0] of T
    objs.each do |i|
      self.push(i)
    end
  end

  def initialize(obj : T, compare : T, T -> Bool = ->(x : T, y : T) { x < y })
    @compare = compare
    @heap = [0, obj]
  end

  def initialize(compare : T, T -> Bool = ->(x : T, y : T) { x < y })
    @compare = compare
    @heap = [0] of T
  end
end
