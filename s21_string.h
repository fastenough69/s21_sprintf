#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

typedef unsigned long s21_size_t;
#define s21_NULL (void*)0

typedef struct {
    char specifier;
    char flags[5];
    char *acuracy;
    char *widht;
    char lenght;
    char *result;
    void *arg;
    double arg_double;
}FormatArg;

void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
s21_size_t s21_sprintf(char *str, const char *format, ...);
s21_size_t s21_strlen(const char *str);
static char *s21_revers(char *str);
static s21_size_t s21_str(char *str, char *dest);
static int s21_digit_to_str(char *str, int digit);
static int s21_float_to_digit(char *str, float num);

#endif