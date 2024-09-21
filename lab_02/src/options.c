#include "../include/options.h"

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
const size_t N_COLOR_OPTIONS = sizeof(COLOR_OPTIONS) / sizeof(COLOR_OPTIONS[0]);

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
const size_t N_BRAND_OPTIONS = sizeof(BRAND_OPTIONS) / sizeof(BRAND_OPTIONS[0]);

const char *COUNTRY_OPTIONS[] = {
    "Russia",
    "UK",
    "USA",
    "German",
    "Italy",
    "Poland",
    "China",
};
const size_t N_COUNTRY_OPTIONS = sizeof(COUNTRY_OPTIONS) / sizeof(COUNTRY_OPTIONS[0]);
