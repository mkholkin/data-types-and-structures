#ifndef RETURN_CODES_H
#define RETURN_CODES_H

typedef enum
{
    OK,

    BUFFER_OVERFLOW_ERROR,
    ORD_OVERFLOW_ERROR,

    ERROR_INVALID_INPUT_INT,
    ERROR_INVALID_INPUT_DOUBLE,
    MANTISSA_OVERFLOW_ERROR
} return_code;

#endif //RETURN_CODES_H