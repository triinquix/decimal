#include <stdio.h>

#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int return_code = 0;
  if (result == NULL)
    return_code = 1;
  else {
    *result = value;
    if (get_sign(value))
      set_sign(result, 0);
    else
      set_sign(result, 1);
  }
  return return_code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int return_code = 0;
  if (result == NULL)
    return_code = 1;
  else {
    *result = value;
    big_decimal result_copy = to_big(*result);
    int exponent = get_exponent(value);
    for (int i = 0; i < exponent; i++) div_by_ten_big(&result_copy, NO_ROUND);
    return_code = to_normal(result_copy, result);
    if (return_code) {
      return_code = 1;
      zero_out(result);
    }
  }
  return return_code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int return_code = 0;
  if (result == NULL)
    return_code = 1;
  else {
    int sign = get_sign(value);
    *result = value;
    big_decimal result_copy = to_big(*result);
    int exponent = get_exponent(value);
    for (int i = 0; i < exponent; i++) div_by_ten_big(&result_copy, NO_ROUND);
    if (sign == 1) increase_big_dec_by_one(&result_copy);
    return_code = to_normal(result_copy, result);
    if (return_code) {
      return_code = 1;
      zero_out(result);
    }
  }
  return return_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int return_code = 0;
  if (result == NULL)
    return_code = 1;
  else {
    *result = value;
    big_decimal result_copy = to_big(*result);
    int exponent = get_exponent(value);
    for (int i = 0; i < exponent; i++) div_by_ten_big(&result_copy, ROUNDING);
    return_code = to_normal(result_copy, result);
    if (return_code) {
      return_code = 1;
      zero_out(result);
    }
  }
  return return_code;
}
