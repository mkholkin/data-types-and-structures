#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

#include "return_codes.h"
#include "types.h"

return_code process_add_car(car_t *cars, size_t *n);

return_code process_remove_car(car_t *cars, size_t *n);

void process_show_key_table(const car_t *cars, const size_t n);

void process_show_sorted_key_table(const car_t *cars, const size_t n);

void process_show_cars_table(const car_t *cars, const size_t n);

void process_show_sorted_cars_table(const car_t *cars, const size_t n);

void process_show_stat(car_t *cars, const size_t n);

void process_super_filter(const car_t *cars, const size_t n);

return_code process_load_cars(car_t *cars, size_t *n);

return_code process_save_cars(const car_t *cars, const size_t n);

#endif //PROCESS_H
