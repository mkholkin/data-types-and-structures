#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUM_BRANDS             24
#define NUM_COUNTRIES         224
#define NUM_COLORS             20

#define MAX_BRAND_NAME_LEN     30
#define MAX_COLOR_NAME_LEN     30
#define MAX_COUNTRY_NAME_LEN   30

const char* brands[NUM_BRANDS] = 
{
    "Toyota", "Honda", "Ford", "Volkswagen", "Nissan", "Hyundai",
    "Chevrolet", "Kia", "Mazda", "Subaru", "Jeep", "Dodge",
    "Ram", "Chrysler", "Fiat", "Alfa Romeo", "Lancia", "Skoda",
    "Seat", "Renault", "Peugeot", "Citroen", "Opel", "Volvo"
};

const char* countries[NUM_COUNTRIES] = 
{
    "Aruba", "Afghanistan", "Angola", "Anguilla", "Aland Islands", "Albania",
    "Andorra", "Arab Emirates", "Argentina", "Armenia", "American Samoa",
    "Antarctica", "Antigua and Barbuda", "Australia", "Austria", "Azerbaijan",
    "Burundi", "Belgium", "Benin", "Burkina Faso", "Bangladesh", "Bulgaria",
    "Bahrain", "Bahamas", "Bosnia", "Saint Barthelemy", "Belarus",
    "Belize", "Bermuda", "Brazil", "Barbados", "Brunei Darussalam", "Bhutan",
    "Bouvet Island", "Botswana", "African Republic", "Canada", "Cocos Islands",
    "Switzerland", "Chile", "China", "Cote d'Ivoire", "Cameroon", "Congo",
    "Cook Islands", "Colombia", "Comoros", "Cabo Verde", "Costa Rica", "Cuba",
    "Curacao", "Christmas Island", "Cayman Islands", "Cyprus", "Czechia", "Germany",
    "Djibouti", "Dominica", "Denmark", "Dominican Republic", "Algeria", "Ecuador",
    "Egypt", "Eritrea", "Western Sahara", "Spain", "Estonia", "Ethiopia",
    "Finland", "Fiji", "France", "Faroe Islands", "Gabon", "United Kingdom",
    "Georgia", "Guernsey", "Ghana", "Gibraltar", "Guinea", "Guadeloupe",
    "Gambia", "Guinea-Bissau", "Equatorial Guinea", "Greece", "Grenada", "Greenland",
    "Guatemala", "French Guiana", "Guam", "Guyana", "Hong Kong", "Honduras",
    "Croatia", "Haiti", "Hungary", "Indonesia", "Isle of Man", "India",
    "Ireland", "Iran", "Iraq", "Iceland", "Israel", "Italy",
    "Jamaica", "Jersey", "Jordan", "Japan", "Kazakhstan", "Kenya", "Kyrgyzstan",
    "Cambodia", "Kiribati", "Saint Kitts", "Korea", "Kuwait",
    "Lebanon", "Liberia", "Libya", "Saint Lucia", "Liechtenstein", "Sri Lanka",
    "Lesotho", "Lithuania", "Luxembourg", "Latvia", "Macao", "Morocco", "Monaco",
    "Moldova", "Madagascar", "Maldives", "Mexico", "Marshall Islands",
    "North Macedonia", "Mali", "Malta", "Myanmar", "Montenegro", "Mongolia",
    "Mozambique", "Mauritania", "Montserrat", "Martinique",
    "Mauritius", "Malawi", "Malaysia", "Mayotte", "Namibia", "New Caledonia",
    "Niger", "Norfolk Island", "Nigeria", "Nicaragua", "Niue", "Netherlands",
    "Norway", "Nepal", "Nauru", "New Zealand", "Oman", "Pakistan", "Panama",
    "Pitcairn", "Peru", "Philippines", "Palau", "Papua New Guinea", "Poland",
    "Puerto Rico", "Portugal", "Paraguay", "Palestine", "French Polynesia",
    "Qatar", "Reunion", "Romania", "Russian Federation", "Rwanda", "Saudi Arabia",
    "Sudan", "Senegal", "Singapore", "Solomon Islands",
    "Sierra Leone", "El Salvador", "San Marino", "Somalia",
    "Serbia", "South Sudan", "Suriname", "Slovakia",
    "Slovenia", "Sweden", "Eswatini", "Sint Maarten", "Seychelles",
    "Chad", "Togo", "Thailand",
    "Tajikistan", "Tokelau", "Turkmenistan", "Timor-Leste", "Tonga", "Trinidad and Tobago",
    "Tunisia", "Turkey", "Tuvalu", "Taiwan", "Uganda", "Ukraine",
    "Uruguay", "United States", "Uzbekistan", "Virgin Islands",
    "Viet Nam", "Vanuatu", "Wallis and Futuna", "Samoa", "Yemen", "South Africa",
    "Zambia", "Zimbabwe"
};

const char *colors[NUM_COLORS] = 
{
    "red", "blue", "green", "yellow", "orange",
    "white", "black", "pink", "brown", "gray",
    "cyan", "magenta", "purple", "tan", "beige",
    "ivory", "ochre", "sienna", "umber", "wheat"
};

typedef enum
{
    NEW,
    NOT_NEW
} car_status;

typedef struct
{
    char brand[MAX_BRAND_NAME_LEN + 1];
    char country[MAX_COUNTRY_NAME_LEN + 1];
    bool is_foreign;
    bool is_service_supported;
    unsigned long long price;
    char color[MAX_COLOR_NAME_LEN + 1];
    bool status;
    union
    {
        struct 
        {
            size_t guarantee_years;
        } new_car;
        struct 
        {
            unsigned year_of_production;
            size_t milleage;
            size_t owners_count;
            size_t repairs_count;
        } old_car;
    } details;
} car_t;

int main(int argc, char **argv)
{
    srand(atoi(argv[1]));
    
    FILE *file = fopen("data.bin", "ab");
    fseek(file, 0, SEEK_END);

    car_t car;

    strcpy(car.brand, brands[rand() % NUM_BRANDS]);
    strcpy(car.country, countries[rand() % NUM_COUNTRIES]);
    strcpy(car.color, colors[rand() % NUM_COLORS]);
    
    car.is_foreign = rand() % 2;
    car.is_service_supported = rand() % 2;
    car.price = 500000 + rand() % (20000000 - 500000 + 1);
    car.status = rand() % 2;
    
    if (car.status == 1)
        car.details.new_car.guarantee_years = 1 + rand() % 10;
    else
    {
        car.details.old_car.milleage = 10000 + rand() % (500000 - 10000 + 1);
        car.details.old_car.owners_count = 1 + rand() % 10;
        car.details.old_car.repairs_count = rand() % 11;
        car.details.old_car.year_of_production = 1970 + rand() % (2024 - 1970 + 1);
    }

    fwrite(&car, sizeof(car_t), 1, file);
    fclose(file);

    return 0;
}