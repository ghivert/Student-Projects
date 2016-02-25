require 'benchmark'
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

      if all_covered
        if temp.radius < @circle.radius or @circle == Geometry.circleNil
          @circle = temp
        end
      end
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
        points.each do |t|
          unless temp.is_covered t
            all_covered = false
            break
          end
        end

        if all_covered
          if temp.radius < @circle.radius or @circle == Geometry.circleNil
            @circle = temp
          end
        end
      end
    end
  end
  @circle
end

tests = Dir.entries(ARGV.first)
tests.shift
tests.shift
File.open "results_naive.csv", "w" do |fh|
  fh << "x;y;radius;time\n"
  tests.each do |t|
    $stdout << t.to_s << "\n"
    points = read_points t
    circle = nil
    bench = Benchmark.realtime { circle = naive points }
    fh << circle.center.x << ";" << circle.center.y << ";" << circle.radius << ";" << bench << "\n"
    fh.flush
  end
end
