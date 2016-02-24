require_relative 'geometry'
require_relative 'reading'

def naive(points)
  @circle = nil
  points.each do |q|
    points.each do |r|
      next if q == r
      all_covered = true
      circle = Geometry::Circle.new(Geometry.middle(q, r),
      Geometry.distance(q, r) / 2)
      points.each do |s|
        all_covered = false unless circle.is_covered s
      end
      @circle = circle if all_covered
    end
  end
  return @circle if @circle

  $stdout << "Milieu...\r"

  cpt = 0
  points.each do |q|
    $stdout << cpt.to_s << "            \r"
    cpt += 1
    points.each do |r|
      next if q == r
      points.each do |s|
        next if s == r or s == q
        all_covered = true
        circle = Geometry.circumcircle(q, r, s)
        points.each do |t|
          all_covered = false unless circle and circle.is_covered t
        end
        @circle = circle if all_covered
      end
    end
  end
  @circle
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results.txt", "w" do |fh|
  tests.each do |t|
    $stdout << t.to_s << "\r"
    points = read_points t
    circle = naive points
    if circle
      fh << t << " " << circle.center.x << " " << circle.center.y << " " << circle.radius << "\n"
    else
      fh << t << " " << "nil\n"
    end
    fh.flush
  end
end
