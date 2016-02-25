require 'benchmark'
require_relative 'geometry'
require_relative 'reading'

def b_md(points)
  # Create the circle.
  if (points.length >= 3)
    Geometry.circumcircle(points[0], points[1], points[2])
  elsif (points.length == 2)
    center = Geometry.middle(points[0], points[1])
    radius = Geometry.distance(points[0], center)
    Geometry::Circle.new(center, radius)
  elsif (points.length == 1)
    Geometry::Circle.new(points[0], 0)
  end
end

def welzl(points, border=[])
  points = points.dup
  border = border.dup
  circle = Geometry.circleNil

  if points.length == 0 or border.length == 3
    circle = b_md(border)
  else
    # Random q in p.
    alea = rand(points.length).to_i
    point = points[alea]
    points.delete_at(alea)

    circle = welzl(points, border)

    if not circle or not circle.contains(point)
      border.push(point)
      circle = welzl(points, border)
    end
  end
  circle
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results_welzl.csv", "w" do |fh|
  fh << "x;y;radius;time\n"
  tests.each do |t|
    $stdout << t.to_s << "\r"
    points = read_points t
    circle = nil
    bench = Benchmark.realtime { circle = welzl points }
    fh << circle.center.x << ";" << circle.center.y << ";" << circle.radius << ";" << bench << "\n"
    fh.flush
  end
end
