SYSSHELL:=$(shell uname)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
ifeq ($(SYSSHELL), Linux)
TFLAGS=-lcheck -lpthread -lrt -lsubunit --coverage -lm
else
TFLAGS=$(shell pkg-config --cflags --libs check) --coverage
endif

.PHONY: all s21_decimal.a test gcov_report rebuild clean

all: s21_decimal.a test gcov_report

s21_decimal.a:
	$(CC) $(CFLAGS) *.c -c
	ar rc s21_decimal.a *.o
	rm -rf *.o

test: s21_decimal.a
	$(CC) $(CFLAGS) ./tests/*.c $(TFLAGS) -c
	$(CC) $(CFLAGS) ./tests/*.c *.c $(TFLAGS) -o test -L. s21_decimal.a
	./test

gcov_report: test
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . 
	genhtml -o report s21_decimal.info

rebuild: clean test

clean:
	rm -rf *.gcno *.info *.gcda *.o *.a s21_decimal test report
	