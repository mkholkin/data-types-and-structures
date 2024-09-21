#include "../../include/io/cars_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/options.h"
#include "../../include/io/io.h"
#include "../../include/io/validators.h"


return_code input_car_brand(const char **brand)
{
    printf("Enter brand:\n");
    return input_option(brand, BRAND_OPTIONS, N_BRAND_OPTIONS, true);
}

return_code input_car_country(const char **country)
{
    printf("Enter country:\n");
    return input_option(country, COUNTRY_OPTIONS, N_COUNTRY_OPTIONS, true);
}

return_code input_car_supports_maintain(bool *supports_maintain)
{
}

return_code input_car_price(unsigned long long *price)
{
    char buf[] = {0};

    const return_code rc = input_until_valid("Enter price: ", buf, 123, validate_price);
    if (rc == OK)
        *price = strtoull(buf,NULL, 10);

    return rc;
}

return_code input_car_color(const char * *color)
{
    return input_option(color, COLOR_OPTIONS, N_COLOR_OPTIONS, true);
}

return_code input_car_is_new(bool *is_new)
{
}

return_code input_year(unsigned *release_year)
{
    char buf[10];

    const return_code rc = input_until_valid("Enter release year: ", buf, 123, validate_year);
    if (rc == OK)
        *release_year = strtoul(buf, NULL, 10);

    return rc;
}

return_code input_car_mileage(size_t *mileage_km)
{
    char buf[10];

    const return_code rc = input_until_valid("Enter mileage: ", buf, 123, validate_mileage);
    if (rc == OK)
        *mileage_km = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_owners_amount(size_t *owners_amount)
{
    char buf[10];

    const return_code rc = input_until_valid("Enter owners amount: ", buf, 123, validate_owners_amount);
    if (rc == OK)
        *owners_amount = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_repairs_amount(size_t *repairs_amount)
{
    char buf[10];

    const return_code rc = input_until_valid("Enter repairs amount: ", buf, 123, validate_repairs_amount);
    if (rc == OK)
        *repairs_amount = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_car_warranty(unsigned *warranty)
{
    char buf[10];

    const return_code rc = input_until_valid("Enter warranty period (years): ", buf, 123, validate_warranty);
    if (rc == OK)
        *warranty = strtoul(buf, NULL, 10);

    return rc;
}

return_code input_car_spec_new(car_spec_new *dst)
{
    return input_car_warranty(&dst->warranty);
}

return_code input_car_spec_secondhand(car_spec_secondhand *dst)
{
    return_code rc = input_year(&dst->release_year);

    if (rc == OK)
        rc = input_car_mileage(&dst->mileage_km);

    if (rc == OK)
        rc = input_owners_amount(&dst->owners_amount);

    if (rc == OK)
        rc = input_repairs_amount(&dst->repairs_amount);

    return rc;
}

return_code input_car(car_t *dst)
{
    return_code rc = input_car_brand(&dst->brand);

    if (rc == OK)
        rc = input_car_country(&dst->country);

    if (rc == OK)
        dst->is_foreign = strcmp(dst->country, "Russia");

    if (rc == OK && dst->is_foreign)
        rc = input_car_supports_maintain(&dst->supports_maintain);

    if (rc == OK)
        rc = input_car_price(&dst->price);

    if (rc == OK)
        rc = input_car_color(&dst->color);

    if (rc == OK)
        rc = input_car_is_new(&dst->is_new);

    if (rc == OK)
    {
        if (dst->is_new)
            rc = input_car_spec_new(&dst->spec.new);
        else
            rc = input_car_spec_secondhand(&dst->spec.secondhand);
    }

    return rc;
}
