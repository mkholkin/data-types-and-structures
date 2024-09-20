#include "../../include/io/validators.h"

#include "../../include/utils/string_tools.h"

bool validate_car_brand(const char *str)
{
    return true;
}

bool validate_country(const char *str)
{
    return is_alphas_only(str);
}

bool validate_price(const char *str)
{
    return is_digits_only(str);
}

bool validate_year(const char *str)
{
    return is_digits_only(str);
}

bool validate_mileage(const char *str)
{
    return is_digits_only(str);
}

bool validate_owners_amount(const char *str)
{
    return is_digits_only(str);
}

bool validate_repairs_amount(const char *str)
{
    return is_digits_only(str);
}

bool validate_warranty(const char *str)
{
    return is_digits_only(str);
}
