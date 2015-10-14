require 'ostruct'

@weight = [ [35, 12, 25, 6,  76, 56, 54, 25],
            [26, 15, 41, 15, 65, 68, 42, 32] ]

# Find smallest weight in tabs.
def smallest_weight
  x = -1; y = -1; min = 1 << 31
  (0...@weight.length).each do |i|
    (0...@weight[0].length).each do |j|
      next if @weight[i][j] == -1
      next unless @weight[i][j] < min
      min = @weight[i][j]
      x = i
      y = j
    end
  end
  (0..1).each { |ind| @weight[ind][y] = -1 }
  OpenStruct.new(:i => x, :j => y)
end

# Apply Johnson algorithm.
def johnson
  g = []
  d = []
  loop do
    min = smallest_weight
    break if min.j == -1 && min.i == -1
    if min.i == 0
      g << min.j
    else
      d.unshift(min.j)
    end
  end
  (g + d).map { |a| a + 1 }
end

puts "#{johnson}"
