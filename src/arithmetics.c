#include "s21_decimal.h"
// Расмотреть краевые случаи и добавить везде банковское округление

// 0 - OK, 1- large, 2-small,3-division by zero;
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  zero_out(result);
  big_decimal b_val_1 = to_big(value_1);
  big_decimal b_val_2 = to_big(value_2);
  big_decimal b_res = to_big(*result);
  int sign_1 = b_val_1.sign;
  int sign_2 = b_val_2.sign;
  normalization_big(&b_val_1, &b_val_2);
  b_res.exponent = b_val_1.exponent;
  // Both positive
  if (sign_1 == 0 && sign_2 == 0) addition(b_val_1, b_val_2, &b_res);
  // First one is positive, the other is negative
  else if (sign_1 == 0 && sign_2 == 1) {
    b_val_2.sign = 0;
    subtraction(b_val_1, b_val_2, &b_res);
  }
  // Second one is positive, the other is negative
  else if (sign_1 == 1 && sign_2 == 0) {
    b_val_1.sign = 0;
    subtraction(b_val_2, b_val_1, &b_res);
  }
  // Both negative
  else {
    b_val_1.sign = 0;
    b_val_2.sign = 0;
    addition(b_val_1, b_val_2, &b_res);
    b_res.sign = 1;
  }
  error = to_normal(b_res, result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  zero_out(result);
  big_decimal b_val_1 = to_big(value_1);
  big_decimal b_val_2 = to_big(value_2);
  big_decimal b_res = to_big(*result);
  int sign_1 = b_val_1.sign;
  int sign_2 = b_val_2.sign;
  normalization_big(&b_val_1, &b_val_2);
  b_res.exponent = b_val_1.exponent;
  // Both positive
  if (sign_1 == 0 && sign_2 == 0) subtraction(b_val_1, b_val_2, &b_res);
  // First one is positive, second one is negative
  else if (sign_1 == 0 && sign_2 == 1) {
    b_val_2.sign = 0;
    addition(b_val_1, b_val_2, &b_res);
  }
  // First one is negative, second one is positive
  else if (sign_1 == 1 && sign_2 == 0) {
    b_val_1.sign = 0;
    addition(b_val_1, b_val_2, &b_res);
    b_res.sign = 1;
  }
  // Both negative
  else {
    b_val_1.sign = 0;
    b_val_2.sign = 0;
    subtraction(b_val_2, b_val_1, &b_res);
  }
  error = to_normal(b_res, result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  zero_out(result);
  big_decimal b_val_1 = to_big(value_1);
  big_decimal b_val_2 = to_big(value_2);
  big_decimal b_res = to_big(*result);
  b_res.exponent = b_val_1.exponent + b_val_2.exponent;
  if (b_val_1.sign + b_val_2.sign == 1) b_res.sign = 1;
  for (int i = 0; i < 224; i++) {
    if (get_bit_big(b_val_2, i)) {
      big_decimal shift_i = b_val_1;
      left_shift_big(&shift_i, i);
      addition(shift_i, b_res, &b_res);
    }
  }
  error = to_normal(b_res, result);
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (is_dec_zero(value_2))
    error = 3;
  else {
    zero_out(result);
    big_decimal dividend = to_big(value_1);
    big_decimal divisor = to_big(value_2);
    big_decimal b_res = to_big(*result);
    division(dividend, divisor, &b_res);
    error = to_normal(b_res, result);
  }
  return error;
}
