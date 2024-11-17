#include "utils/string_tools.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void split(char *string, char **dst, size_t *words_count, const char *sep)
{
    char *token;

    if (!(token = strtok(string, sep)))
        return;

    do
    {
        *dst = token;
        ++(*words_count);
        ++dst;
    }
    while ((token = strtok(NULL, sep)) != NULL);
}

int is_digits_only(const char *string)
{
    if (string == NULL)
        return 0;

    int digits_only = isdigit(*string);

    while (digits_only && *(++string) != '\0')
        digits_only = isdigit(*string);

    return digits_only;
}

int is_alphas_only(const char *string)
{
    if (string == NULL)
        return 0;

    int alphas_only = isalpha(*string);

    while (alphas_only && *(++string) != '\0')
        alphas_only = isalpha(*string);

    return alphas_only;
}

char *minutes_to_time_string(char *string, const unsigned short minutes)
{
    if (minutes > 1439)
        return NULL;

    sprintf(string, "%02d:%02d", minutes / 60, minutes % 60);

    return string;
}

unsigned short time_string_to_minutes(const char *string)
{
    unsigned short hours, minutes;

    sscanf(string, "%2hu:%2hu", &hours, &minutes);

    return hours * 60 + minutes;
}

char *strrcpbrk(const char *string, const char *charset)
{
    const char *string_start = string;
    int missmatch_found = 0;

    for (; *string; ++string)
    {
    }

    while (!missmatch_found && string_start < string)
    {
        --string;
        if (strchr(charset, *string) == NULL)
            missmatch_found = 1;
    }

    return missmatch_found ? (char *) string : NULL;
}

char *rstrip(char *string, const char *charset)
{
    char *non_esc_end = strrcpbrk(string, charset);

    if (non_esc_end)
        *(non_esc_end + 1) = '\0';

    return string;
}

size_t str_count(const char *string, const char c)
{
    if (string == NULL)
        return 0;

    size_t n = 0;

    for (; *string != '\0'; ++string)
        if (*string == c)
            ++n;

    return n;
}
