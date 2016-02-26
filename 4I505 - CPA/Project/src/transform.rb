require 'gnuplot'
require 'rubygems'
require 'gsl'

storage  = []
times_1  = []
instance = []

File.open "./results_welzl.csv" do |file|
  file.each_line do |line|
    splitted = line.split(';')
    x        = splitted[0].to_f
    y        = splitted[1].to_f
    radius   = splitted[2].to_f
    time     = splitted[3].to_f
    storage << [x, y, radius, time]
  end
end

cpt = 0
storage.each do |line|
  times_1 << line[3]
  instance << cpt
  cpt += 1
end

storage = []

File.open "./results_naive.csv" do |file|
  file.each_line do |line|
    splitted = line.split(',')
    x        = splitted[0].to_f
    y        = splitted[1].to_f
    radius   = splitted[2].to_f
    time     = splitted[3].to_f
    storage << [x, y, radius, time]
  end
end

times_2 = []

storage.each do |line|
  times_2 << line[3]
end

instance = GSL::Vector.alloc(instance)
times_1  = GSL::Vector.alloc(times_1)
times_2  = GSL::Vector.alloc(times_2)

(c0_1, c1_1, cov00_1, cov01_1, cov11_1, chisq_1, status_1) = GSL::Fit::linear(instance, times_1)
(c0_2, c1_2, cov00_2, cov01_2, cov11_2, chisq_2, status_2) = GSL::Fit::linear(instance, times_2)
times_1_fit = (instance * c1_1) + c0_1
times_2_fit = (instance * c1_2) + c0_2

Gnuplot.open do |gp|
  Gnuplot::Plot.new(gp) do |plot|

    plot.title  "Temps de calcul pour les différentes instances"
    plot.xlabel "Instances"
    plot.ylabel "Temps"

    plot.data << Gnuplot::DataSet.new([instance.to_a, times_1.to_a]) do |ds|
      ds.with = "points"
      ds.notitle
    end

    plot.data << Gnuplot::DataSet.new([instance.to_a, times_2.to_a]) do |ds|
      ds.with = "points"
      ds.notitle
    end

    plot.data << Gnuplot::DataSet.new([instance.to_a, times_1_fit.to_a]) do |ds|
      ds.with = "lines"
      ds.notitle
    end

    plot.data << Gnuplot::DataSet.new([instance.to_a, times_2_fit.to_a]) do |ds|
      ds.with = "lines"
      ds.notitle
    end

    plot.terminal "jpeg"
    plot.output "graph.jpg"
  end
end
