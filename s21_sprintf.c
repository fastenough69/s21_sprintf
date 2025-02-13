#include "s21_string.h"

int main(void){
    char str[100] = "ghbdt";
    char str1[100] = "ghbdt";
    // s21_size_t res = s21_sprintf(str + 5, "%-10c %+d %.10f %s %u", 'q', -10, -11.1, "str", -99);
    // s21_sprintf(str + 5, "%.10f %+10da %s", 11.4324, -10, "fdsfsd");
    s21_sprintf(str + 5, "%+10da %s", -10, "fdsfsd");
    sprintf(str1 + 5, "%-10da %s", -10, "fdsfsd");
    printf("%s\n", str);
    printf("%s\n", str1);
    return 0;
}

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
    for(char *pt = dest; (s21_size_t)(pt - dest) < s21_strlen(dest); pt++){
        str[id_str++] = *pt;
    }
    return id_str;
}

static int s21_digit_to_str(char *str, int digit){ // нужно переделать
    int id_new = 0, temp = 0, id_str = 0;
    bool flag_negative = false;
    if((int)digit < 0){
        digit = ~digit + 1;
        flag_negative = true;
    }
    char *new = (char*)malloc(12);
    *new = '\0';
    do{
        temp = digit % 10;
        new[id_new++] = temp + 48;
        digit /= 10;
    } while(digit != 0);
    // if(flag_negative){
    //     new[id_new++] = '-';
    // }
    new[id_new] = '\0';
    new = s21_revers(new);

    for(char *pt = new; pt - new < id_new; pt++){
        str[id_str++] = *pt;
    }
    free(new);
    str[id_str] = '\0';
    return id_str;
}

static int s21_float_to_digit(char *str, float num){
    int temp = (int)num, id = 0;
    id = s21_digit_to_str(str, temp);
    str[id++] = '.';
    float number = (num - (int)num);
    int digit = (int)number;
    int count = 0;
    while(number != digit && count != 6){
        number *= 10;
        count++;
        digit = (int)number;
    }
    if(digit < 0) digit = ~digit + 1;
    id += s21_digit_to_str(str + id, digit);
    return id;
}

static FormatArg s21_initArg() {
    FormatArg new = {0};
    new.acuracy = (char*)malloc(sizeof(char) * 2);
    new.acuracy[0] = '\0';
    new.widht = (char*)malloc(sizeof(char) * 2);
    new.widht[0] = '\0';
    new.result = (char*)malloc(sizeof(char) * 2);
    new.arg = s21_NULL;
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
    cur->arg = NULL;
}

static int s21_len_digit(int digit){
    int temp = 0, count = 0;
    do{
        temp = digit % 10;
        digit /= 10;
        count++;
    } while(digit != 0);
    return count;
}

int s21_len_float(double acc){
    int count = 0;
    int integer = (int)acc;  // берём целую часть числа
    while (integer != acc)  // сравниваем целую часть числа с самим числом
    {
        acc *= 10;  // если нужно, то добавляем в целую часть числа новую цифру
        count++;
        integer = (int)acc;
    }
    return count;
}

static void s21_parse_specifier(FormatArg *cur_arg, char specifier, va_list argc){ // тут додлать шорт лонг
    s21_size_t new_size = 0;
    switch(specifier){
        case 'c':        
            cur_arg->specifier = 'c';
            cur_arg->arg = (void*)(uintptr_t)va_arg(argc, int);
            break;
        case 'd':
            cur_arg->specifier = 'd';
            int temp = va_arg(argc, int);
            s21_safe_realloc(&cur_arg->result, s21_len_digit(temp) + 1);
            s21_digit_to_str(cur_arg->result, temp);
            break;
        case 'f':
            cur_arg->specifier = 'f';
            double temp_flo = va_arg(argc, double);
            new_size = s21_len_digit((int)temp_flo) + s21_len_float(temp_flo) + 6;
            s21_safe_realloc(&cur_arg->result, new_size);
            s21_float_to_digit(cur_arg->result, temp_flo);
            break;
        case 's':
            cur_arg->specifier = 's';
            char *temp_str = va_arg(argc, char*);
            new_size = s21_strlen(temp_str);
            s21_safe_realloc(&cur_arg->result, new_size + 1);
            s21_str(cur_arg->result, temp_str);
            cur_arg->result[new_size] = '\0';
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
        s21_safe_realloc(dest, ++count_len + 1);
        // char *temp = (char*)realloc(*dest, ++count_len + 1);
        // *dest = temp;
        (*dest)[count_len - 1] = *str;
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
        default:
            if(*(cur) >= 48 || *(cur) <= 57){
                cur += s21_copy_to_arg(cur, &cur_arg->widht);
            }
    }
    return cur - format;
}

static void s21_write_widht(char *arg_widht , char **res, s21_size_t *size){ // тут надо доделать
    int width = atoi(arg_widht);
    if (width <= 0) return; 
    *size += width + 1;

    s21_safe_realloc(res, width + 1);
    if(!res) return;
    *res = memset(*res, ' ', width);
    (*res)[width] = '\0';
}

static int s21_make_res_resstr(FormatArg cur_arg, char *str){
    char *res = malloc(sizeof(char) * 2);
    *res = '\0';
    s21_size_t size = 0;
    if(s21_strlen(cur_arg.widht)) s21_write_widht(cur_arg.widht, &res, &size);
    else{
        size = s21_strlen(cur_arg.result);
        if(size){
            s21_safe_realloc(&res, size);
        }
    }
    if(s21_strlen(cur_arg.flags)){
        s21_size_t len_flags = s21_strlen(cur_arg.flags);
        for(char *pt = cur_arg.flags; pt - cur_arg.flags < len_flags; pt++){
            if(*pt == '+' && (cur_arg.specifier == 'd' || cur_arg.specifier == 'u' || cur_arg.specifier == 'f')){
                if(size == s21_strlen(cur_arg.result)){
                    size++;
                    s21_size_t size_arg = s21_strlen(cur_arg.result) + 1;
                    s21_safe_realloc(&res, size);
                }
                int index = 0;
                for(int i = 1; i < size && index < s21_strlen(cur_arg.result); i++){
                    if(index < s21_strlen(cur_arg.result))
                        res[i] = cur_arg.result[index++];
                }
                int digit = atoi(cur_arg.result);
                if(digit > 0) res[0] = '+';

                // s21_size_t size_arg = s21_strlen(cur_arg.result) + 2;
                // char *temp = malloc(sizeof(char) * size_arg);
                // temp[size_arg - 1] = '\0';
                // int index = 0;
                // for(int i = 1; i < size_arg-1 && index < s21_strlen(cur_arg.result); i++){
                //     if(index < s21_strlen(cur_arg.result)) temp[i] = cur_arg.result[index++];
                // }
                // 
                // temp[0] = (digit < 0) ? '-' : '+';
                // cur_arg.result = temp;
                // free(temp);
            }
            if(*pt == '-'){
                
            }
            // if(*pt == ' ' && !flg_positive){

            // }
        }
    }
    if(cur_arg.acuracy){

    }
    res[size - 1] = '\0';
    s21_str(str, res);
    // s21_str(str, cur_arg.result);
    free(res);
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
            *cur2 = *cur1;
            cur2++;
            continue;
        }
        cur2 += s21_make_res_resstr(cur_arg, cur2);
        s21_clearArg(&cur_arg);
        cur_arg = s21_initArg();

    }
    // если cur_arg не пустой нужно его обработать а потом уже освободить
    s21_clearArg(&cur_arg);
    va_end(argc);
    return s21_strlen(str);
}