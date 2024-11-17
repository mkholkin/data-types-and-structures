/**
* @file string_tools.h
 * @brief Дополнительные инструменты для работы со строками
 */

#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#include <stddef.h>

/// @brief Разбить строку на слова по строке-разделителю. Исходная строка будет испорчена
/// @param[in] string
/// @param[out] dst
/// @param[out] words_count
/// @param sep срока-разделитель
void split(char *string, char **dst, size_t *words_count, const char *sep);

/// @brief Проверка: состоит ли строка только из чисел
/// @param[in] string
/// @return булевое значение
int is_digits_only(const char *string);

/// @brief Проверка: состоит ли строка только из букв
/// @param[in] string
/// @return булевое значение
int is_alphas_only(const char *string);

/// @brief Возвращает указатель на первый символ строки с конца не входящий в заданный набор символов
/// @param[in] string
/// @param[in] charset
/// @return char *
char *strrcpbrk(const char *string, const char *charset);

/// @brief Удалить все вхождения указанных символов с конца строки
/// @param[in] string
/// @param[in] charset
/// @return указатель на начало строки
char *rstrip(char *string, const char *charset);

/// @brief Перевести минуты в формат hh:mm
/// @param[out] string
/// @param[in] minutes
/// @return указатель на начало временной строки
char *minutes_to_time_string(char *string, unsigned short minutes);

/// @brief Перевести временную строку формата hh:dd в минуты
/// @param[in] string
/// @return минуты
unsigned short time_string_to_minutes(const char *string);

/// @brief Подсчитать количество вхождений символа <c> в строку <string>
/// @param[in] string
/// @param[in] c
/// @return количесто вхождений <c> в <string>
size_t str_count(const char *string, const char c);

#endif //STRING_TOOLS_H
