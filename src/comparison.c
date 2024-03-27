#include "s21_decimal.h"

// 0-FALSE, 1-TRUE
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  if (is_dec_zero(value_1) && is_dec_zero(value_2))
    result = 0;
  else {
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);
    // If first one is negative, seconde one is positive
    if (sign_1 > sign_2) result = 1;
    // If first one is positive, second one is negative
    else if (sign_1 < sign_2)
      result = 0;
    // Both numbers have the same sign
    else {
      big_decimal b_val_1 = to_big(value_1);
      big_decimal b_val_2 = to_big(value_2);
      result = is_less_big(b_val_1, b_val_2);
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2) && s21_is_not_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  if (is_dec_zero(value_1) && is_dec_zero(value_2))
    result = 1;
  else {
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);
    if ((sign_1 + sign_2) % 2)
      result = 0;
    else {
      big_decimal b_val_1 = to_big(value_1);
      big_decimal b_val_2 = to_big(value_2);
      result = is_equal_big(b_val_1, b_val_2);
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
