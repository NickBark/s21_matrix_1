#include "unit.h"

START_TEST(create_matrix_1) {
  matrix_t result;
  int rows = 2, columns = 10;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(0, exit_code);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t result;
  int rows = 2, columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(0, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t result = {0};
  int rows = 0;
  int columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(1, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_matrix_4) {
  matrix_t result = {0};
  int rows = 0, columns = 0;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(create_matrix_5) {
  matrix_t result = {0};
  int rows = 4, columns = -7;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(create_matrix_6) {
  ck_assert_int_eq(1, s21_create_matrix(0, 0, NULL));
}
END_TEST

Suite *suite_s21_create_matrix(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc_create_matrix = tcase_create("s21_create_matrix");
  suite_add_tcase(s, tc_create_matrix);

  tcase_add_test(tc_create_matrix, create_matrix_1);
  tcase_add_test(tc_create_matrix, create_matrix_2);
  tcase_add_test(tc_create_matrix, create_matrix_3);
  tcase_add_test(tc_create_matrix, create_matrix_4);
  tcase_add_test(tc_create_matrix, create_matrix_5);
  tcase_add_test(tc_create_matrix, create_matrix_6);

  return s;
}
