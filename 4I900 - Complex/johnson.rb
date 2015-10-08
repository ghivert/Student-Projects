require 'ostruct'

@poids = [ [35, 12, 25, 6, 76, 56, 54, 25],
           [26, 15, 41, 15, 65, 68, 42, 32] ]
@not_1 = @poids[0].length + 1

def smallest_poids
  x = 0; y = 0; min = 1 << 31
  (0...@poids.length).each do |i|
    (0...@poids[0].length).each do |j|
      next if @poids[i][j] == -1
      next unless @poids[i][j] < min
      min = @poids[i][j]
      x = i
      y = j
    end
  end
  (0..1).each { |ind| @poids[ind][y] = -1 }
  puts "#{x}, #{y}"
  @not_1 -= 1
  OpenStruct.new(:i => x, :j => y)
end

def johnson
  g = Array.new(0); d = Array.new(0)
  while @not_1 != 0
    puts "#{@poids}"
    min = smallest_poids
    puts "#{min}"
    if min.i == 0
      g << min.j
    else
      d.unshift(min.j)
    end
  end
  g + d
end

puts "#{johnson}"
