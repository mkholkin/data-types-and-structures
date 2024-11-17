#ifndef RETURN_CODES_H
#define RETURN_CODES_H

typedef enum
{
    OK,
    DIALOG_EXIT,
    ERR_DIALOG_INPUT_OVERFLOW,
    ERR_DIALOG_INVALID_INPUT,
    ERR_IO,
} return_code;

#endif //RETURN_CODES_H
