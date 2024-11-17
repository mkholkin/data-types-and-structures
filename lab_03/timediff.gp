set arrow from graph 0,0.5 to graph 1,0.5 nohead linecolor rgb "black" lw 1
set terminal svg size 1024,768 enhanced
set output 'timedif_graphs.svg'

set xlabel 'Заполненность матрицы (%)'
set ylabel 'Разница во времени обработки (%)'
set title 'График зависимости разницы во времени обработки от заполненности матрицы'
set grid

# Устанавливаем диапазоны для осей
set xrange [0:100]
set yrange [-100:100]

# Определяем линии для разных размеров матриц
plot 'data/matrix_50x50_performance.txt' using 1:2 with linespoints title '50x50 Matrix', \
     'data/matrix_100x100_performance.txt' using 1:2 with linespoints title '100x100 Matrix', \
     'data/matrix_250x250_performance.txt' using 1:2 with linespoints title '250x250 Matrix', \
     'data/matrix_500x500_performance.txt' using 1:2 with linespoints title '500x500 Matrix', \
     'data/matrix_1000x1000_performance.txt' using 1:2 with linespoints title '1000x1000 Matrix', \
     'data/matrix_2500x2500_performance.txt' using 1:2 with linespoints title '2500x2500 Matrix', \
     'data/matrix_5000x5000_performance.txt' using 1:2 with linespoints title '5000x5000 Matrix'

unset output
