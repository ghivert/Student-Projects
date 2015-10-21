TASKS = [[ 35, 12, 25, 6,  76, 56, 54, 25 ],
         [ 26, 15, 41, 15, 65, 68, 42, 32 ],
         [ 13, 19, 21, 25, 51, 42, 28, 31 ]]

class Node
  def initialize(task, machine, done, time)
    @task = task
    @done = done
    @time = time
    @machine = machine
  end
  
  def lower_bound
  end
  
  def upper_bound
  end
end

class Tree  
  def generate_tree
    (0...TASKS.length).each do |i|
      (0...TASKS[0].length).each do |j|
        @nodes << new Node(j, i, [], 0)
      end
    end
  end
end

tree = new Tree
