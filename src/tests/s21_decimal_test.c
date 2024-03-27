#include "../s21_decimal.h"

#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_decimal_test.h"

START_TEST(test_is_less) {
  s21_decimal decimal_1 = {{123, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{120, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  decimal_2.bits[0] = 5555;
  result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_1.bits[0] = 5556;
  result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  decimal_2.bits[0] = 888888;
  decimal_1.bits[1] = 1;
  result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_1, 1);
  result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_2, 1);
  result = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_greater) {
  s21_decimal decimal_1 = {{123, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{120, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_2.bits[0] = 5555;
  result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  decimal_1.bits[0] = 5556;
  result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_2.bits[0] = 888888;
  decimal_1.bits[1] = 1;
  result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_1, 1);
  result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_2, 1);
  result = s21_is_greater(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal) {
  s21_decimal decimal_1 = {{69, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{69, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_1, 1);
  result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_2, 1);
  result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_1.bits[1] = 1;
  result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  decimal_2.bits[1] = 1;
  result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_exponent(&decimal_1, 1);
  result = s21_is_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal) {
  s21_decimal decimal_1 = {{69, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{69, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_1, 1);
  result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_2, 1);
  result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  decimal_1.bits[1] = 1;
  result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_2.bits[1] = 1;
  result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_exponent(&decimal_1, 1);
  result = s21_is_not_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal) {
  s21_decimal decimal_1 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_less_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_1.bits[0] = 900;
  result = s21_is_less_or_equal(decimal_2, decimal_1);
  ck_assert_int_eq(result, 1);
  result = s21_is_less_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_1, 1);
  result = s21_is_less_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_2, 1);
  result = s21_is_less_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_exponent(&decimal_1, 1);
  result = s21_is_less_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal) {
  s21_decimal decimal_1 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  int result = s21_is_greater_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  decimal_1.bits[0] = 900;
  result = s21_is_greater_or_equal(decimal_2, decimal_1);
  ck_assert_int_eq(result, 0);
  result = s21_is_greater_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
  set_sign(&decimal_1, 1);
  result = s21_is_greater_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_sign(&decimal_2, 1);
  result = s21_is_greater_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 0);
  set_exponent(&decimal_1, 1);
  result = s21_is_greater_or_equal(decimal_1, decimal_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_floor) {
  s21_decimal decimal_1 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2;
  set_exponent(&decimal_1, 1);
  s21_floor(decimal_1, &decimal_2);
  unsigned int result = decimal_2.bits[0];
  ck_assert_int_eq(result, 88);
  decimal_1.bits[0] = 9999;
  s21_floor(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 999);
  decimal_1.bits[0] = 1001;
  s21_floor(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 100);
  set_sign(&decimal_1, 1);
  decimal_1.bits[0] = 666;
  s21_floor(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 67);
  decimal_1.bits[0] = 1234;
  set_exponent(&decimal_1, 2);
  s21_floor(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 13);
  decimal_1.bits[0] = 99999;
  set_exponent(&decimal_1, 1);
  s21_floor(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 10000);
}
END_TEST

START_TEST(test_negate) {
  s21_decimal decimal_1 = {{55, 1, 2, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2;
  s21_negate(decimal_1, &decimal_2);
  int sign = get_sign(decimal_2);
  ck_assert_int_eq(sign, 1);
  set_sign(&decimal_2, 1);
  s21_negate(decimal_1, &decimal_2);
  sign = get_sign(decimal_2);
  ck_assert_int_eq(sign, 1);
  set_sign(&decimal_1, 1);
  s21_negate(decimal_1, &decimal_2);
  sign = get_sign(decimal_2);
  ck_assert_int_eq(sign, 0);
  set_sign(&decimal_2, 0);
  s21_negate(decimal_1, &decimal_2);
  sign = get_sign(decimal_2);
  ck_assert_int_eq(sign, 0);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal decimal_1 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2;
  set_exponent(&decimal_1, 1);
  s21_truncate(decimal_1, &decimal_2);
  unsigned int result = decimal_2.bits[0];
  ck_assert_int_eq(result, 88);
  decimal_1.bits[0] = 123456789;
  s21_truncate(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 12345678);
  set_exponent(&decimal_1, 5);
  s21_truncate(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 1234);
  set_exponent(&decimal_1, 1);
  set_sign(&decimal_1, 1);
  s21_truncate(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 12345678);
  decimal_1.bits[0] = 775533;
  s21_truncate(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 77553);
  decimal_1.bits[0] = 17;
  s21_truncate(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_round) {
  s21_decimal decimal_1 = {{888, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2;
  set_exponent(&decimal_1, 1);
  s21_round(decimal_1, &decimal_2);
  unsigned int result = decimal_2.bits[0];
  ck_assert_int_eq(result, 89);
  decimal_1.bits[0] = 1234;
  s21_round(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 123);
  decimal_1.bits[0] = 18755;
  set_exponent(&decimal_1, 2);
  s21_round(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 188);
  decimal_1.bits[0] = 18755;
  set_exponent(&decimal_1, 1);
  set_sign(&decimal_1, 1);
  s21_round(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 1876);
  decimal_1.bits[0] = 123;
  s21_round(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 12);
  decimal_1.bits[0] = 786534;
  set_exponent(&decimal_1, 5);
  s21_round(decimal_1, &decimal_2);
  result = decimal_2.bits[0];
  ck_assert_int_eq(result, 8);
}
END_TEST

START_TEST(test_add) {
  s21_decimal decimal_1 = {{123, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{543, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result;
  s21_add(decimal_1, decimal_2, &decimal_result);
  int unsigned result = decimal_result.bits[0];
  ck_assert_int_eq(result, 666);
  decimal_1.bits[1] = 22;
  decimal_2.bits[1] = 44;
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 66);
  decimal_1.bits[2] = 666;
  decimal_2.bits[2] = 0;
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 666);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  decimal_1.bits[0] = 123;
  decimal_2.bits[0] = 543;
  set_sign(&decimal_1, 1);
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 420);
  set_sign(&decimal_2, 1);
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 666);
  set_exponent(&decimal_1, 1);
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 5553);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  set_sign(&decimal_1, 1);
  set_sign(&decimal_2, 1);
  decimal_1.bits[1] = 55;
  decimal_2.bits[1] = 66;
  set_exponent(&decimal_1, 1);
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 715);
  result = get_sign(decimal_1);
  ck_assert_int_eq(result, 1);
  result = get_sign(decimal_2);
  ck_assert_int_eq(result, 1);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  set_sign(&decimal_1, 1);
  set_sign(&decimal_2, 0);
  decimal_1.bits[2] = 888;
  decimal_2.bits[2] = 22;
  set_exponent(&decimal_1, 1);
  s21_add(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 668);
  result = get_sign(decimal_1);
  ck_assert_int_eq(result, 1);
  result = get_sign(decimal_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_sub) {
  s21_decimal decimal_1 = {{123, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{543, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result;
  s21_sub(decimal_1, decimal_2, &decimal_result);
  int unsigned result = decimal_result.bits[0];
  ck_assert_int_eq(result, 420);
  set_sign(&decimal_1, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 666);
  set_sign(&decimal_1, 0);
  set_sign(&decimal_2, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 666);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  decimal_1.bits[1] = 2000;
  decimal_2.bits[1] = 5000;
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 3000);
  set_sign(&decimal_2, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 7000);
  set_sign(&decimal_1, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 3000);
  set_sign(&decimal_1, 0);
  set_sign(&decimal_2, 0);
  set_exponent(&decimal_1, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 48000);
  set_exponent(&decimal_2, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 3000);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  decimal_1.bits[2] = 10000;
  decimal_2.bits[2] = 1000;
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 9000);
  set_sign(&decimal_1, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 11000);
  set_sign(&decimal_2, 1);
  set_exponent(&decimal_1, 1);
  s21_sub(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_mul_0) {
  s21_decimal decimal_1 = {{22, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{44, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result;
  s21_mul(decimal_1, decimal_2, &decimal_result);
  int unsigned result = decimal_result.bits[0];
  ck_assert_int_eq(result, 968);
  set_exponent(&decimal_1, 2);
  set_sign(&decimal_1, 1);
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 968);
  result = get_sign(decimal_result);
  ck_assert_int_eq(result, 1);
  set_exponent(&decimal_2, 2);
  set_sign(&decimal_2, 1);
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 968);
  result = get_sign(decimal_result);
  ck_assert_int_eq(result, 0);
  zero_out(&decimal_1);
  zero_out(&decimal_2);
  decimal_1.bits[1] = 2;
  decimal_2.bits[1] = 2;
  set_exponent(&decimal_1, 3);
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 0);
  decimal_1.bits[2] = 3;
  decimal_2.bits[2] = 3;
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[2];
  ck_assert_int_eq(result, 0);
  decimal_1.bits[0] = 1;
  decimal_2.bits[0] = 1;
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  set_exponent(&decimal_1, 0);
  ck_assert_int_eq(result, 0);
  decimal_1.bits[2] = 0;
  decimal_2.bits[2] = 0;
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[1];
  ck_assert_int_eq(result, 4);
  s21_mul(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_mul_1) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{6, 0, 0, 0}};
  ck_assert_int_eq(s21_mul(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(test_mul_2) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal y = {{0x0000000B, 0x00000000, 0x00000000, 0x00010000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xC28F5C29, 0x8F5C28F5, 0x1C28F5C2, 0x001B0000}};
  ck_assert_int_eq(s21_mul(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(test_mul_3) {
  s21_decimal x = {{0x2110991E, 0x1ED3CC02, 0x00000023, 0x000E0000}};
  s21_decimal y = {{0xC09256A0, 0x00000C41, 0x00000000, 0x00100000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xBA2121FE, 0x3DE0F035, 0x1C360358, 0x00180000}};
  ck_assert_int_eq(s21_mul(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(test_mul_4) {
  s21_decimal x = {{0x2110991F, 0x1ED3CC02, 0x00000023, 0x000E0000}};
  s21_decimal y = {{0xC092569D, 0x00000C41, 0x00000000, 0x00100000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x92DF46D1, 0x3DDA088A, 0x1C360358, 0x00180000}};
  ck_assert_int_eq(s21_mul(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(test_div_0) {
  s21_decimal decimal_1 = {{44, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_2 = {{22, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal decimal_result;
  s21_div(decimal_1, decimal_2, &decimal_result);
  int unsigned result = decimal_result.bits[0];
  ck_assert_int_eq(result, 2);
  set_exponent(&decimal_1, 1);
  decimal_1.bits[0] = 100;
  decimal_2.bits[0] = 20;
  s21_div(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 5);
  result = get_exponent(decimal_result);
  ck_assert_int_eq(result, 1);
  set_exponent(&decimal_2, 1);
  decimal_1.bits[0] = 500;
  decimal_2.bits[0] = 5;
  s21_div(decimal_1, decimal_2, &decimal_result);
  result = decimal_result.bits[0];
  ck_assert_int_eq(result, 100);
  result = get_exponent(decimal_result);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_div_1) {
  s21_decimal x = {{0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal correct = {{0}};
  s21_div(x, y, &result);
  ck_assert(s21_is_equal(result, correct));
}
END_TEST

START_TEST(test_div_2) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0}};
  s21_decimal result = {{0}};
  ck_assert(s21_div(x, y, &result) == 3);
}
END_TEST

START_TEST(test_div_3) {
  s21_decimal x = {{10}};
  s21_decimal y = {{5}};
  s21_decimal result = {{0}};
  s21_decimal correct = {{2, 0, 0, 0}};
  s21_div(x, y, &result);
  ck_assert(s21_is_equal(result, correct));
}
END_TEST

START_TEST(test_div_4) {
  s21_decimal x = {{5}};
  s21_decimal y = {{10}};
  s21_decimal result = {{0}};
  s21_decimal correct = {{5, 0, 0, 0}};
  set_exponent(&correct, 1);
  s21_div(x, y, &result);
  ck_assert(s21_is_equal(result, correct));
}
END_TEST

START_TEST(test_div_5) {
  s21_decimal x = {{1}};
  set_exponent(&x, 28);
  s21_decimal y = {{2}};
  s21_decimal result = {{0}};
  s21_decimal correct = {{0}};
  s21_div(x, y, &result);
  ck_assert(s21_is_equal(result, correct));
}
END_TEST

START_TEST(test_from_int_to_decimal) {
  s21_decimal decimal_1 = {{44, 0, 0, 0b00000000000000000000000000000000}};
  int x = 8888;
  s21_from_int_to_decimal(x, &decimal_1);
  int unsigned result = decimal_1.bits[0];
  ck_assert_int_eq(result, 8888);
  x = -666;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 666);
  result = get_sign(decimal_1);
  ck_assert_int_eq(result, 1);
  x = 412341234;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 412341234);
  x = 2234343;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 2234343);
  x = 9787;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 9787);
  x = 2222222;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 2222222);
  x = 13371337;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 13371337);
  x = 1984;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 1984);
  x = 555555555;
  s21_from_int_to_decimal(x, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 555555555);
}
END_TEST

START_TEST(test_from_float_to_decimal) {
  float f = 25.5;
  s21_decimal decimal_1 = {{44, 0, 0, 0b00000000000000000000000000000000}};
  s21_from_float_to_decimal(f, &decimal_1);
  int unsigned result = decimal_1.bits[0];
  ck_assert_int_eq(result, 2550000);
  f = 173.5;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 1735000);
  f = 0.55551;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 5555099);
  f = 765.1;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 7650999);
  f = 8888.0;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 8888000);
  f = 99.9;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 9990000);
  f = 13.13;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 1313000);
  f = 987.1;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 9870999);
  f = 1.1;
  s21_from_float_to_decimal(f, &decimal_1);
  result = decimal_1.bits[0];
  ck_assert_int_eq(result, 1100000);
}
END_TEST

START_TEST(test_from_decimal_to_int) {
  s21_decimal decimal_1 = {{88888, 0, 0, 0b00000000000000000000000000000000}};
  int x = 777;
  s21_from_decimal_to_int(decimal_1, &x);
  int result = x;
  ck_assert_int_eq(result, 88888);
  decimal_1.bits[0] = 9;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, 9);
  decimal_1.bits[0] = 77777;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, 77777);
  decimal_1.bits[0] = 888;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, 888);
  decimal_1.bits[0] = 13371337;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, 13371337);
  decimal_1.bits[0] = 123123;
  set_sign(&decimal_1, 1);
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, -123123);
  decimal_1.bits[0] = 77777777;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, -77777777);
  decimal_1.bits[0] = 98;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, -98);
  decimal_1.bits[0] = 0;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, -0);
  decimal_1.bits[0] = 44;
  s21_from_decimal_to_int(decimal_1, &x);
  result = x;
  ck_assert_int_eq(result, -44);
}
END_TEST

START_TEST(test_from_decimal_to_float) {
  s21_decimal decimal_1 = {{88888, 0, 0, 0b00000000000000000000000000000000}};
  float f = 1;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 88888);
  decimal_1.bits[0] = 23;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 23);
  decimal_1.bits[0] = 7676;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 7676);
  decimal_1.bits[0] = 55;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 55);
  decimal_1.bits[0] = 22;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 22);
  decimal_1.bits[0] = 8912;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 8912);
  decimal_1.bits[0] = 2358;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 2358);
  decimal_1.bits[0] = 3874;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 3874);
  decimal_1.bits[0] = 276;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 276);
  decimal_1.bits[0] = 3371;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 3371);
  decimal_1.bits[0] = 85;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 85);
  decimal_1.bits[0] = 10;
  set_exponent(&decimal_1, 1);
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, 1);
  set_sign(&decimal_1, 1);
  set_exponent(&decimal_1, 0);
  decimal_1.bits[0] = 3;
  s21_from_decimal_to_float(decimal_1, &f);
  ck_assert_float_eq(f, -3);
}
END_TEST

Suite *suite_is_less(void) {
  Suite *s;
  TCase *tc_is_less;

  s = suite_create("s21_is_less");
  tc_is_less = tcase_create("s21_is_less tcase");

  tcase_add_test(tc_is_less, test_is_less);
  suite_add_tcase(s, tc_is_less);
  tcase_set_timeout(tc_is_less, 100);

  return s;
}

Suite *suite_is_greater(void) {
  Suite *s;
  TCase *tc_is_greater;

  s = suite_create("s21_is_greater");
  tc_is_greater = tcase_create("s21_is_greater tcase");

  tcase_add_test(tc_is_greater, test_is_greater);
  suite_add_tcase(s, tc_is_greater);
  tcase_set_timeout(tc_is_greater, 100);

  return s;
}

Suite *suite_is_equal(void) {
  Suite *s;
  TCase *tc_is_equal;

  s = suite_create("s21_is_equal");
  tc_is_equal = tcase_create("s21_is_equal tcase");

  tcase_add_test(tc_is_equal, test_is_equal);
  suite_add_tcase(s, tc_is_equal);
  tcase_set_timeout(tc_is_equal, 100);

  return s;
}

Suite *suite_is_not_equal(void) {
  Suite *s;
  TCase *tc_is_not_equal;

  s = suite_create("s21_is_not_equal");
  tc_is_not_equal = tcase_create("s21_is_not_equal tcase");

  tcase_add_test(tc_is_not_equal, test_is_not_equal);
  suite_add_tcase(s, tc_is_not_equal);
  tcase_set_timeout(tc_is_not_equal, 100);
  return s;
}

Suite *suite_is_less_or_equal(void) {
  Suite *s;
  TCase *tc_is_less_or_equal;

  s = suite_create("s21_is_less_or_equal");
  tc_is_less_or_equal = tcase_create("s21_is_less_or_equal tcase");

  tcase_add_test(tc_is_less_or_equal, test_is_less_or_equal);
  suite_add_tcase(s, tc_is_less_or_equal);
  tcase_set_timeout(tc_is_less_or_equal, 100);
  return s;
}

Suite *suite_is_greater_or_equal(void) {
  Suite *s;
  TCase *tc_is_greater_or_equal;

  s = suite_create("s21_is_greater_or_equal");
  tc_is_greater_or_equal = tcase_create("s21_is_greater_or_equal tcase");

  tcase_add_test(tc_is_greater_or_equal, test_is_greater_or_equal);
  suite_add_tcase(s, tc_is_greater_or_equal);
  tcase_set_timeout(tc_is_greater_or_equal, 100);

  return s;
}

Suite *suite_floor(void) {
  Suite *s;
  TCase *tc_floor;

  s = suite_create("s21_floor");
  tc_floor = tcase_create("s21_floor tcase");

  tcase_add_test(tc_floor, test_floor);
  suite_add_tcase(s, tc_floor);
  tcase_set_timeout(tc_floor, 100);

  return s;
}

Suite *suite_negate(void) {
  Suite *s;
  TCase *tc_negate;

  s = suite_create("s21_negate");
  tc_negate = tcase_create("s21_negate tcase");

  tcase_add_test(tc_negate, test_negate);
  suite_add_tcase(s, tc_negate);
  tcase_set_timeout(tc_negate, 100);

  return s;
}

Suite *suite_truncate(void) {
  Suite *s;
  TCase *tc_truncate;

  s = suite_create("s21_truncate");
  tc_truncate = tcase_create("s21_truncate tcase");

  tcase_add_test(tc_truncate, test_truncate);
  suite_add_tcase(s, tc_truncate);
  tcase_set_timeout(tc_truncate, 100);

  return s;
}

Suite *suite_round(void) {
  Suite *s;
  TCase *tc_round;

  s = suite_create("s21_round");
  tc_round = tcase_create("s21_round tcase");

  tcase_add_test(tc_round, test_round);
  suite_add_tcase(s, tc_round);
  tcase_set_timeout(tc_round, 100);

  return s;
}

Suite *suite_add(void) {
  Suite *s;
  TCase *tc_add;

  s = suite_create("s21_add");
  tc_add = tcase_create("s21_add tcase");

  tcase_add_test(tc_add, test_add);
  suite_add_tcase(s, tc_add);
  tcase_set_timeout(tc_add, 100);

  return s;
}

Suite *suite_sub(void) {
  Suite *s;
  TCase *tc_sub;

  s = suite_create("s21_sub");
  tc_sub = tcase_create("s21_sub tcase");

  tcase_add_test(tc_sub, test_sub);
  suite_add_tcase(s, tc_sub);
  tcase_set_timeout(tc_sub, 100);

  return s;
}

Suite *suite_mul(void) {
  Suite *s;
  TCase *tc_mul;

  s = suite_create("s21_mul");
  tc_mul = tcase_create("s21_mul tcase");

  tcase_add_test(tc_mul, test_mul_0);
  tcase_add_test(tc_mul, test_mul_1);
  tcase_add_test(tc_mul, test_mul_2);
  tcase_add_test(tc_mul, test_mul_3);
  tcase_add_test(tc_mul, test_mul_4);
  suite_add_tcase(s, tc_mul);
  tcase_set_timeout(tc_mul, 100);

  return s;
}

Suite *suite_div(void) {
  Suite *s;
  TCase *tc_div;

  s = suite_create("s21_div");
  tc_div = tcase_create("s21_div tcase");

  tcase_add_test(tc_div, test_div_0);
  tcase_add_test(tc_div, test_div_1);
  tcase_add_test(tc_div, test_div_2);
  tcase_add_test(tc_div, test_div_3);
  tcase_add_test(tc_div, test_div_4);
  tcase_add_test(tc_div, test_div_5);

  suite_add_tcase(s, tc_div);
  tcase_set_timeout(tc_div, 100);

  return s;
}

Suite *suite_from_int_to_decimal(void) {
  Suite *s;
  TCase *tc_from_int_to_decimal;

  s = suite_create("s21_from_int_to_decimal");
  tc_from_int_to_decimal = tcase_create("s21_from_int_to_decimal tcase");

  tcase_add_test(tc_from_int_to_decimal, test_from_int_to_decimal);
  suite_add_tcase(s, tc_from_int_to_decimal);
  tcase_set_timeout(tc_from_int_to_decimal, 100);

  return s;
}

Suite *suite_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc_from_float_to_decimal;

  s = suite_create("s21_from_float_to_decimal");
  tc_from_float_to_decimal = tcase_create("s21_from_float_to_decimal tcase");

  tcase_add_test(tc_from_float_to_decimal, test_from_float_to_decimal);
  suite_add_tcase(s, tc_from_float_to_decimal);
  tcase_set_timeout(tc_from_float_to_decimal, 100);

  return s;
}

Suite *suite_from_decimal_to_int(void) {
  Suite *s;
  TCase *tc_from_decimal_to_int;

  s = suite_create("s21_from_decimal_to_int");
  tc_from_decimal_to_int = tcase_create("s21_from_decimal_to_int tcase");

  tcase_add_test(tc_from_decimal_to_int, test_from_decimal_to_int);
  suite_add_tcase(s, tc_from_decimal_to_int);
  tcase_set_timeout(tc_from_decimal_to_int, 100);

  return s;
}

Suite *suite_from_decimal_to_float(void) {
  Suite *s;
  TCase *tc_from_decimal_to_float;

  s = suite_create("s21_from_decimal_to_float");
  tc_from_decimal_to_float = tcase_create("s21_from_decimal_to_float tcase");

  tcase_add_test(tc_from_decimal_to_float, test_from_decimal_to_float);
  suite_add_tcase(s, tc_from_decimal_to_float);
  tcase_set_timeout(tc_from_decimal_to_float, 100);

  return s;
}