require_relative 'geometry'
require_relative 'reading'

def b_md(points)
  circle = Geometry.circleNil
  # Create the circle.
  if (points.length >= 3)
    circle = Geometry.circumcircle(points[0], points[1], points[2])
    return circle if circle == Geometry.circleNil
  elsif (points.length == 2)
    center = Geometry.middle(points[0], points[1])
    radius = Geometry.distance(points[0], center)
    return Geometry::Circle.new(center, radius);
  else
    return Geometry.circleNil
  end

  # Testing if all points are on that circle.
  points.each do |point|
    dist = point.distance(circle.center) - circle.radius
    return Geometry.circleNil if dist <= -2 and dist > 2
  end

  # The circle has passed all tests. We can return it.
  return circle;
end

def welzl(points, border=[])
  circle = Geometry.circleNil
  if points.length == 0 or border.length == 3
    circle = b_md(border)
  else
    # Random q in p.
    alea = points[rand(points.length).to_i]
    pts = points.dup; bord = border.dup
    pts.delete(alea)

    circle = welzl(pts, bord)

    bord.push(alea)
    circle = welzl(pts, bord) unless circle.contains(alea)
  end
  circle
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results_welzl.txt", "w" do |fh|
  tests.each do |t|
    $stdout << t.to_s << "\r"
    points = read_points t
    circle = welzl points
    fh << t << " -- x: " << circle.center.x << ", y: " << circle.center.y << ", radius: " << circle.radius << "\n"
  end
end
