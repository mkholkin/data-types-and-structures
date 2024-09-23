#include "../include/process.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/defines.h"
#include "../include/options.h"
#include "../include/algorithm/key_table.h"
#include "../include/algorithm/sorting.h"
#include "../include/io/cars_io.h"
#include "../include/io/io.h"
#include "../include/utils/array_tools.h"
#include "../include/utils/time.h"

return_code process_add_car(car_t *cars, size_t *n)
{
    if (*n == MAX_CARS
    )
        return ERR_CARS_LIMIT_REACHED;

    return input_car(&cars[(*n)++]);
}

return_code process_remove_car(car_t *cars, size_t *n)
{
    car_t *target = NULL;
    unsigned long long key;
    const return_code rc = input_car_price(&key);

    if (rc == OK)
    {
        for (int i = 0; i < *n; ++i)
            if (cars[i].price == key)
                target = cars + i;

        if (target)
            arr_remove(cars, sizeof(car_t), n, target);
    }

    return rc;
}

void process_show_key_table(const car_t *cars, const size_t n)
{
    key_price key_tbl[n];
    gen_key_table(cars, key_tbl, n);
    printf("|=======|================|\n"
        "| Index |      Price     |\n"
        "|=======|================|\n");
    for (size_t i = 0; i < n; i++)
        printf("| %5zu | %14llu |\n"
               "|-------+----------------|\n", key_tbl[i].src_idx, key_tbl[i].price);
}

void process_show_sorted_key_table(const car_t *cars, const size_t n)
{
    key_price key_tbl[n];
    gen_key_table(cars, key_tbl, n);
    key_tbl_qsort_cars_by_price(key_tbl, n);
    printf("|=======|================|\n"
        "| Index |      Price     |\n"
        "|=======|================|\n");
    for (size_t i = 0; i < n; i++)
        printf("| %5zu | %14llu |\n"
               "|-------+----------------|\n", key_tbl[i].src_idx, key_tbl[i].price);
}

void process_show_cars_table(const car_t *cars, const size_t n)
{
    printf(
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n"
        "| Index |     Brand     |     Country     | Maintenance |      Price     |   Color   | Warranty (years) | Release year | Mileage (km) | Owners amount | Repairs amount |\n"
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n");

    for (size_t i = 0; i < n; i++)
    {
        const car_t car = cars[i];
        printf("| %5zu | %13s | %15s | %11c | %14llu | %9s |", i, car.brand, car.country,
               car.is_foreign ? car.supports_maintain ? '+' : '-' : '+', car.price, car.color);
        if (car.is_new)
            printf(" %16u | %12c | %12c | %13c | %14c |\n", car.spec.new.warranty, '-', '-', '-', '-');
        else
            printf(" %16c | %12u | %12zu | %13zu | %14zu |\n", '-', car.spec.secondhand.release_year,
                   car.spec.secondhand.mileage_km, car.spec.secondhand.owners_amount,
                   car.spec.secondhand.repairs_amount);
        printf(
            "+-------+---------------+-----------------+-------------+----------------+-----------+------------------+--------------+--------------+---------------+----------------+\n");
    }
}

void process_show_sorted_cars_table(const car_t *cars, const size_t n)
{
    key_price key_tbl[n];
    gen_key_table(cars, key_tbl, n);
    key_tbl_qsort_cars_by_price(key_tbl, n);
    printf(
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n"
        "| Index |     Brand     |     Country     | Maintenance |      Price     |   Color   | Warranty (years) | Release year | Mileage (km) | Owners amount | Repairs amount |\n"
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n");

    for (size_t i = 0; i < n; i++)
    {
        const car_t car = cars[key_tbl[i].src_idx];
        printf("| %5zu | %13s | %15s | %11c | %14llu | %9s |", i, car.brand, car.country,
               car.is_foreign ? car.supports_maintain ? '+' : '-' : '+', car.price, car.color);
        if (car.is_new)
            printf(" %16u | %12c | %12c | %13c | %14c |\n", car.spec.new.warranty, '-', '-', '-', '-');
        else
            printf(" %16c | %12u | %12zu | %13zu | %14zu |\n", '-', car.spec.secondhand.release_year,
                   car.spec.secondhand.mileage_km, car.spec.secondhand.owners_amount,
                   car.spec.secondhand.repairs_amount);
        printf(
            "+-------+---------------+-----------------+-------------+----------------+-----------+------------------+--------------+--------------+---------------+----------------+\n");
    }
}

void process_show_stat(car_t *cars, const size_t n)
{
    key_price key_tbl[n];
    gen_key_table(cars, key_tbl, n);

    const time_t seed = time(NULL);

    srand(seed);
    shuffle(cars, sizeof(car_t), n);
    srand(seed);
    shuffle(key_tbl, sizeof(key_price), n);

    nsec_t beg = nanoseconds_now();
    qsort_cars_by_price(cars, n);
    nsec_t end = nanoseconds_now();
    const nsec_t table_time_qsort = end - beg;

    beg = nanoseconds_now();
    key_tbl_qsort_cars_by_price(key_tbl, n);
    end = nanoseconds_now();
    const nsec_t key_table_time_qsort = end - beg;

    srand(seed);
    shuffle(cars, sizeof(car_t), n);
    srand(seed);
    shuffle(key_tbl, sizeof(key_price), n);

    beg = nanoseconds_now();
    selectsort_cars_by_price(cars, n);
    end = nanoseconds_now();
    const nsec_t table_time_selectsort = end - beg;

    beg = nanoseconds_now();
    key_tbl_selectsort_cars_by_price(key_tbl, n);
    end = nanoseconds_now();
    const nsec_t key_table_time_selectsort = end - beg;

    printf("┌────────────────────────────┬────────────────────┬────────────────────┐\n"
           "│                            │ Time (nanoseconds) │   Memory (bytes)   │\n"
           "├────────────────────────────┼────────────────────┼────────────────────┤\n"
           "│ Table (quick sort)         │ %18llu │ %18zu │\n"
           "├────────────────────────────┼────────────────────┼────────────────────┤\n"
           "│ Key-Table (quick sort)     │ %18llu │ %18zu │\n"
           "├────────────────────────────┼────────────────────┼────────────────────┤\n"
           "│ Table (selection sort)     │ %18llu │ %18zu │\n"
           "├────────────────────────────┼────────────────────┼────────────────────┤\n"
           "│ Key-Table (selection sort) │ %18llu │ %18zu │\n"
           "└────────────────────────────┴────────────────────┴────────────────────┘\n",
           table_time_qsort, sizeof(car_t) * n,
           key_table_time_qsort, (sizeof(car_t) + sizeof(key_price)) * n,
           table_time_selectsort, sizeof(car_t) * n,
           key_table_time_selectsort, (sizeof(car_t) + sizeof(key_price)) * n);
}

void process_super_filter(const car_t *cars, const size_t n)
{
    car_t selected_cars[MAX_CARS];
    size_t n_selected = 0;

    const char *key_brand;
    unsigned long long low_price, high_price;

    printf("Enter brand:\n");
    const return_code rc = input_option(&key_brand, BRAND_OPTIONS, N_BRAND_OPTIONS, true);

    while (rc == OK)
    {
        input_car_price(&low_price);
        input_car_price(&high_price);

        if (high_price <= low_price)
            printf("[!] High price must be higher than low\n");
        else
            break;
    }

    for (int i = 0; i < n; i++)
        if (strcmp(cars[i].brand, key_brand) == 0 && cars[i].is_new == false && cars[i].spec.secondhand.owners_amount ==
            1 && cars[i].spec.secondhand.repairs_amount == 0 && cars[i].price >= low_price && cars[i].price <=
            high_price)
            selected_cars[n_selected++] = cars[i];

    process_show_cars_table(selected_cars, n_selected);

    printf("\n"
        "=======================================================================================================================================================================|\n"
        "|                                                                 FOREIGN CARS WITH MAINTAINANACE SUPPORT                                                              |\n"
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n"
        "| Index |     Brand     |     Country     | Maintenance |      Price     |   Color   | Warranty (years) | Release year | Mileage (km) | Owners amount | Repairs amount |\n"
        "|=======|===============|=================|=============|================|===========|==================|==============|==============|===============|================|\n"
    );

    for (size_t i = 0; i < n_selected; i++)
    {
        const car_t car = selected_cars[i];
        if (car.is_foreign && car.supports_maintain)
        {
            printf("| %5zu | %13s | %15s | %11c | %14llu | %9s |", i, car.brand, car.country, '+',  car.price, car.color);
            if (car.is_new)
                printf(" %16u | %12c | %12c | %13c | %14c |\n", car.spec.new.warranty, '-', '-', '-', '-');
            else
                printf(" %16c | %12u | %12zu | %13zu | %14zu |\n", '-', car.spec.secondhand.release_year,
                       car.spec.secondhand.mileage_km, car.spec.secondhand.owners_amount,
                       car.spec.secondhand.repairs_amount);
            printf(
                "+-------+---------------+-----------------+-------------+----------------+-----------+------------------+--------------+--------------+---------------+----------------+\n");
        }
    }
}


return_code process_load_cars(car_t *cars, size_t *n)
{
    // TODO: handle errors
    *n = 0;
    FILE *stream = fopen(DATA_FILE, "rb");
    const size_t el_size = sizeof(car_t);

    while (*n < MAX_CARS && fread(cars + *n, el_size, 1, stream) == 1)
        (*n)++;

    if (stream)
        fclose(stream);

    printf("[+] Successfully loaded %zu cars\n", *n);

    return OK;
}

return_code process_save_cars(const car_t *cars, const size_t n)
{
    return_code rc = OK;
    FILE *stream = fopen(DATA_FILE, "wb");

    if (stream == NULL)
        rc = ERR_IO;

    if (rc == OK)
    {
        const size_t bytes_written = fwrite(cars, sizeof(car_t), n, stream);
        if (bytes_written != n)
            rc = ERR_IO;
    }

    if (rc == OK)
        printf("[+] Successfully saved %zu cars\n", n);

    if (stream)
        fclose(stream);

    return rc;
}
