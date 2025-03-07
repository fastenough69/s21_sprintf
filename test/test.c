#include "test.h"

START_TEST(test_sprintf_c_1) {
    char str1[100] = {0};
    char str2[100] = {0};
    int a = 78;
    ck_assert_int_eq(sprintf(str1, "%-4c", a), s21_sprintf(str2, "%-4c", a));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_c_3) {
    char str1[100] = {0};
    char str2[100] = {0};
    int b = 66;
    ck_assert_int_eq(sprintf(str1, "%5c", b), s21_sprintf(str2, "%5c", b));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_c_4) {
    char str1[100] = {0};
    char str2[100] = {0};
    int c = '\0';
    sprintf(str1, "%c", c);
    s21_sprintf(str2, "%c", c);
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_c_5) {
    char str1[100] = {0};
    char str2[100] = {0};
    int e = -123;
    ck_assert_int_eq(sprintf(str1, "%c", e), s21_sprintf(str2, "%c", e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_c_6) {
    char str1[100] = {0};
    char str2[100] = {0};
    int e = 123;
    ck_assert_int_eq(sprintf(str1, "%c", e), s21_sprintf(str2, "%c", e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  Suite *sprintf_c_suite(void) {
    Suite *s;
    TCase *tc_core;
  
    s = suite_create("-=S21_SPRINTF_C=-");
    tc_core = tcase_create("SprintfcCore");
  
    tcase_add_test(tc_core, test_sprintf_c_1);
    tcase_add_test(tc_core, test_sprintf_c_3);
    tcase_add_test(tc_core, test_sprintf_c_4);
    tcase_add_test(tc_core, test_sprintf_c_5);
    tcase_add_test(tc_core, test_sprintf_c_6);
    suite_add_tcase(s, tc_core);
  
    return s;
  }
  
  START_TEST(test_sprintf_d_1) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "% d";
    int val = 0;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_2) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%-4d";
    int a = 78;
    ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_3) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%4d";
    int e = 123;
    ck_assert_int_eq(sprintf(str1, str3, e), s21_sprintf(str2, str3, e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_4) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%hd";
    int b = -66;
    ck_assert_int_eq(sprintf(str1, str3, b), s21_sprintf(str2, str3, b));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_5) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%ld";
    int c = 35;
    ck_assert_int_eq(sprintf(str1, str3, c), s21_sprintf(str2, str3, c));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_6) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%.5d";
    int d = 124;
    ck_assert_int_eq(sprintf(str1, str3, d), s21_sprintf(str2, str3, d));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_7) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%+d";
    int e = 123;
    ck_assert_int_eq(sprintf(str1, str3, e), s21_sprintf(str2, str3, e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_8) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%-+ 5.5hd";
    int e = 12368598;
    ck_assert_int_eq(sprintf(str1, str3, e), s21_sprintf(str2, str3, e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_9) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%-+ 5.5ld";
    int e = 12368598;
    ck_assert_int_eq(sprintf(str1, str3, e), s21_sprintf(str2, str3, e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_d_10) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%15ld";
    int e = 12368598;
    ck_assert_int_eq(sprintf(str1, str3, e), s21_sprintf(str2, str3, e));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  Suite *sprintf_d_suite(void) {
    Suite *s;
    TCase *tc_core;
  
    s = suite_create("-=S21_SPRINTF_D=-");
    tc_core = tcase_create("SprintfdCore");
  
    tcase_add_test(tc_core, test_sprintf_d_1);
    tcase_add_test(tc_core, test_sprintf_d_2);
    tcase_add_test(tc_core, test_sprintf_d_3);
    tcase_add_test(tc_core, test_sprintf_d_4);
    tcase_add_test(tc_core, test_sprintf_d_5);
    tcase_add_test(tc_core, test_sprintf_d_6);
    tcase_add_test(tc_core, test_sprintf_d_7);
    tcase_add_test(tc_core, test_sprintf_d_8);
    tcase_add_test(tc_core, test_sprintf_d_9);
    tcase_add_test(tc_core, test_sprintf_d_10);
    suite_add_tcase(s, tc_core);
  
    return s;
  }
  
  START_TEST(test_sprintf_s_1) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "(%   s%-20s%20s| ";
    char *val = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, val, val, val),
                     s21_sprintf(str2, str3, val, val, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_s_2) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "(%-20s| ";
    char *val = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_s_3) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "(%s| ";
    char *val = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, val),
                     s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_s_4) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "(%+-  50s)";
    char *val = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_s_5) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "(%.5s)";
    char *val = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  Suite *sprintf_s_suite(void) {
    Suite *s;
    TCase *tc_core;
  
    s = suite_create("=S21_SPRINTF_S=-");
    tc_core = tcase_create("SprintfsCore");
  
    tcase_add_test(tc_core, test_sprintf_s_1);
    tcase_add_test(tc_core, test_sprintf_s_2);
    tcase_add_test(tc_core, test_sprintf_s_3);
    tcase_add_test(tc_core, test_sprintf_s_4);
    tcase_add_test(tc_core, test_sprintf_s_5);
    suite_add_tcase(s, tc_core);
  
    return s;
  }

//   START_TEST(test_sprintf_f_1) {
//     char str1[STR_LEN] = {'\0'};
//     char str2[STR_LEN] = {'\0'};
//     char *format = "%Lf";
//     long double val = 513515.131513515151351;
//     ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
//     ck_assert_str_eq(str1, str2);
//   }
//   END_TEST
  
//   START_TEST(test_sprintf_f_2) {
//     char str1[STR_LEN] = {'\0'};
//     char str2[STR_LEN] = {'\0'};
//     char *format = "%10Lf";
//     long double val = 15.35;
//     ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
//     ck_assert_str_eq(str1, str2);
//   }
//   END_TEST
  
  START_TEST(test_sprintf_f_3) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%.0f";
    double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_f_4) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%.f";
    double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
//   START_TEST(test_sprintf_f_5) {
//     char str1[STR_LEN] = {'\0'};
//     char str2[STR_LEN] = {'\0'};
//     char *format = "%.15Lf";
//     long double val = 15.35;
//     ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
//     ck_assert_str_eq(str1, str2);
//   }
//   END_TEST
  
  START_TEST(test_sprintf_f_6) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%.9f";
    double val = -15.3558;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_f_7) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%f";
    long double val = 72537572375.1431341;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_f_8) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "% f";
    float val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
//   START_TEST(test_sprintf_f_9) {
//     char str1[STR_LEN] = {'\0'};
//     char str2[STR_LEN] = {'\0'};
//     char *format = "% .0f %.lf %Lf %f %lf %Lf";
//     float val = 0;
//     double val1 = 0;
//     long double val2 = 3515315.153151;
//     float val3 = 5.5;
//     double val4 = 9851.51351;
//     long double val5 = 95919539159.53151351131;
//     ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
//                      sprintf(str2, format, val, val1, val2, val3, val4, val5));
  
//     ck_assert_str_eq(str1, str2);
//   }
//   END_TEST
  
  START_TEST(test_sprintf_f_10) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%10f";
    double val = 15;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_f_11) {
    char str1[STR_LEN] = {'\0'};
    char str2[STR_LEN] = {'\0'};
    char *format = "%+f";
    double val = 15.1;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  
    ck_assert_str_eq(str1, str2);
  }
  END_TEST
  
  Suite *sprintf_f_suite(void) {
    Suite *s;
    TCase *tc_core;
  
    s = suite_create("-=S21_SPRINTF_F=-");
    tc_core = tcase_create("SprintfuCore");
  
    
    tcase_add_test(tc_core, test_sprintf_f_8);
    tcase_add_test(tc_core, test_sprintf_f_10);
    tcase_add_test(tc_core, test_sprintf_f_11);
    tcase_add_test(tc_core, test_sprintf_f_7);
    tcase_add_test(tc_core, test_sprintf_f_6);
    tcase_add_test(tc_core, test_sprintf_f_4);
    tcase_add_test(tc_core, test_sprintf_f_3);
  
    suite_add_tcase(s, tc_core);
  
    return s;
  }

  START_TEST(test_sprintf_u_1) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%u";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_2) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%4u";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_3) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%-4u";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_4) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%.4u";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_5) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%hu";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_6) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%lu";
    unsigned int val = 012;
    ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_7) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%u";
    unsigned int val1 = 0;
    ck_assert_int_eq(sprintf(str1, str3, val1), s21_sprintf(str2, str3, val1));
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  START_TEST(test_sprintf_u_8) {
    char str1[100] = "";
    char str2[100] = "";
    char *str3 = "%+- 20.20lu";
    unsigned int val1 = 0123;
    ck_assert_int_eq(sprintf(str1, str3, val1), s21_sprintf(str2, str3, val1));
    ck_assert_str_eq(str1, str2);
    ck_assert_pstr_eq(str1, str2);
  }
  END_TEST
  
  Suite *sprintf_u_suite(void) {
    Suite *s;
    TCase *tc_core;
  
    s = suite_create("42m-=S21_SPRINTF_U=-");
    tc_core = tcase_create("SprintfuCore");
  
    tcase_add_test(tc_core, test_sprintf_u_1);
    tcase_add_test(tc_core, test_sprintf_u_2);
    tcase_add_test(tc_core, test_sprintf_u_3);
    tcase_add_test(tc_core, test_sprintf_u_4);
    tcase_add_test(tc_core, test_sprintf_u_5);
    tcase_add_test(tc_core, test_sprintf_u_6);
    tcase_add_test(tc_core, test_sprintf_u_7);
    tcase_add_test(tc_core, test_sprintf_u_8);
    suite_add_tcase(s, tc_core);
  
    return s;
  }
  

int main(void){
    int number_failed = 0;
    Suite *string_tests[] = {
        sprintf_c_suite(), sprintf_d_suite(), sprintf_s_suite(),
        sprintf_u_suite(), sprintf_f_suite(), s21_NULL};
    for (int i = 0; string_tests[i] != s21_NULL; i++) {
        SRunner *runner;
        runner = srunner_create(string_tests[i]);
        srunner_set_fork_status(runner, CK_NOFORK);
        srunner_run_all(runner, CK_NORMAL);
        number_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }
    return (number_failed == 0) ? 0: 1;
}