#ifndef SORTING_H
#define SORTING_H

#include "../types.h"

void selectsort_cars_by_price(car_t *cars, const size_t n);
void qsort_cars_by_price(car_t *cars, const size_t n);

void key_tbl_qsort_cars_by_price(key_price *items, const size_t n);
void key_selectsort_cars_by_price(key_price *items, const size_t n);

#endif //SORTING_H
