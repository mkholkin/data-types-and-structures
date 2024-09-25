#include "../../include/io/io.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/utils/string_tools.h"

#define MAX_USER_choice_LEN 2
#define MAX_USER_CHOICE_LEN_WITH_NULL (MAX_USER_choice_LEN + 1)
#define INPUT_OVERFLOW_MSG "Ввод слишком длинный. Попробуйте еще раз\n"
#define INVALID_INPUT_MSG "Невалидное значение. Попробуйте еще раз\n"

int should_retry(const return_code rc)
{
    return rc == ERR_DIALOG_INPUT_OVERFLOW || rc == ERR_DIALOG_INVALID_INPUT;
}

static void print_dialog_retry_message(const return_code rc)
{
    switch (rc)
    {
        case ERR_DIALOG_INPUT_OVERFLOW:
            printf(INPUT_OVERFLOW_MSG);
            break;
        case ERR_DIALOG_INVALID_INPUT:
            printf(INVALID_INPUT_MSG);
            break;
        default:
            break;
    }
}

static return_code input_string(const char *prompt, char *string, const size_t max_len)
{
    return_code rc = OK;

    printf("%s", prompt);

    char buff[max_len + 1 + 1];

    if (fgets(buff, max_len + 1 + 1, stdin)) // +1 for \n + 1 for \0
    {
        if (buff[strlen(buff) - 1] != '\n' && !feof(stdin))
        {
            rc = ERR_DIALOG_INPUT_OVERFLOW;
            fflush(stdin);
        }

        if (rc == OK)
            rstrip(buff, "\n");
    }
    else if (ferror(stdin))
        rc = ERR_IO;

    if (rc == OK)
        strcpy(string, buff);

    return rc;
}

return_code input_option(const char **user_choice, const char **options, const size_t n_options, const bool retry)
{
    return_code rc;
    *user_choice = NULL;

    do
    {
        char *user_input[MAX_USER_CHOICE_LEN_WITH_NULL];

        for (int i = 0; i < n_options; ++i)
            printf("    [%d] %s\n", i + 1, options[i]);
        printf("\n    [0] Exit\n");

        rc = input_string("Choice: ", user_input, MAX_USER_choice_LEN);

        if (rc == OK && strcmp(user_input, "0") == 0)
            rc = DIALOG_EXIT;

        for (int i = 0; rc == OK && *user_choice == NULL && i < n_options; ++i)
        {
            if (strtol(user_input, NULL, 10) == i + 1)
                *user_choice = options[i];
        }
    }
    while (retry && (rc == OK || should_retry(rc)) && *user_choice == NULL);

    return rc;
}

return_code input_user_choice(const char **user_choice, const char *exit_code, const size_t n_options, ...)
{
    // writes NULL to <user_choice> if choice is invalid or io error occured
    *user_choice = NULL;
    char user_input[MAX_USER_CHOICE_LEN_WITH_NULL];

    return_code rc = input_string("Choice: ", user_input, MAX_USER_choice_LEN);

    if (rc == OK && strcmp(user_input, exit_code) == 0)
        rc = DIALOG_EXIT;

    if (rc == OK)
    {
        va_list args;
        va_start(args, n_options);

        for (size_t i = 0; i < n_options && *user_choice == NULL; ++i)
        {
            const char *option = va_arg(args, const char *);

            if (strcmp(user_input, option) == 0)
                *user_choice = option;
        }

        va_end(args);
    }

    return rc;
}

return_code input_until_valid(const char *prompt, char *string, const size_t max_len, bool (*validator)(const char *))
{
    return_code rc;

    do
    {
        rc = input_string(prompt, string, max_len);

        if (rc == OK && validator != NULL && !validator(string))
            rc = ERR_DIALOG_INVALID_INPUT;

        print_dialog_retry_message(rc);
    }
    while (should_retry(rc));

    return rc;
}
