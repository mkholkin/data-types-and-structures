#include "../../include/io/cars_io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/defines.h"
#include "../../include/options.h"
#include "../../include/io/io.h"
#include "../../include/io/validators.h"


return_code input_car_brand(char *brand)
{
    const char *user_choice;
    printf("Enter brand:\n");

    const return_code rc = input_option(&user_choice, BRAND_OPTIONS, N_BRAND_OPTIONS, true);
    if (rc == OK)
        strcpy(brand, user_choice);

    return rc;
}

return_code input_car_country(char *country)
{
    const char *user_choice;
    printf("Enter country:\n");

    const return_code rc = input_option(&user_choice, COUNTRY_OPTIONS, N_COUNTRY_OPTIONS, true);
    if (rc == OK)
        strcpy(country, user_choice);

    return rc;
}

return_code input_car_supports_maintain(bool *supports_maintain)
{
    const char *user_choice = NULL;
    return_code rc;

    printf("Is car maintenance supported:\n"
           "    [1] Yes\n"\
           "    [2] No\n"\
           "\n"
           "    [0] Exit\n");
    do
            rc = input_user_choice(&user_choice, "0", 2, "1", "2");
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    switch (atoi(user_choice))
    {
        case 1:
            *supports_maintain = 1;
            break;
        case 2:
            *supports_maintain = 0;
            break;
        default:
            assert(0);
    }

    return rc;
}

return_code input_car_price(unsigned long long *price)
{
    char buf[ULL_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter price: ", buf, ULL_MAX_DIGITS, validate_price);
    if (rc == OK)
        *price = strtoull(buf,NULL, 10);

    return rc;
}

return_code input_car_color(char *color)
{
    const char *user_choice;
    printf("Enter color:\n");

    const return_code rc = input_option(&user_choice, COLOR_OPTIONS, N_COLOR_OPTIONS, true);
    if (rc == OK)
        strcpy(color, user_choice);

    return rc;
}

return_code input_car_is_new(bool *is_new)
{
    const char *user_choice = NULL;
    return_code rc;

    printf("Is car new:\n"
           "    [1] Yes\n"\
           "    [2] No\n"\
           "\n"
           "    [0] Exit\n");
    do
        rc = input_user_choice(&user_choice, "0", 2, "1", "2");
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    switch (atoi(user_choice))
    {
        case 1:
            *is_new = 1;
        break;
        case 2:
            *is_new = 0;
        break;
        default:
            assert(0);
    }

    return rc;
}

return_code input_year(unsigned *release_year)
{
    char buf[UINT_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter release year: ", buf, UINT_MAX_DIGITS, validate_year);
    if (rc == OK)
        *release_year = strtoul(buf, NULL, 10);

    return rc;
}

return_code input_car_mileage(size_t *mileage_km)
{
    char buf[UL_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter mileage (km): ", buf, UL_MAX_DIGITS, validate_mileage);
    if (rc == OK)
        *mileage_km = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_owners_amount(size_t *owners_amount)
{
    char buf[ULL_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter owners amount: ", buf, ULL_MAX_DIGITS, validate_owners_amount);
    if (rc == OK)
        *owners_amount = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_repairs_amount(size_t *repairs_amount)
{
    char buf[ULL_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter repairs amount: ", buf, ULL_MAX_DIGITS, validate_repairs_amount);
    if (rc == OK)
        *repairs_amount = strtoull(buf, NULL, 10);

    return rc;
}

return_code input_car_warranty(unsigned *warranty)
{
    char buf[UINT_MAX_DIGITS + 1];

    const return_code rc = input_until_valid("Enter warranty period (years): ", buf, UINT_MAX_DIGITS, validate_warranty);
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
    return_code rc = input_car_brand(dst->brand);

    if (rc == OK)
        rc = input_car_country(dst->country);

    if (rc == OK)
        dst->is_foreign = strcmp(dst->country, "Russia");

    if (rc == OK && dst->is_foreign)
        rc = input_car_supports_maintain(&dst->supports_maintain);

    if (rc == OK)
        rc = input_car_price(&dst->price);

    if (rc == OK)
        rc = input_car_color(dst->color);

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
