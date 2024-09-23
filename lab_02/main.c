#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/defines.h"
#include "include/process.h"
#include "include/types.h"
#include "include/io/cars_io.h"
#include "include/io/io.h"

#define CHOISE_COMMANDS_MENU \
"Chose command:\n"\
"   [1] Add car\n"\
"   [2] Remove car\n"\
"   [3] Show cars table\n"\
"   [4] Show sorted cars table\n"\
"   [5] Show key-table (price)\n"\
"   [6] Show sorted key-table (price)\n"\
"   [7] Filter cars\n"\
"   [8] Show stat\n"\
"   [9] Load cars table from file\n"\
"   [10] Save cars table to file\n"\
"\n"\
"   [0] Exit\n"\
"\n"

return_code exec_command(car_t *cars, size_t *n);

return_code start_polling(car_t *cars, size_t *n);

int main(void)
{
    car_t cars[MAX_CARS];
    size_t n;

    process_load_cars(cars + 10, &n);

    return start_polling(cars, &n);
}

return_code start_polling(car_t *cars, size_t *n)
{
    return_code rc;

    do
    {
        rc = exec_command(cars, n);
    }
    while (rc == OK);

    return rc;
}

return_code exec_command(car_t *cars, size_t *n)
{
    return_code rc;
    const char *user_choise = NULL;

    printf(CHOISE_COMMANDS_MENU);
    do
    {
        rc = input_user_choice(&user_choise, "0", 10, "1", "2", "3", "4", "5", "6", "7", "8", "9", "10");
    }
    while ((rc == OK || should_retry(rc)) && user_choise == NULL);

    if (rc == OK)
        switch (atoi(user_choise))
        {
            case 1:
                rc = process_add_car(cars, n);
                break;
            case 2:
                rc = process_remove_car(cars, n);
                break;
            case 3:
                process_show_cars_table(cars, *n);
                break;
            case 4:
                process_show_sorted_cars_table(cars, *n);
                break;
            case 5:
                process_show_key_table(cars, *n);
                break;
            case 6:
                process_show_sorted_key_table(cars, *n);
                break;
            case 7:
                process_super_filter(cars, *n);
                break;
            case 8:
                process_show_stat(cars, *n);
                break;
            case 9:
                rc = process_load_cars(cars, n);
                break;
            case 10:
                rc = process_save_cars(cars, *n);
                break;
            default:
                assert(0);
        }

    return rc;
}
