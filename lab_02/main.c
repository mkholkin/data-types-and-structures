#include <stdio.h>

#include "include/process.h"
#include "include/types.h"

int main(void)
{
    car_t arr[10] =
    {
        {"Jopa", "Russia", 0, 1, 1000000000, "Red", 0, .spec.secondhand = { 2024, 12312, 2, 0}},
        {"Havail", "China"},
        {"BMW", "USA"},
    };
    size_t n = 3;

    // process_show_sorted_key_table(arr, n);
    process_show_cars_table(arr, n);
}
