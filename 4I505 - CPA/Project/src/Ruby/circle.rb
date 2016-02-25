require_relative 'geometry'
require_relative 'reading'

def naive(points)
  @circle = Geometry.circleNil
  points.each do |q|
    points.each do |r|
      next if q == r
      all_covered = true
      temp = Geometry::Circle.new(Geometry.middle(q, r), Geometry.distance(q, r) / 2)
      points.each do |s|
        unless temp.is_covered s
          all_covered = false
          break
        end
      end
      @circle = temp if all_covered
    end
  end
  return @circle unless @circle == Geometry.circleNil

  points.each do |q|
    points.each do |r|
      next if q == r
      points.each do |s|
        next if s == r or s == q
        all_covered = true
        temp = Geometry.circumcircle(q, r, s)
        #puts "x: #{temp.center.x}, y: #{temp.center.y}, r: #{temp.radius}"
        points.each do |t|
          unless temp.is_covered t
            all_covered = false
            break
          end
        end
        @circle = temp if all_covered
      end
    end
  end
  @circle
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results_naive.txt", "w" do |fh|
  tests.each do |t|
    $stdout << t.to_s << "\n"
    points = read_points t
    circle = naive points
    fh << t << " -- x: " << circle.center.x << ", y: " << circle.center.y << ", radius: " << circle.radius << "\n"
    fh.flush
  end
end
