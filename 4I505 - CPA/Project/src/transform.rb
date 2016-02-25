temp = []

File.open "./welzl.txt" do |file|
  file.each_line do |line|
    splitted = line.split(';')
    splitted.shift
    coordinates = splitted[1]
    coordinates = coordinates.split(',')
    time = splitted[0]
    radius = splitted[2]
    x = coordinates[0][1..coordinates[0].length - 1]
    y = coordinates[1][0..coordinates[1].length - 2]
    temp << [x, y, radius, time]
  end
end

File.open "./results_welzl.csv", "w" do |file|
  temp.each do |line|
    file.printf "%10.4f;%10.4f;%10.4f;%10.4f\n", line[0], line[1], line[2], line[3]
  end
end
