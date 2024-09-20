#include "../../include/algorithm/key_table.h"

void gen_key_table(const car_t *cars, key_price *tbl, const size_t nmemb)
{
    for (int i = 0; i < nmemb; ++i)
    {
        tbl[i].src_idx = i;
        tbl[i].price = cars[i].price;
    }
}
