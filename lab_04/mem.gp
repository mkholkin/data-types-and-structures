set terminal svg size 1024,768 enhanced
set output 'mem_graphs.svg'

set xlabel 'Количество элементов'
set ylabel 'Память (байт)'
set title 'График зависимости занимаемой памяти от количества элементов'
set grid

# Устанавливаем диапазоны для осей
set xrange [0:100]
set yrange [0:1700]

# Определяем линии для разных размеров матриц
plot 'data/da_stack.txt' using 1:2 with lines title 'Динамический массив', \
     'data/sa_stack.txt' using 1:2 with lines title 'Статический массив', \
     'data/ll_stack.txt' using 1:2 with lines title 'Связный список', \

unset output
