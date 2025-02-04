#include "s21_string.h"

int main(void){
    // printf("%s\n", (char*)memchr("dsadas", 'a', 3));
    // printf("%s", (char*)s21_memchr("dsadas", 'a', 3));
    
    // printf("%d\n", memcmp("abc", "ab3", 3));
    // printf("%d\n", s21_memcmp("abc", "ab3", 3));

    char str[100] = "ghbdt";
    char str1[100] = "ghbdt";
    s21_size_t res = s21_sprintf(str + 5, "%-10c %+20d %.10f %s %u", 'q', -10, -11.1, "str", -99);
    sprintf(str1 + 5, "%-10c %+20d %.10f %s %u", 'q', -10, -11.1, "str", -99);
    printf("%s\n", str);
    printf("%s\n", str1);
    return 0;
}

// void *s21_memchr(const void *str, int c, size_t n){
//     void *result = NULL;
//     char *cur = (char*)str;
//     unsigned char temp = (unsigned char)c;
//     for(char *i = cur; i - cur <= n; i++){
//         if(*i == c) result = i;
//     }
//     return result;
// }

// int s21_memcmp(const void *str1, const void *str2, size_t n){
//     char *temp1 = (char*)str1, *temp2 = (char*)str2;
//     char *i = temp1, *j = temp2;
//     int total = 0;
//     for( ; i - temp1 <= n && j - temp2 <= n; i++, j++){
//         if(*i == *j) continue;
//         else if(*i < *j) total--;
//         else if(*i > *j) total++;
//     }
//     return total;
// }

s21_size_t s21_strlen(const char *str){
    s21_size_t res = 0;
    if(str != s21_NULL){
        while(*str != '\0'){
            str++;
            res++;
        }
    }
    return res;
}

static char *s21_revers(char *str){
    s21_size_t left = 0, right = s21_strlen(str) - 1;
    if(left != right){
        while(left <= right){
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
    for(char *pt = dest; (s21_size_t)(pt - dest) < s21_strlen(dest); pt++){
        str[id_str++] = *pt;
    }
    return id_str;
}

static int s21_digit_to_str(char *str, int digit){
    int id_new = 0, temp = 0, id_str = 0;
    bool flag_negative = false;
    if((int)digit < 0){
        digit = ~digit + 1;
        flag_negative = true;
    }
    char *new = (char*)malloc(sizeof(char));
    do{
        temp = digit % 10;
        new[id_new++] = temp + 48;
        digit /= 10;
        new = (char*)realloc(new, id_new + 1);
    } while(digit != 0);
    new[id_new] = '\0';
    new = s21_revers(new);

    for(char *pt = new; pt - new < id_new; pt++){
        str[id_str++] = *pt;
    }
    free(new);
    str[id_str] = '\0';
    return id_str;
}

static int s21_float_to_digit(char *str, float num){ // переделать функциию как автономную для float/double чисел
    int temp = (int)num, id = 0;
    id = s21_digit_to_str(str, temp);
    str[id++] = '.';
    int number = (num - (int)num) * 10;
    number = ~number + 1;
    id += s21_digit_to_str(str + id, number);
    return id;
}

static FormatArg s21_initArg() {
    FormatArg new = {0};
    new.acuracy = (char*)calloc(1, sizeof(char)); // Используем calloc, чтобы сразу обнулить
    new.widht = (char*)calloc(1, sizeof(char));
    new.result = (char*)calloc(1, sizeof(char));
    new.arg = s21_NULL;
    return new;
}

static void s21_clearArg(FormatArg *cur){
    free(cur->acuracy);
    // free(cur->arg);
    
    free(cur->result);
    free(cur->widht);
    cur->arg = cur->result = cur->acuracy = cur->widht = s21_NULL;
    // free(cur);
}

static void s21_parse_specifier(FormatArg *cur_arg, char specifier, va_list argc){
    switch(specifier){
        case 'c':        
            cur_arg->specifier = 'c';
            cur_arg->arg = (void*)(uintptr_t)va_arg(argc, int);
            break;
        case 'd':
            cur_arg->specifier = 'd';
            cur_arg->arg = (void*)(uintptr_t)va_arg(argc, int);
            break;
        case 'f':
            cur_arg->specifier = 'f';
            cur_arg->arg_double = va_arg(argc, double);
            break;
        case 's':
            cur_arg->specifier = 's';
            cur_arg->arg = va_arg(argc, char*);
            break;
        case 'u':
            cur_arg->specifier = 'u';
            cur_arg->arg = (void*)(uintptr_t)va_arg(argc, unsigned int);
            break;
        case 'l':
            cur_arg->lenght = 'l';
            break;
        case 'h':
            cur_arg->lenght = 'h';
            break;
    }
}

static int s21_copy_to_arg(const char *str, char **dest){
    s21_size_t count_len = 0;
    while(*str >= '0' && *str <= '9'){
        char *temp = (char*)realloc(*dest, count_len + 2);
        *dest = temp;
        (*dest)[count_len++] = *str;
        str++;
    }
    (*dest)[count_len] = '\0';
    return count_len;
}

static int s21_parse_flags(const char *format, char temp, FormatArg *cur_arg){
    const char *cur = format;
    switch(temp){
        case '+':
            strcat(cur_arg->flags, "+");
            if(*(cur + 1) >= 48 || *(cur + 1) <= 57){
                cur++;
                cur += s21_copy_to_arg(cur, &cur_arg->widht);
            }
            break;
        case '-':
            strcat(cur_arg->flags, "-");
            if(*(cur + 1) >= 48 || *(cur + 1) <= 57){
                cur++;
                cur += s21_copy_to_arg(cur, &cur_arg->widht);
            }
            break;
        case ' ':
            strcat(cur_arg->flags, " ");
            cur++;
            break;
        case '.':
            cur++;
            cur += s21_copy_to_arg(cur, &cur_arg->acuracy);
            break;
    }
    return cur - format;
}

static void s21_write_widht(FormatArg *cur_arg, s21_size_t *size_res){
    if(s21_strlen(cur_arg->widht)) *size_res += atoi(cur_arg->widht);
    cur_arg->result = (char*)realloc(cur_arg->result, *size_res);
    char *pt = cur_arg->result;
    for(int i = 0; i < atoi(cur_arg->widht) && pt - cur_arg->result < *size_res; i++){
        *pt = ' ';
        pt++;
    }
}

static int s21_make_res_resstr(FormatArg cur_arg, char *str){
    s21_size_t size_res = 0;
    if(s21_strlen(cur_arg.flags)){
        s21_size_t len_flags = s21_strlen(cur_arg.flags);
        for(char *pt = cur_arg.flags; pt - cur_arg.flags < len_flags; pt++){
            if(*pt == '+' && (cur_arg.specifier == 'd' || cur_arg.specifier == 'u' || cur_arg.specifier == 'f')){
                s21_write_widht(&cur_arg, &size_res);
                int temp = (int)(uintptr_t)cur_arg.arg;
                cur_arg.result[size_res++] = (temp < 0) ? '-' : '+';
                cur_arg.result = realloc(cur_arg.result, size_res + 11);
                if(cur_arg.specifier == 'd' || cur_arg.specifier == 'u'){
                    size_res += s21_digit_to_str(&cur_arg.result[size_res], temp);
                }
                if(cur_arg.specifier == 'f'){
                    size_res += s21_float_to_digit(cur_arg.result, cur_arg.arg_double);
                }
            }
            if(*pt == '-'){
                if(cur_arg.specifier == 'd' || cur_arg.specifier == 'u'){
                    size_res += s21_digit_to_str(cur_arg.result, (int)(uintptr_t)cur_arg.arg);
                }
                if(cur_arg.specifier == 'f'){
                    size_res += s21_float_to_digit(cur_arg.result, cur_arg.arg_double);
                }
                s21_write_widht(&cur_arg, &size_res);
            }
        }
        cur_arg.result[size_res] = '\0';
        s21_str(str, cur_arg.result);
    }
    return s21_strlen(str);
}

s21_size_t s21_sprintf(char *str, const char *format, ...){
    va_list argc;
    va_start(argc, format);
    s21_size_t format_len = s21_strlen(format);
    FormatArg cur_arg = s21_initArg();
    char *cur2 = str;
    for(const char *cur1 = format; cur1 - format < format_len; cur1++){
        if(*cur1 == '%'){
            char temp = *(++cur1);
            cur1 += s21_parse_flags(cur1, temp, &cur_arg);
            if(*cur1 >= 92 || *cur1 <= 122){
                s21_parse_specifier(&cur_arg, *cur1, argc);
            }
        } else {
            cur2 += s21_make_res_resstr(cur_arg, cur2);
            s21_clearArg(&cur_arg);
            *cur2 = *cur1;
            cur2++;
            cur_arg = s21_initArg();
        }
    }
    va_end(argc);
    return s21_strlen(str);
}