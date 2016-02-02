require_relative 'geometry'

# Read all points from the file given in parameter. Stock in array.
def read_points
  points = []

  File.open ARGV[0] do |file|
    file.each_line do |line|
      coordinates = line.split(' ').map { |x| x.to_i }
      points << Geometry::Point.new(coordinates[0], coordinates[1])
    end
  end
  points
end
