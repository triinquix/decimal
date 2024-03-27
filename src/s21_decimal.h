#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
  int exponent;
  int sign;
} big_decimal;

#define NaN 0. / 0.
#define inf 1. / 0.
#define n_inf -1. / 0.

enum rounding { NO_ROUND, ROUNDING, BANKERS_ROUNDING };
// Binary operations

// Checks if decimal equals zero
int is_dec_zero(s21_decimal decimal);

// Gets bit by its number
int get_bit(s21_decimal decimal, int bit_number);

// Sets bit on the position
void set_bit(s21_decimal* decimal, int bit_number, int bit);

// Gets exponent
int get_exponent(s21_decimal decimal);

// Sets exponent
void set_exponent(s21_decimal* decimal, int exp);

// Zero out decimal
void zero_out(s21_decimal* decimal);

// Gets sign
int get_sign(s21_decimal decimal);

// Sets sign
void set_sign(s21_decimal* decimal, int bit);

// Comparison operations

// Checks if the fist decimal is less than the second one
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

// Checks if the fist decimal is less or equal to the second one
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Checks if the first decimal is greater that the second one
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

// Checks if the fist decimal is greater or equal to the second one
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// Checks if both numbers are equal
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

// Checks if given numbers are not equal
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Conversion functions

// Int to decimal
int s21_from_int_to_decimal(int src, s21_decimal* dst);

// Float to decimal
int s21_from_float_to_decimal(float src, s21_decimal* dst);

// Decimal to int
int s21_from_decimal_to_int(s21_decimal src, int* dst);

// Decimal to float
int s21_from_decimal_to_float(s21_decimal src, float* dst);

// Arithmetic operations

// Subtraction
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Addition
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Multiplication
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Division
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Operations connected with big_decimal

// Conversion

// From s21_decimal to big_decimal
big_decimal to_big(s21_decimal decimal);

// From big_decimal to s21_decimal
int to_normal(big_decimal big, s21_decimal* decimal);

// Arithmetics

// Divides dividend by divisor and saves result in b_res
void division(big_decimal dividend, big_decimal divisor, big_decimal* b_res);

// Normalizes two big_decimal numbers so that both have the same exponent
void normalization_big(big_decimal* value_1, big_decimal* value_2);

// Multiplies numerator by ten
void mul_by_ten_numerator_big(big_decimal* decimal);

// Adds two big_decimal numbers (binary addition)
void addition(big_decimal value_1, big_decimal value_2, big_decimal* result);

// Subtracts value_2 from value_1 (binary subtraction)
void subtraction(big_decimal value_1, big_decimal value_2, big_decimal* result);

// Increases numerator by one
void increase_big_dec_by_one(big_decimal* value);

// Applies bankers' rounding to dec_to_round
void bankers_rounding(big_decimal remainder, big_decimal* dec_to_round);

// Counts maximum shift
int count_max_shift(big_decimal decimal);

// Divides decimal by ten
void div_by_ten_big(big_decimal* decimal, enum rounding round_method);

// Counts significant bits
int get_significant_bits(big_decimal big);

// Bit operations

// Gets bit by its number
int get_bit_big(big_decimal decimal, int bit_number);

// Sets bit by its number
void set_bit_big(big_decimal* decimal, int bit_number, int bit);

// Zeroes out big_decimal
void zero_out_big(big_decimal* big);

// Checks if decimal is zero
int is_big_dec_zero(big_decimal decimal);

// Shifts the decimal to the left by shift bits
void left_shift_big(big_decimal* decimal, int shift);

// Comparison

// Checks if two given big_decimal structures are equal
int is_equal_big(big_decimal value_1, big_decimal value_2);

// Checks if the first big decimal is less than the second one
int is_less_big(big_decimal value_1, big_decimal value_2);

// Checks if the first big decimal is greater than the second one
int is_greater_big(big_decimal value_1, big_decimal value_2);

// Checks if the first big decimal is greater or equal
int is_greater_or_equal_big(big_decimal value_1, big_decimal value_2);

// Checks if the first big decimal is less or equal
int is_less_or_equal_big(big_decimal value_1, big_decimal value_2);

// Returns the result of multiplying the specified Decimal value by negative one
int s21_negate(s21_decimal value, s21_decimal* result);

// Rounds a specified Decimal number to the closest integer toward negative
// infinity
int s21_truncate(s21_decimal value, s21_decimal* result);

// Rounds a specified Decimal number to the closest integer toward negative
// infinity
int s21_floor(s21_decimal value, s21_decimal* result);

// Rounds a decimal value to the nearest integer
int s21_round(s21_decimal value, s21_decimal* result);

#endif