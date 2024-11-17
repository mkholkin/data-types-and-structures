set terminal svg size 1024,768 enhanced
set output 'mem_graphs.svg'

set xlabel 'Количество элементов'
set ylabel 'Память (байт)'
set title 'График зависимости занимаемой памяти от количества элементов'
set grid

# Устанавливаем диапазоны для осей
set xrange [0:1000]
set yrange [0:16040]

# Определяем линии для разных размеров матриц
plot 'data/sa_queue.txt' using 1:2 with lines title 'Статический массив', \
     'data/ll_queue.txt' using 1:2 with lines title 'Связный список', \

unset output
