require_relative 'geometry'
require_relative 'reading'

def b_md(r)
  circle = nil
  # Create the circle.
  if (r.length >= 3)
    circle = Geometry.circumcircle(r[0], r[1], r[2])
    return unless circle
  elsif (r.length == 2)
    center = Geometry::Point.new((r[0].x + r[1].x) / 2, (r[0].y + r[1].y) / 2)
    radius = r[0].distance(center);
    return Geometry::Circle.new(center, radius);
  else
    return
  end

  radius = circle.radius
  center = circle.center

  # Testing if all points of R are on that circle.
  r.each do |point|
    dist = point.distance(center) - radius
    return unless dist > -2 && dist < 2
  end

  # The circle has passed all tests. We can return it.
  return circle;
end

def welzl(pa, r=[])
  d = nil
  if pa.length == 0 or r.length == 3
    d = b_md(r)
  else
    # Random q in p.
    alea = pa[rand(pa.length).to_i]
    z = pa.dup
    z.delete(alea)
    s = r.dup
    d = welzl(z, s)
    s.push(alea)
    if not d
      d = welzl(z, s)
    elsif not d.contains(alea)
      d = welzl(z, s)
    end
  end
  d
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results.txt", "w" do |fh|
  tests.each do |t|
    $stdout << t.to_s << "\r"
    points = read_points t
    circle = welzl points
    if circle
      fh << t << " " << circle.center.x << " " << circle.center.y << " " << circle.radius << "\n"
    else
      fh << t << " " << "nil\n"
    end
  end
end
