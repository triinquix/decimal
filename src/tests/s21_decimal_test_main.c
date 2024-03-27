#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal_test.h"

int main(void) {
  int failed = 0;
  int num_of_tests = 0;
  Suite *s_1, *s_2, *s_3, *s_4, *s_5, *s_6, *s_7, *s_8, *s_9, *s_10, *s_11,
      *s_12, *s_13, *s_14, *s_15, *s_16, *s_17, *s_18;
  SRunner *runner_1, *runner_2, *runner_3, *runner_4, *runner_5, *runner_6,
      *runner_7, *runner_8, *runner_9, *runner_10, *runner_11, *runner_12,
      *runner_13, *runner_14, *runner_15, *runner_16, *runner_17, *runner_18;

  s_1 = suite_is_less();
  s_2 = suite_is_greater();
  s_3 = suite_is_equal();
  s_4 = suite_is_not_equal();
  s_5 = suite_is_less_or_equal();
  s_6 = suite_is_greater_or_equal();
  s_7 = suite_floor();
  s_8 = suite_negate();
  s_9 = suite_truncate();
  s_10 = suite_round();
  s_11 = suite_add();
  s_12 = suite_sub();
  s_13 = suite_mul();
  s_14 = suite_div();
  s_15 = suite_from_int_to_decimal();
  s_16 = suite_from_float_to_decimal();
  s_17 = suite_from_decimal_to_int();
  s_18 = suite_from_decimal_to_float();

  runner_1 = srunner_create(s_1);
  printf("\033[1;32mRUNNING IS_LESS TESTS\033[1;0m\n");
  srunner_run_all(runner_1, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_1);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_2 = srunner_create(s_2);
  printf("\033[1;32mRUNNING IS_GREATER TESTS\033[1;0m\n");
  srunner_run_all(runner_2, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_2);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_3 = srunner_create(s_3);
  printf("\033[1;32mRUNNING IS_EQUAL TESTS\033[1;0m\n");
  srunner_run_all(runner_3, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_3);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_4 = srunner_create(s_4);
  printf("\033[1;32mRUNNING IS_NOT_EQUAL TESTS\033[1;0m\n");
  srunner_run_all(runner_4, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_4);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_5 = srunner_create(s_5);
  printf("\033[1;32mRUNNING IS_LESS_OR_EQUAL TESTS\033[1;0m\n");
  srunner_run_all(runner_5, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_5);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_6 = srunner_create(s_6);
  printf("\033[1;32mRUNNING IS_GREATER_OR_EQUAL TESTS\033[1;0m\n");
  srunner_run_all(runner_6, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_6);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_7 = srunner_create(s_7);
  printf("\033[1;32mRUNNING FLOOR TESTS\033[1;0m\n");
  srunner_run_all(runner_7, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_7);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_8 = srunner_create(s_8);
  printf("\033[1;32mRUNNING NEGATE TESTS\033[1;0m\n");
  srunner_run_all(runner_8, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_8);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_9 = srunner_create(s_9);
  printf("\033[1;32mRUNNING TRUNCATE TESTS\033[1;0m\n");
  srunner_run_all(runner_9, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_9);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_10 = srunner_create(s_10);
  printf("\033[1;32mRUNNING ROUND TESTS\033[1;0m\n");
  srunner_run_all(runner_10, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_10);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_11 = srunner_create(s_11);
  printf("\033[1;32mRUNNING ADD TESTS\033[1;0m\n");
  srunner_run_all(runner_11, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_11);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_12 = srunner_create(s_12);
  printf("\033[1;32mRUNNING SUB TESTS\033[1;0m\n");
  srunner_run_all(runner_12, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_12);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_13 = srunner_create(s_13);
  printf("\033[1;32mRUNNING MUL TESTS\033[1;0m\n");
  srunner_run_all(runner_13, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_13);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_14 = srunner_create(s_14);
  printf("\033[1;32mRUNNING DIV TESTS\033[1;0m\n");
  srunner_run_all(runner_14, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_14);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_15 = srunner_create(s_15);
  printf("\033[1;32mRUNNING FROM_INT_TO_DECIMAL TESTS\033[1;0m\n");
  srunner_run_all(runner_15, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_15);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_16 = srunner_create(s_16);
  printf("\033[1;32mRUNNING FROM_FLOAT_TO_DECIMAL TESTS\033[1;0m\n");
  srunner_run_all(runner_16, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_16);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_17 = srunner_create(s_17);
  printf("\033[1;32mRUNNING FROM_DECIMAL_TO_INT TESTS\033[1;0m\n");
  srunner_run_all(runner_17, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_17);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);
  printf("\n");

  runner_18 = srunner_create(s_18);
  printf("\033[1;32mRUNNING FROM_DECIMAL_TO_FLOAT TESTS\033[1;0m\n");
  srunner_run_all(runner_18, CK_VERBOSE);
  num_of_tests += srunner_ntests_run(runner_18);
  printf("\033[1;33m[+] Total number of tests run -> %d\033[1;0m\n",
         num_of_tests);

  failed = srunner_ntests_failed(runner_1) + srunner_ntests_failed(runner_2) +
           srunner_ntests_failed(runner_3) + srunner_ntests_failed(runner_4) +
           srunner_ntests_failed(runner_5) + srunner_ntests_failed(runner_6) +
           srunner_ntests_failed(runner_7) + srunner_ntests_failed(runner_8) +
           srunner_ntests_failed(runner_9) + srunner_ntests_failed(runner_10) +
           srunner_ntests_failed(runner_11) + srunner_ntests_failed(runner_12) +
           srunner_ntests_failed(runner_13) + srunner_ntests_failed(runner_14) +
           srunner_ntests_failed(runner_15) + srunner_ntests_failed(runner_16) +
           srunner_ntests_failed(runner_17) + srunner_ntests_failed(runner_18);

  srunner_free(runner_1);
  srunner_free(runner_2);
  srunner_free(runner_3);
  srunner_free(runner_4);
  srunner_free(runner_5);
  srunner_free(runner_6);
  srunner_free(runner_7);
  srunner_free(runner_8);
  srunner_free(runner_9);
  srunner_free(runner_10);
  srunner_free(runner_11);
  srunner_free(runner_12);
  srunner_free(runner_13);
  srunner_free(runner_14);
  srunner_free(runner_15);
  srunner_free(runner_16);
  srunner_free(runner_17);
  srunner_free(runner_18);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}