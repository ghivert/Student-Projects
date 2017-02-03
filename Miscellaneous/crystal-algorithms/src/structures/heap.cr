class Heap(T)
  def initialize(*objs, compare : T, T -> Bool = ->(x : T, y : T) { x > y })
    @compare = compare
    @heap = [0] of T
    objs.each do |i|
      self.push(i)
    end
  end

  def initialize(objs : Enumerable(T), compare : T, T -> Bool = ->(x : T, y : T) { x > y })
    @compare = compare
    @heap = [0] of T
    objs.each do |i|
      self.push(i)
    end
  end

  def initialize(obj : T, compare : T, T -> Bool = ->(x : T, y : T) { x > y })
    @compare = compare
    @heap = [0, obj]
  end

  def initialize(compare : T, T -> Bool = ->(x : T, y : T) { x > y })
    @compare = compare
    @heap = [0] of T
  end

  def add_elem(obj)
    index = (@heap << obj).size - 1
    temp = index / 2
    while index != 1 && @compare.call(@heap[temp], obj)
      @heap[temp], @heap[index], index, temp = @heap[index], @heap[temp], temp, temp / 2
    end
  end

  def push(*objs)
    objs.each do |obj|
      add_elem(obj)
    end
    self
  end

  def push(objs : Enumrable(T))
    objs.each do |obj|
      add_elem(obj)
    end
    self
  end

  def push(obj)
    add_elem(obj)
    self
  end

  def <<(obj)
    add_elem(obj)
    self
  end

  def pop
    if self.empty?
      return nil
    elsif @heap.size == 2
      return @heap.pop
    end

    result, @heap[1], index = @heap[1], @heap.pop, 1

    while 2 * index < @heap.size
     # Init locals.
     left  = 2 * index
     right = 2 * index + 1
     n_left  = @heap[left]
     n_right = right > @heap.size ? nil : @heap[right]
     n_index = @heap[index]

     if n_right.nil? # If there's no right child.
       if @compare.call(n_index, n_left)
         @heap[index], @heap[left], index = n_left, n_index, left
       else
         break
       end
     elsif @compare.call(n_index, n_left) || @compare.call(n_index, n_right)
       if @compare.call(n_right, n_left)
         @heap[index], @heap[left], index = n_left, n_index, left
       else
         @heap[index], @heap[right], index = n_right, n_index, right
       end
     else
       break
     end
   end
   result
  end

  def empty?
    return true if @heap.size == 1
    false
  end

  def size
    @heap.size - 1
  end

  def include?(obj)
    @heap[1..@heap.size].each do |elem|
      return true if elem == obj
    end
    false
  end
end
