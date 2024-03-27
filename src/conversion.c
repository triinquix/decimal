#include <math.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 1;
  if (dst) {
    zero_out(dst);
    if (src < 0) {
      if (src == -2147483648) src++;
      set_sign(dst, 1);
      src = -src;
    }
    dst->bits[0] = src;
    result = 0;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  int sign = get_sign(src);
  if (get_exponent(src)) s21_truncate(src, &src);
  *dst = src.bits[0];
  if (sign) *dst = -(*dst);
  if (src.bits[1] || src.bits[2] || (get_bit(src, 31) && !sign)) result = 1;
  return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 1;
  union {
    float number;
    unsigned int tmp;
  } tmp_union = {.number = src};
  int isNegative = (tmp_union.tmp & (1 << 31)) >> 31;
  if (isNegative) src = -src;
  zero_out(dst);
  if (src >= 1e-28 && src != NaN && src != inf && src != n_inf) {
    if (isNegative) set_sign(dst, 1);
    // Gets unbiased exponent
    int exponent = ((tmp_union.tmp & (0b11111111 << 23)) >> 23) - 127;
    dst->bits[0] = 1;
    for (int i = 22; i >= 0; i--) {
      int bit_to_check = (tmp_union.tmp & (1 << i)) >> i;
      if (bit_to_check) {
        s21_decimal dec_one = {{1, 0, 0, 0}};
        s21_decimal dec_one_shifted = {{1 << (23 - i), 0, 0, 0}};
        s21_decimal tmp_dec;
        zero_out(&tmp_dec);
        s21_div(dec_one, dec_one_shifted, &tmp_dec);
        s21_add(*dst, tmp_dec, dst);
      }
    }
    s21_decimal tmp_decimal = {{1 << abs(exponent), 0, 0, 0}};
    s21_decimal copy = *dst;
    if (exponent >= 0)
      s21_mul(copy, tmp_decimal, dst);
    else
      s21_div(copy, tmp_decimal, dst);
    big_decimal tmp_big = to_big(*dst);
    while (tmp_big.bits[1] || tmp_big.bits[2] ||
           get_significant_bits(tmp_big) > 7)
      div_by_ten_big(&tmp_big, NO_ROUND);
    to_normal(tmp_big, dst);
    result = 0;
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  s21_decimal dec_min = {{1, 0, 0, 0}};
  set_exponent(&dec_min, 28);
  s21_decimal dec_max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int isNegative = get_sign(src);
  set_sign(&src, 0);
  if (s21_is_less(src, dec_min))
    *dst = 0;
  else if (!s21_is_greater(src, dec_max)) {
    big_decimal tmp_big = to_big(src);
    while (get_significant_bits(tmp_big) > 7)
      div_by_ten_big(&tmp_big, ROUNDING);
    if (tmp_big.exponent >= 0) {
      int exponent = tmp_big.exponent;
      *dst = tmp_big.bits[0];
      while (exponent--) *(dst) *= 0.1;
      *dst = roundf((*dst) * pow(10, tmp_big.exponent)) /
             pow(10, tmp_big.exponent);
      if (isNegative) *dst *= (-1);
      error = 0;
    }
  }
  return error;
}
