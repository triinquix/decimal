#include "s21_decimal.h"

// 0-False, 1-TRUE
int is_dec_zero(s21_decimal decimal) {
  int res = 1;
  for (int i = 0; i < 3; i++)
    if (decimal.bits[i] != 0) res = 0;
  return res;
}

int get_bit(s21_decimal decimal, int bit_number) {
  int res = -1;
  if (bit_number >= 0 && bit_number <= 127) {
    int arr_num = bit_number / 32;
    bit_number %= 32;
    res = ((1U << bit_number) & decimal.bits[arr_num]) >> bit_number;
  }
  return res;
}

void set_bit(s21_decimal* decimal, int bit_number, int bit) {
  if (bit_number >= 0 && bit_number <= 127) {
    int arr_num = bit_number / 32;
    bit_number %= 32;
    if (bit == 1)
      decimal->bits[arr_num] |= 1U << bit_number;
    else if (bit == 0)
      decimal->bits[arr_num] &= ~(1U << bit_number);
  }
}

int get_exponent(s21_decimal decimal) {
  return (decimal.bits[3] & (0b11111111 << 16)) >> 16;
}

void set_exponent(s21_decimal* decimal, int exp) {
  for (int i = 112; i < 120; i++) {
    int bit_to_insert = ((1U << (i - 112)) & exp) >> (i - 112);
    set_bit(decimal, i, bit_to_insert);
  }
}

void zero_out(s21_decimal* decimal) {
  for (int i = 0; i < 4; i++) decimal->bits[i] = 0;
}

int get_sign(s21_decimal decimal) { return get_bit(decimal, 127); }

void set_sign(s21_decimal* decimal, int bit) { set_bit(decimal, 127, bit); }
