#!/bin/bash

for (( i=1; i<=$1; i++ )); do
    x=$(shuf -i 1-999999999999 -n 1)
    ./a.out $x
done

echo "Файл успешно сгенерирован!"
