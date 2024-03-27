#include "s21_decimal.h"

// Improve shift function

// Conversions

big_decimal to_big(s21_decimal decimal) {
  big_decimal result;
  zero_out_big(&result);
  for (int i = 0; i < 3; i++) result.bits[i] = decimal.bits[i];
  result.exponent = get_exponent(decimal);
  result.sign = get_sign(decimal);
  return result;
}

int to_normal(big_decimal big, s21_decimal* decimal) {
  int error = 0;
  // Rethink
  while (big.exponent > 28) {
    div_by_ten_big(&big, BANKERS_ROUNDING);
  }
  while ((big.bits[3] || big.bits[4] || big.bits[5] || big.bits[6]) &&
         big.exponent) {
    div_by_ten_big(&big, BANKERS_ROUNDING);
  }
  if (big.bits[3] || big.bits[4] || big.bits[5] || big.bits[6]) {
    if (big.sign)
      error = 2;
    else
      error = 1;
  } else {
    if (is_big_dec_zero(big)) {
      big.exponent = 0;
      big.sign = 0;
    }
    for (int i = 0; i < 3; i++) decimal->bits[i] = big.bits[i];
    set_sign(decimal, big.sign);
    set_exponent(decimal, big.exponent);
  }
  return error;
}

// Arithmetics

void division(big_decimal dividend, big_decimal divisor, big_decimal* b_res) {
  b_res->exponent = dividend.exponent - divisor.exponent;
  if (dividend.sign + divisor.sign == 1) b_res->sign = 1;
  dividend.exponent = 0;
  divisor.exponent = 0;
  dividend.sign = 0;
  divisor.sign = 0;
  while (b_res->exponent < 56 && !is_big_dec_zero(dividend)) {
    if (is_less_big(dividend, divisor)) {
      mul_by_ten_numerator_big(&dividend);
      mul_by_ten_numerator_big(b_res);
      (b_res->exponent)++;
    } else {
      int max_shift = count_max_shift(divisor);
      for (int i = max_shift;
           i >= 0 && is_greater_or_equal_big(dividend, divisor); i--) {
        big_decimal shift = divisor;
        left_shift_big(&shift, i);
        // Тут перепроверить
        if (is_less_or_equal_big(shift, dividend)) {
          subtraction(dividend, shift, &dividend);
          big_decimal dec_one;
          zero_out_big(&dec_one);
          dec_one.bits[0] = 1;
          left_shift_big(&dec_one, i);
          addition(*b_res, dec_one, b_res);
        }
      }
    }
  }
  while (b_res->exponent < 0) {
    (b_res->exponent)++;
    mul_by_ten_numerator_big(b_res);
  }
}

void normalization_big(big_decimal* value_1, big_decimal* value_2) {
  int exponent_1 = value_1->exponent;
  int exponent_2 = value_2->exponent;
  int difference = exponent_1 - exponent_2;
  if (difference > 0) {
    for (int i = 0; i < difference; i++) mul_by_ten_numerator_big(value_2);
    value_2->exponent = exponent_1;
  } else {
    for (int i = 0; i < -difference; i++) mul_by_ten_numerator_big(value_1);
    value_1->exponent = exponent_2;
  }
}

void mul_by_ten_numerator_big(big_decimal* decimal) {
  big_decimal shift_1 = *decimal;
  left_shift_big(&shift_1, 1);
  big_decimal shift_3 = *decimal;
  left_shift_big(&shift_3, 3);
  addition(shift_1, shift_3, decimal);
}

void addition(big_decimal value_1, big_decimal value_2, big_decimal* result) {
  int carry = 0;
  for (int i = 0; i < 224; i++) {
    int tmp = carry + get_bit_big(value_1, i) + get_bit_big(value_2, i);
    set_bit_big(result, i, tmp % 2);
    if (tmp > 1)
      carry = 1;
    else
      carry = 0;
  }
}

void subtraction(big_decimal value_1, big_decimal value_2,
                 big_decimal* result) {
  big_decimal minuend;
  big_decimal subtrahend;
  if (is_greater_big(value_1, value_2)) {
    minuend = value_1;
    subtrahend = value_2;
  } else {
    minuend = value_2;
    subtrahend = value_1;
    result->sign = 1;
  }
  for (int i = 0; i < 224; i++) {
    int tmp_bit = get_bit_big(minuend, i) - get_bit_big(subtrahend, i);
    if (tmp_bit == -1) {
      for (int j = i + 1; j < 224; j++) {
        if (get_bit_big(minuend, j)) {
          set_bit_big(&minuend, j, 0);
          break;
        } else
          set_bit_big(&minuend, j, 1);
      }
    }
    if (tmp_bit < 0) tmp_bit = 1;
    set_bit_big(result, i, tmp_bit);
  }
}

void increase_big_dec_by_one(big_decimal* value) {
  big_decimal dec_one;
  zero_out_big(&dec_one);
  dec_one.bits[0] = 1;
  addition(*value, dec_one, value);
}

void bankers_rounding(big_decimal remainder, big_decimal* value) {
  big_decimal dec_five;
  zero_out_big(&dec_five);
  dec_five.bits[0] = 5;
  if (is_equal_big(remainder, dec_five)) {
    if (get_bit_big(*value, 0)) increase_big_dec_by_one(value);
  } else if (is_greater_big(remainder, dec_five))
    increase_big_dec_by_one(value);
}

void math_rounding(big_decimal remainder, big_decimal* value) {
  big_decimal dec_five;
  zero_out_big(&dec_five);
  dec_five.bits[0] = 5;
  if (is_greater_or_equal_big(remainder, dec_five))
    increase_big_dec_by_one(value);
}

int count_max_shift(big_decimal decimal) {
  int res = 223;
  if (!is_big_dec_zero(decimal)) {
    for (int i = 223; i >= 0; i--) {
      if (get_bit_big(decimal, i)) {
        res -= i;
        break;
      }
    }
  }
  return res;
}

void div_by_ten_big(big_decimal* decimal, enum rounding round_method) {
  big_decimal divisor;
  zero_out_big(&divisor);
  big_decimal dividend = *decimal;
  for (int i = 0; i < 7; i++) decimal->bits[i] = 0;
  decimal->exponent--;
  dividend.exponent = 0;
  dividend.sign = 0;
  divisor.bits[0] = 10;
  int max_shift = count_max_shift(divisor);
  for (int i = max_shift; i >= 0; i--) {
    big_decimal shift = divisor;
    left_shift_big(&shift, i);
    if (is_less_or_equal_big(shift, dividend)) {
      subtraction(dividend, shift, &dividend);
      big_decimal dec_one;
      zero_out_big(&dec_one);
      dec_one.bits[0] = 1;
      left_shift_big(&dec_one, i);
      addition(*decimal, dec_one, decimal);
    }
  }
  if (round_method == BANKERS_ROUNDING)
    bankers_rounding(dividend, decimal);
  else if (round_method == ROUNDING)
    math_rounding(dividend, decimal);
}

int get_significant_bits(big_decimal big) {
  unsigned int tmp = big.bits[0];
  int res = 1;
  while (tmp >= 10) {
    tmp /= 10;
    res++;
  }
  return res;
}

// Bit operations

int get_bit_big(big_decimal decimal, int bit_number) {
  int res = -1;
  int arr_num = bit_number / 32;
  bit_number %= 32;
  res = ((1U << bit_number) & decimal.bits[arr_num]) >> bit_number;
  return res;
}

void set_bit_big(big_decimal* decimal, int bit_number, int bit) {
  int arr_num = bit_number / 32;
  bit_number %= 32;
  if (bit == 1)
    decimal->bits[arr_num] |= 1U << bit_number;
  else if (bit == 0)
    decimal->bits[arr_num] &= ~(1U << bit_number);
}

void zero_out_big(big_decimal* big) {
  for (int i = 0; i < 7; i++) big->bits[i] = 0;
  big->exponent = 0;
  big->sign = 0;
}

int is_big_dec_zero(big_decimal decimal) {
  int res = 1;
  for (int i = 0; i < 7; i++)
    if (decimal.bits[i] != 0) res = 0;
  return res;
}

void left_shift_big(big_decimal* decimal, int shift) {
  for (int i = 223; i >= 0; i--) {
    if (i >= shift) {
      int bit_to_set = get_bit_big(*decimal, i - shift);
      set_bit_big(decimal, i, bit_to_set);
    } else
      set_bit_big(decimal, i, 0);
  }
}

// Comparison

int is_equal_big(big_decimal value_1, big_decimal value_2) {
  int result = 1;
  if (is_big_dec_zero(value_1) && is_big_dec_zero(value_2))
    result = 1;
  else {
    int sign_1 = value_1.sign;
    int sign_2 = value_2.sign;
    if ((sign_1 + sign_2) % 2)
      result = 0;
    else {
      normalization_big(&value_1, &value_2);
      for (int i = 0; i < 7; i++) {
        if (value_1.bits[i] != value_2.bits[i]) result = 0;
      }
    }
  }
  return result;
}

int is_less_big(big_decimal value_1, big_decimal value_2) {
  int result = 0;
  if (is_big_dec_zero(value_1) && is_big_dec_zero(value_2))
    result = 0;
  else {
    int sign_1 = value_1.sign;
    int sign_2 = value_2.sign;
    // If first one is negative, seconde one is positive
    if (sign_1 > sign_2) result = 1;
    // If first one is positive, second one is negative
    else if (sign_1 < sign_2)
      result = 0;
    // Both numbers have the same sign
    else {
      normalization_big(&value_1, &value_2);
      for (int i = 6; i >= 0; i--) {
        if (value_1.bits[i] < value_2.bits[i]) {
          result = 1;
          break;
        } else if (value_1.bits[i] > value_2.bits[i])
          break;
      }
      if (sign_1) result = 1 - result;
    }
  }
  return result;
}

int is_greater_big(big_decimal value_1, big_decimal value_2) {
  return !is_less_big(value_1, value_2) && !is_equal_big(value_1, value_2);
}

int is_greater_or_equal_big(big_decimal value_1, big_decimal value_2) {
  return is_greater_big(value_1, value_2) || is_equal_big(value_1, value_2);
}

int is_less_or_equal_big(big_decimal value_1, big_decimal value_2) {
  return is_less_big(value_1, value_2) || is_equal_big(value_1, value_2);
}
