// не забыть поменять названия на свои функции, а не из string.h
#include "s21_string.h"

// int main(void){
//     // // char str[100] = "ghbdt";
//     // // char str1[100] = "ghbdt";
//     // // // s21_sprintf(str + 5, "%+10da %10s %10c %d", 1, "fdsfsd", 'c', -1);
//     // // // sprintf(str1 + 5, "%+10da %10s %10c %d", 1, "fdsfsd", 'c', -1);
//     // // long digit = 324534543;
//     // // s21_sprintf(str + 5, "%+-10.1d %-10.2s %+-.8f %c, %ld", 205, "fsdfs", 11.0021, 'c', digit);
//     // // sprintf(str1 + 5, "%+-10.1d %-10.2s %+-.8f %c, %ld", 205, "fsdfs", 11.0021, 'c', digit);
//     // // printf("%s\n", str);
//     // // printf("%s\n", str1);
//     char str1[512] = {'\0'};
//     char str2[512] = {'\0'};
//     char *str3 = "%.0f";
//     double val = 15.35;
//     printf("%d %d\n", sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
//     printf("%s\n", str1);
//     printf("%s\n", str2);
//     return 0;
// }

s21_size_t s21_strlen(const char *str){
    s21_size_t res = 0;
    if(str){
        while(*str != '\0'){
            str++;
            res++;
        }
    }
    return res;
}

static void s21_safe_realloc(char **ptr, s21_size_t new_size){
    if(!ptr || !new_size) return;
    char *temp = (char*)realloc(*ptr, new_size);
    if(temp){
        *ptr = temp;
    }
}

static char *s21_revers(char *str){
    s21_size_t left = 0, right = s21_strlen(str) - 1;
    if(left != right){
        while(left < right){
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
    return str;
}

static s21_size_t s21_str(char *str, char *dest){
    s21_size_t id_str = 0;
    s21_size_t len_dest = s21_strlen(dest);
    for(char *pt = dest; (s21_size_t)(pt - dest) < len_dest; pt++){
        str[id_str++] = *pt;
    }
    return id_str;
}

static long long s21_digitLong_to_str(char *str, long long digit){
    long long id_new = 0, temp = 0, id_str = 0;
    bool flag_negative = false;
    if((long)digit < 0){
        digit = ~digit + 1;
        flag_negative = true;
    }
    char *new = (char*)malloc(100);
    *new = '\0';
    do{
        temp = digit % 10;
        new[id_new++] = temp + 48;
        digit /= 10;
    } while(digit != 0);
    if(flag_negative){
        new[id_new++] = '-';
    }
    new[id_new] = '\0';
    new = s21_revers(new);

    for(char *pt = new; pt - new < id_new; pt++){
        str[id_str++] = *pt;
    }
    free(new);
    str[id_str] = '\0';
    return id_str;
}

static int s21_float_to_digit(char *str, long double num, int precision) {
    // Обрабатываем целую часть
    long temp = (long)num;
    int id = s21_digitLong_to_str(str, temp);
    if(precision != 0){
        str[id++] = '.';
        
        // Обрабатываем дробную часть
        long double fractional_part = num - temp;
        if (fractional_part < 0) fractional_part = -fractional_part;
        
        // Округляем дробную часть
        double multiplier = 1;
        for (int i = 0; i < precision; i++) {
            multiplier *= 10;
        }
        long long fraction = (long long)(fractional_part * multiplier + 0.5);

        // Добавляем ведущие нули, если необходимо
        long zeros_to_add = precision - s21_digitLong_to_str(str + id, fraction);
        for (int i = 0; i < zeros_to_add; i++) {
            str[id++] = '0';
        }

        // Добавляем саму дробную часть
        id += s21_digitLong_to_str(str + id, fraction);
    }
    str[id] = '\0';

    
    return id;
}


static FormatArg s21_initArg() {
    FormatArg new = {0};
    new.acuracy = (char*)malloc(sizeof(char) * 2);
    new.acuracy[0] = '\0';
    new.widht = (char*)malloc(sizeof(char) * 2);
    new.widht[0] = '\0';
    new.result = (char*)malloc(sizeof(char) * 2);
    return new;
}

static void s21_clearArg(FormatArg *cur) {
    if (cur->acuracy) {
        free(cur->acuracy);
        cur->acuracy = NULL;
    }
    if (cur->widht) {
        free(cur->widht);
        cur->widht = NULL;
    }
    if (cur->result) {
        free(cur->result);
        cur->result = NULL;
    }
}

static int s21_len_digitLong(long long digit){
    int count = 0;
    do{
        // temp = digit % 10;
        digit /= 10;
        count++;
    } while(digit != 0);
    return count;
}

int s21_len_float(double acc){
    int count = 0;
    long integer = (long)acc;  
    while (integer != acc) {
        acc *= 10;
        count++;
        integer = (long)acc;
    }
    return count;
}

static int s21_parse_lenght(FormatArg *cur_arg, char *symbol){
    int res = 0;
    if(*symbol == 'h' || *symbol == 'l'){
        cur_arg->lenght = *symbol;
        res++;
    }
    return res;
}

static void s21_read_digit(s21_size_t *new_size, FormatArg *cur_arg, va_list argc){
    if(cur_arg->lenght == 'l'){
        long temp_lgd = va_arg(argc, long);
        *new_size = s21_len_digitLong(temp_lgd) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, (long long)temp_lgd);
    /*...*/
    }else if(cur_arg->lenght == 'h'){
        short int temp_sh = (short int)va_arg(argc, int);
        *new_size = s21_len_digitLong(temp_sh) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, temp_sh);
    } else {
        int temp = va_arg(argc, int);
        *new_size = s21_len_digitLong(temp) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, temp);
    }
}

static void s21_read_unumber(s21_size_t *new_size, FormatArg *cur_arg, va_list argc){
    if(cur_arg->lenght == 'l'){
        unsigned long int temp_ulg = va_arg(argc, unsigned long);
        *new_size = s21_len_digitLong(temp_ulg) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, temp_ulg);
        /*...*/
    } else if(cur_arg->lenght == 'h'){
        unsigned short temp_ulg = (unsigned short)va_arg(argc, unsigned int);
        *new_size = s21_len_digitLong(temp_ulg) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, temp_ulg);
    } else {
        unsigned int temp_uint = va_arg(argc, unsigned int);
        *new_size = s21_len_digitLong(temp_uint) + 2;
        s21_safe_realloc(&cur_arg->result, *new_size);
        s21_digitLong_to_str(cur_arg->result, temp_uint);
    }
}

static void s21_read_float_number(s21_size_t *new_size, FormatArg *cur_arg, va_list argc){
    int acuracy;
    if(*(cur_arg->acuracy) == '-'){
        acuracy = 0;
    } else if(s21_strlen(cur_arg->acuracy)){
        acuracy = atoi(cur_arg->acuracy);
        // acuracy = (acuracy == 0) ? 6 : acuracy;
    } else {
        acuracy = 6;
    }
    // acuracy = (acuracy == 0) ? 6 : acuracy;
    double temp_flo = va_arg(argc, double);
    *new_size = s21_len_digitLong((long)temp_flo) + s21_len_float(temp_flo) + acuracy + 2;
    s21_safe_realloc(&cur_arg->result, *new_size);
    s21_float_to_digit(cur_arg->result, temp_flo, acuracy);
}

static void s21_parse_specifier(FormatArg *cur_arg, char specifier, va_list argc){ // разделить на функции
    s21_size_t new_size = 0;
    switch(specifier){
        case 'c':        
            cur_arg->specifier = 'c';
            char temp_ch = va_arg(argc, int);
            new_size++;
            s21_safe_realloc(&cur_arg->result, new_size + 1);
            cur_arg->result[0] = temp_ch;
            cur_arg->result[1] = '\0';
            break;
        case 'd':
            cur_arg->specifier = 'd';
            s21_read_digit(&new_size, cur_arg, argc);
            break;
        case 'f':
            cur_arg->specifier = 'f';
            s21_read_float_number(&new_size, cur_arg, argc);
            break;
        case 's':
            cur_arg->specifier = 's'; // попробовать сделать  s h
            char *temp_str = va_arg(argc, char*);
            new_size = s21_strlen(temp_str);
            s21_safe_realloc(&cur_arg->result, new_size + 1);
            s21_str(cur_arg->result, temp_str);
            cur_arg->result[new_size] = '\0';
            break;
        case 'u':
            cur_arg->specifier = 'u';
            s21_read_unumber(&new_size, cur_arg, argc);
            break;
    }
    cur_arg->len_res = s21_strlen(cur_arg->result);
}

static int s21_copy_to_arg(const char *str, char **dest){
    s21_size_t count_len = 0;
    (*dest)[count_len] = 48;
    while(*str >= '0' && *str <= '9'){
        s21_safe_realloc(dest, ++count_len + 1);
        (*dest)[count_len - 1] = *str;
        str++;
    }
    (*dest)[count_len] = '\0';
    return count_len;
}

static int s21_parse_flags(const char *format, FormatArg *cur_arg){ // разделить эту функцию
    const char *cur = format;
    do{
        switch(*cur){
            case '+':
                strncat(cur_arg->flags, "+", 5);
                if(*(cur + 1) >= 48 || *(cur + 1) <= 57){ // вынести под отдельную функцию
                    cur++;
                    cur += s21_copy_to_arg(cur, &cur_arg->widht);
                }
                break;
            case '-':
                strncat(cur_arg->flags, "-", 5);
                if(*(cur + 1) >= 48 || *(cur + 1) <= 57){
                    cur++;
                    cur += s21_copy_to_arg(cur, &cur_arg->widht);
                }
                break;
            case ' ':
                strncat(cur_arg->flags, " ", 5);
                if(*(cur) >= 48 || *(cur) <= 57){
                    cur++;
                    cur += s21_copy_to_arg(cur, &cur_arg->widht);
                }
                break;
            case '.':
                cur++;
                if(*(cur) >= 48 && *(cur) <= 57){
                    cur += s21_copy_to_arg(cur, &cur_arg->acuracy);
                } else {
                    s21_safe_realloc(&cur_arg->acuracy, 2);
                    cur_arg->acuracy[0] = '-';
                    cur_arg->acuracy[1] = '\0';
                }
                break;
            default:
                if(*(cur) >= 48 || *(cur) <= 57){
                    cur += s21_copy_to_arg(cur, &cur_arg->widht);
                }
        }
    } while(*cur == '-' || *cur == ' ' || *cur == '+' || *cur == '.');
    return cur - format;
}

static void s21_write_widht(char *arg_widht ,char **res, s21_size_t *size){
    int width = atoi(arg_widht);
    if (width <= 0) return; 
    *size += width + 1;

    s21_safe_realloc(res, width + 1);
    if(!res) return;
    *res = memset(*res, ' ', width);
    (*res)[width] = '\0';
}

static void s21_make_flags(FormatArg cur_arg, bool *flag_symbol, char *symbol, bool *negative_flag){
    s21_size_t len_flags = s21_strlen(cur_arg.flags);
    for(char *pt = cur_arg.flags; (s21_size_t)(pt - cur_arg.flags) < len_flags; pt++){
        if(*pt == '+' && (cur_arg.specifier == 'd' || cur_arg.specifier == 'f')){
            int digit = atoi(cur_arg.result); 
            *flag_symbol |= true;
            if(digit > 0){
                *symbol = '+';
            }
        }
        if(*pt == '-'){
            *negative_flag |= true;
        }
        if(*pt == ' ' && (cur_arg.specifier == 'd' || cur_arg.specifier == 'f') && strchr(cur_arg.flags, '+') == NULL){
            int digit = atoi(cur_arg.result);
            *flag_symbol |= true;
            if(digit >= 0){
                *symbol = ' ';
            }
        }
    }
}

static s21_size_t s21_make_acuracy(FormatArg *cur_arg, s21_size_t *size_arg, s21_size_t size, char **temp){
    int acuracy;
    if(*(cur_arg->acuracy) != '-'){
        acuracy = atoi(cur_arg->acuracy);
        
    }
    if(cur_arg->specifier == 'd' || cur_arg->specifier == 'u'){
        if((s21_size_t)acuracy > cur_arg->len_res){
            *size_arg = acuracy + 1;
            s21_safe_realloc(temp, *size_arg);
            (*temp)[*size_arg - 1] = '\0';
            memset(*temp, '0', acuracy);
            s21_size_t j = 0; 
            for(int i = acuracy - cur_arg->len_res; i < acuracy && j <= cur_arg->len_res; i++){
                (*temp)[i] = cur_arg->result[j++];
            }
            cur_arg->result = *temp;
            cur_arg->len_res = acuracy;
        }
        if(cur_arg->len_res + 1 > size){
            size = cur_arg->len_res + 1;
        }
        (*temp)[*size_arg - 1] = '\0';
    }
    
    return size;
}

static void s21_write_res(FormatArg cur_arg, bool negative_flag, s21_size_t *size, char **res){
    int id_arg = cur_arg.len_res - 1;
    if(!negative_flag){
        if(*size - 2 < cur_arg.len_res - 1){
            *size += 1;
            s21_safe_realloc(res, *size);
        }
        for(int i = *size - 2; i >= 0; i--){
            if(id_arg >= 0)
                (*res)[i] = cur_arg.result[id_arg--];
        }
    } else {
        id_arg = 0;
        if(*size - 2 < cur_arg.len_res - 1){
            *size += 1;
            s21_safe_realloc(res, *size);
        }
        for(int i = 0; (s21_size_t)id_arg < cur_arg.len_res; i++){
            (*res)[i] = cur_arg.result[id_arg++];
        }
    }
}

static void s21_write_symbol_digit(FormatArg *cur_arg, char **copy, s21_size_t *size_arg, char symbol){
    int digit = atoi(cur_arg->result);
    if(digit >= 0){
        *size_arg = cur_arg->len_res + 2;
        s21_safe_realloc(copy, *size_arg);
        (*copy)[*size_arg - 1] = '\0';
        s21_size_t index = 0;
        for(s21_size_t i = 1; i < *size_arg - 1 && index < cur_arg->len_res; i++){
            (*copy)[i] = cur_arg->result[index++];
        }
        cur_arg->len_res++;
        (*copy)[0] = symbol;
        cur_arg->result = *copy;
    }
}

static int s21_make_res_resstr(FormatArg cur_arg, char *str){
    char *res = malloc(sizeof(char) * 2);
    *res = '\0';
    s21_size_t size = 0;
    if(s21_strlen(cur_arg.widht) && (s21_size_t)atoi(cur_arg.widht) > cur_arg.len_res) s21_write_widht(cur_arg.widht, &res, &size);
    else{
        size = cur_arg.len_res + 1;
        if(size){
            s21_safe_realloc(&res, size);
            memset(res, ' ', size);
        }
    }
    res[size - 1] = '\0';
    s21_size_t size_arg = cur_arg.len_res + 2;
    char *temp = malloc(sizeof(char) * size_arg);
    temp[size_arg - 1] = '\0';
    char *copy = malloc(sizeof(char) * (cur_arg.len_res + 1));
    copy[cur_arg.len_res] = '\0';

    char symbol = 0;
    bool flag_symbol = false;
    bool negative_flag = false;
    if(s21_strlen(cur_arg.flags)){
        s21_make_flags(cur_arg, &flag_symbol, &symbol, &negative_flag);
    }
    if(s21_strlen(cur_arg.acuracy) && *(cur_arg.acuracy) != '-'){
        s21_size_t temp_size = s21_make_acuracy(&cur_arg, &size_arg, size, &temp);
        if(temp_size > size){
            size = temp_size - 1;
            s21_safe_realloc(&res, size);
            memset(res, ' ', size);
            res[size - 1] = '\0';
        }
        if(cur_arg.specifier == 's'){
            int acuracy;
            if(*(cur_arg.acuracy) != '-'){
                acuracy = atoi(cur_arg.acuracy);
            }
            if((s21_size_t)acuracy <= cur_arg.len_res){
                cur_arg.len_res = acuracy;
            }
            if((s21_size_t)acuracy <= size){
                size = cur_arg.len_res + 1;
                s21_safe_realloc(&res, size);
                res[size - 1] = '\0';
            }
        }
    }
    if(flag_symbol){
        s21_write_symbol_digit(&cur_arg, &copy, &size_arg, symbol);
    }
    s21_write_res(cur_arg, negative_flag, &size, &res);
    res[size - 1] = '\0';
    s21_str(str, res);
    if(temp) free(temp);
    if(copy) free(copy);
    free(res);
    return s21_strlen(str);
}

int s21_sprintf(char *str, const char *format, ...){
    va_list argc;
    va_start(argc, format);
    s21_size_t format_len = s21_strlen(format);
    FormatArg cur_arg = s21_initArg();
    char *cur2 = str;
    for(const char *cur1 = format; (s21_size_t)(cur1 - format) < format_len; cur1++){
        if(*cur1 == '%'){
            ++cur1;
            cur1 += s21_parse_flags(cur1, &cur_arg);
            if(*cur1 >= 92 || *cur1 <= 122){
                cur1 += s21_parse_lenght(&cur_arg, (char*)cur1);
                s21_parse_specifier(&cur_arg, *cur1, argc);
            }
        } else {
            *cur2 = *cur1;
            cur2++;
            continue;
        }
        cur2 += s21_make_res_resstr(cur_arg, cur2);
        s21_clearArg(&cur_arg);
        cur_arg = s21_initArg();
    }
    s21_clearArg(&cur_arg);
    va_end(argc);
    return (int)s21_strlen(str);
}