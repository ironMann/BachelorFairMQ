set terminal png size 5000, 800
set output "heatmap.png"
# size ratio 1.0
set title "Heatmap: memory size of EPNs with schedAlg "

set xlabel "seconds"
set ylabel "EPN number:"

set tic scale 0

#set size 1.0,0.7

set palette rgbformulae -7, 2, -7

set pm3d interpolate 0,0


set cbrange [0:4]
set cbtics 1
#unset cbtics

set xtics 10
set ytics 1

set xrange [0:770]
set yrange [-0.5:2.5]

set view map

splot 'schedalg.txt' matrix with image
