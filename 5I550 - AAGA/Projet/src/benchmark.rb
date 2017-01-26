require 'benchmark'
require_relative 'tree'

tree, n_times, m_times = nil, 15, 25
real_time, depth, average_depth = Array.new(30, 0), Array.new(30, 0), Array.new(30, 0)

File.open("cache_stats.txt", "w") do |file|
  file.puts "Generating trees:"
  file.puts "Size;Real Time;Depth;Average Depth"

  (2..m_times).each do |i|
    n_times.times do
      results = Benchmark.measure { tree = Tree.generate(i) }

      depth[i]         += tree.depth
      real_time[i]     += results.to_s.delete("()").split(" ")[3].to_i
      average_depth[i] += tree.average_depth

      tree = nil
    end

    depth[i]           /= n_times.to_f
    real_time[i]       /= n_times.to_f
    average_depth[i]   /= n_times.to_f

    file.puts "#{i};#{real_time[i]};#{depth[i]};#{average_depth[i]}"
  end
end
