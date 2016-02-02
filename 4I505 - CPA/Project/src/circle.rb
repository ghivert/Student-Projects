require_relative 'geometry'
require_relative 'reading'

def naive
  points = read_points
  points.each do |q|
    points.each do |r|
      all_covered = true
      circle = Geometry::Circle.new(Geometry.middle(q, r),
      Geometry.distance(q, r) / 2)
      points.each do |s|
        all_covered = false unless circle.is_covered s
      end
      return circle if all_covered
    end
  end

  points.each do |q|
    points.each do |r|
      points.each do |s|
        all_covered = true
        circle = Geometry.circumcircle(q, r, s)
        points.each do |t|
          all_covered = false unless circle.is_covered s
        end
        return circle if all_covered
      end
    end
  end
end
