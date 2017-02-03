require "../spec_helper"

describe "Heap" do
  numbers = [] of Int32
  100.times { numbers << rand(100) }

  describe "#empty?" do
    it "is empty when no elements have been added" do
      heap = Heap(Int32).new
      heap.empty?.should be_true
    end

    it "is not empty when one or more elements have been added" do
      heap = Heap(Int32).new
      heap.push(rand(100))
      heap.empty?.should be_false

      heap = Heap(Int32).new(rand(100), rand(100))
      heap.empty?.should be_false
    end

    it "preserves its state after adding and removing one element" do
      heap = Heap(Int32).new
      heap.push(rand(100))
      heap.empty?.should be_false
      heap.pop
      heap.empty?.should be_true
    end
  end

  describe "#size" do
    it "correctly reports the number of elements in the heap" do
      Heap.new(numbers).size.should eq numbers.size
      Heap(Int32).new.size.should eq 0
    end
  end

  describe "#pop" do
    it "returns nil if heap is empty" do
      heap = Heap(Int32).new
      heap.pop.should be_nil
    end

    it "returns the first value" do
      temp = rand(100)
      Heap.new(temp).pop.should eq temp
    end
  end

  describe "#push" do
    it "returns self" do
      heap = Heap.new(rand(100))
      heap.push(rand(100)).should eq heap
    end

    it "pushes object in the heap" do
      heap = Heap(Int32).new
      temp = rand(100)
      heap.push(temp)
      heap.include?(temp).should be_true
    end
  end

  describe "#include?" do
    it "is false if heap is empty" do
      Heap(Int32).new.include?(rand(100)).should be_false
    end

    it "is false if heap does not contains the object" do
      temp = rand(100)
      Heap.new(temp + 1).include?(temp).should be_false
    end

    it "is true if the heap contains the object" do
      temp = rand(100)
      heap = Heap.new(temp)
      heap.include?(temp).should be_true

      5.times { heap << rand(100) }
      temp = rand(100)
      heap.push(temp).include?(temp).should be_true
    end
  end
end

describe "MinHeap" do
  numbers = [] of Int32
  100.times { numbers << rand(100) }

  it "pop the smallest element" do
    heap = MinHeap.new(numbers)
    s_numbers = numbers.sort
    heap.pop.should eq s_numbers[0]
    heap.pop.should eq s_numbers[1]
    heap.pop.should eq s_numbers[2]
  end
end

describe "MaxHeap" do
  numbers = [] of Int32
  100.times { numbers << rand(100) }

  it "pop the highest element" do
    heap = MaxHeap.new(numbers)
    s_numbers = numbers.sort
    heap.pop.should eq s_numbers[-1]
    heap.pop.should eq s_numbers[-2]
    heap.pop.should eq s_numbers[-3]
  end
end
