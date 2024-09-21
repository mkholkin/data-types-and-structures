#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

#define VARCHAR_LENGTH 255

typedef struct
{
    unsigned warranty;
} car_spec_new;

typedef struct
{
    unsigned release_year;
    size_t mileage_km;
    size_t owners_amount;
    size_t repairs_amount;
} car_spec_secondhand;

typedef union
{
    car_spec_new new;
    car_spec_secondhand secondhand;
} car_spec;

typedef struct
{
    const char *brand;
    const char *country;
    bool is_foreign;
    bool supports_maintain;
    unsigned long long price;
    const char *color;
    bool is_new;
    car_spec spec;
} car_t;


// element of key-table
typedef struct
{
    size_t src_idx;
    unsigned long long price;
} key_price;
#endif //TYPES_H
