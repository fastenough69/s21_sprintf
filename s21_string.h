#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
// #include <stdint.h>

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
    s21_size_t len_res;
}FormatArg;

int s21_len_float(double acc);
s21_size_t s21_sprintf(char *str, const char *format, ...);
s21_size_t s21_strlen(const char *str);

#endif