#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

#include "return_codes.h"
#include "types.h"

return_code process_add_car(car_t *cars, size_t *n);
return_code process_remove_car(car_t *cars, size_t *n);
void process_show_sorted_key_table(key_price *key_tbl, size_t n);
void process_show_cars_table(const car_t *cars, size_t n);
void process_show_sorted_cars_table(car_t *cars, key_price *key_tbl, const size_t n);
return_code process_compare_methods(car_t *cars, key_price *key_tbl, size_t *n);
return_code process_compare_sort_algorithms(car_t *cars, key_price *key_tbl, size_t *n);

#endif //PROCESS_H
