#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

typedef unsigned long s21_size_t;
#define s21_NULL (void*)0

typedef union TypeRes{
    wchar_t *wchar_vl;
    char *vl;
}TypeRes;

typedef struct {
    char specifier;
    char flags[5];
    char *acuracy;
    char *widht;
    char lenght;
    char *result;
    TypeRes *new_res;
    s21_size_t len_res;
}FormatArg;

s21_size_t s21_str_lchar(wchar_t *str, wchar_t *dest);
int s21_len_float(double acc);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_sprintf(char *str, const char *format, ...);

#endif