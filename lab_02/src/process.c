#include "../include/process.h"

#include <stdio.h>

#include "../include/defines.h"
#include "../include/algorithm/sorting.h"
#include "../include/io/cars_io.h"

return_code process_add_car(car_t *cars, size_t *n)
{
    if (*n == MAX_CARS
    )
    return ERR_CARS_LIMIT_REACHED;

    return input_car(&cars[(*n)++]);
}

return_code process_remove_car(car_t *cars, size_t *n)
{

}

void process_show_sorted_key_table(key_price *key_tbl, const size_t n)
{
    key_tbl_qsort_cars_by_price(key_tbl, n);
    printf("|=======|================|\n"
        "| Index |      Price     |\n"
        "|=======|================|\n");
    for (size_t i = 0; i < n; i++)
        printf("| %5zu | %14llu |\n"
               "|-------+----------------|\n", key_tbl[i].src_idx, key_tbl[i].price);
}

void process_show_cars_table(const car_t *cars, size_t n)
{
    printf("|=======|=========|=============|=============|================|===========|==================|==============|==============|===============|================|\n"
                 "| Index |  Brand  |   Country   | Maintenance |      Price     |   Color   | Warranty (years) | Release year | Mileage (km) | Owners amount | Repairs amount |\n"
                 "|=======|=========|=============|=============|================|===========|==================|==============|==============|===============|================|\n");

    for (size_t i = 0; i < n; i++)
    {
        car_t car = cars[i];
        printf("| %5zu | %7s | %11s | %11c | %14llu | %9s |", i, car.brand, car.country, car.is_foreign ? car.supports_maintain ? '+' : '-' : '+', car.price, car.color);
        if (car.is_new)
            printf(" %16u | %12c | %12c | %13c | %14c |\n", car.spec.new.warranty, '-', '-', '-', '-');
        else
            printf(" %16c | %12u | %12zu | %13zu | %14zu |\n", '-', car.spec.secondhand.release_year, car.spec.secondhand.mileage_km, car.spec.secondhand.owners_amount, car.spec.secondhand.repairs_amount);
        printf("|-------+---------+-------------+-------------+----------------+-----------+------------------+--------------+--------------+---------------+----------------+\n");
    }
}

void process_show_sorted_cars_table(const car_t *cars, key_price *key_tbl, const size_t n)
{
    key_tbl_qsort_cars_by_price(key_tbl, n);
    printf("|=======|=========|=============|=============|================|===========|==================|==============|==============|===============|================|\n"
             "| Index |  Brand  |   Country   | Maintenance |      Price     |   Color   | Warranty (years) | Release year | Mileage (km) | Owners amount | Repairs amount |\n"
             "|=======|=========|=============|=============|================|===========|==================|==============|==============|===============|================|\n");

    for (size_t i = 0; i < n; i++)
    {
        car_t car = cars[key_tbl[i].src_idx];
        printf("| %5zu | %7s | %11s | %11c | %14llu | %9s |", i, car.brand, car.country, car.is_foreign ? car.supports_maintain ? '+' : '-' : '+', car.price, car.color);
        if (car.is_new)
            printf(" %16u | %12c | %12c | %13c | %14c |\n", car.spec.new.warranty, '-', '-', '-', '-');
        else
            printf(" %16c | %12u | %12zu | %13zu | %14zu |\n", '-', car.spec.secondhand.release_year, car.spec.secondhand.mileage_km, car.spec.secondhand.owners_amount, car.spec.secondhand.repairs_amount);
        printf("|-------+---------+-------------+-------------+----------------+-----------+------------------+--------------+--------------+---------------+----------------+\n");
    }
}

return_code process_compare_methods(car_t *cars, key_price *key_tbl, size_t *n)
{
}

return_code process_compare_sort_algorithms(car_t *cars, key_price *key_tbl, size_t *n)
{

}
