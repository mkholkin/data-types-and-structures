#ifndef DEFINES_H
#define DEFINES_H

#define MAX_CARS 100

const char *COLOR_OPTIONS[] = {
    "Black",
    "White",
    "Grey",
    "Red",
    "Green",
    "Pink",
    "Silver",
    "Gold",
    "Light_green",
};
#define N_COLOR_OPTIONS (sizeof(COLOR_OPTIONS / sizeof(COLOR_OPTIONS[0]))

const char *BRAND_OPTIONS[] = {
    "BMW",
    "Havail",
    "Ford",
    "Mercedes",
    "Audi",
    "Porche",
    "Lada",
    "Dodge",
    "Chevrolet"
};
#define N_BRAND_OPTIONS (sizeof(BRAND_OPTIONS / sizeof(BRAND_OPTIONS[0]))

const char *COUNTRY_OPTIONS[] = {
    "Russia,
    "UK",
    "USA",
    "German",
    "Italy",
    "Poland",
    "China",
};
#define N_COUNTRY_OPTIONS (sizeof(COUNTRY_OPTIONS / sizeof(COUNTRY_OPTIONS[0]))

#endif //DEFINES_H
