


print "processing start\n"

[["guitar", 9.467], ["mbira", 0.158], ["speech", 0.986]].each do |name, offset_sec|
  [["8k", 8000], ["8to48k",48000], ["16k", 16000], ["48k", 48000]].each do |suffix, rate|
      offset = rate * offset_sec
      duration = rate * 0.032
      print "processing ./sounds/#{name}_#{suffix}.dat #{duration} #{offset}\n"
    `./myDFT ./sounds/#{name}_#{suffix}.dat #{offset} #{duration} > ./dat/#{name}_#{suffix}.dat`
      gnuplot = <<EOS
set terminal png
set output "./output/#{name}_#{suffix}.png"
plot "./dat/#{name}_#{suffix}.dat"
EOS

      open ("plot.gnuplot","w") {|f|
        f.puts gnuplot
      }
      `gnuplot plot.gnuplot`
      print "plotted"
 
	end	
end

