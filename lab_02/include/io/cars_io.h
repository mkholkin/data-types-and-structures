#ifndef CARS_IO_H
#define CARS_IO_H

#include "../return_codes.h"
#include "../types.h"

return_code input_car_brand(char *str);

return_code input_car_country(char *str);

return_code input_car_foreign(bool *is_foreign);

return_code input_car_supprots_maintain(bool *supports_maintain);

return_code input_car_price(unsigned long long *price);

return_code input_car_color(car_color *color);

return_code input_car_is_new(bool *is_new);

return_code input_year(unsigned *release_year);

return_code input_car_mileage(size_t *mileage_km);

return_code input_owners_amount(size_t *owners_amount);

return_code input_repairs_amount(size_t *repairs_amount);

return_code input_car_warranty(unsigned *warranty);

return_code input_car_spec_new(car_spec_new *dst);

return_code input_car_spec_secondhand(car_spec_secondhand *dst);

return_code input_car(car_t *dst);

#endif //CARS_IO_H
