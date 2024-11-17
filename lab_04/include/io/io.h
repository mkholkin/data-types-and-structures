/**
* @file io.h
 * @brief Функции коммуникации с пользователем
 */

#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdbool.h>

#include "../return_codes.h"

/// @brief Ввод строки от пользователя пока не будет выполнено условие валидации
/// @param[in] prompt
/// @param[out] string
/// @param[in] max_len
/// @param[in] validator
/// @return Код возврата | Строка введенная пользовтелем, прошедшая валидацию
return_code input_until_valid(const char *prompt, char *string, size_t max_len, bool (*validator)(const char *));

/// @brief Выбор пользовтелем одного из предложенных вариантов, до тех пор пока выбор не будет валидным
/// @param[out] user_choice
/// @param[in] exit_code Код выхода их диалога выбора
/// @param[in] n_options Количество предложенных вариантов выбора (без учета кода выхода)
/// @param ... Предложенные выборы
/// @return Код возврата | Выбор пользователя (гарантированно один из предложенных)
return_code input_user_choice(const char **user_choice, const char *exit_code, size_t n_options, ...);

/// @brief Возвращает булевое значение - можно ли запросить повторный ввод от пользователя при ошибке
/// @param[in] rc Текущий код возврата (состояние программы)
/// @return
int should_retry(const return_code rc);

return_code input_option(const char **user_choice, const char **options, const size_t n_options, const bool retry);

#endif //IO_H
