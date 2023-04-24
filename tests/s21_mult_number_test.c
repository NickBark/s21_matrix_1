#include "unit.h"

START_TEST(mult_1) {
  matrix_t A = {0}, result;
  int rows = 5, columns = 5;
  double number = (double)(rand()) / RAND_MAX;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] * number, result.matrix[i][j],
                              1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_2) {
  matrix_t A = {0}, result;
  int rows = 5, columns = 5;
  double number = (double)(rand()) / RAND_MAX;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] * number, result.matrix[i][j],
                              1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_3) {
  matrix_t A = {0}, result = {0};
  int rows = 5, columns = 5;
  double number = (double)(rand()) / RAND_MAX;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] * number, result.matrix[i][j],
                              1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_4) {
  matrix_t A = {0}, result = {0};
  A.matrix = NULL;
  double number = (double)(rand()) / RAND_MAX;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 1);
}
END_TEST

START_TEST(mult_5) {
  matrix_t A = {0}, result = {0};
  int Arows = 0, Acolumns = 0;
  double number = (double)(rand()) / RAND_MAX;
  s21_create_matrix(Arows, Acolumns, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 1);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_mult_number(void) {
  Suite *s = suite_create("mult_number");
  TCase *tc_mult_number = tcase_create("mult_number");
  suite_add_tcase(s, tc_mult_number);

  tcase_add_test(tc_mult_number, mult_1);
  tcase_add_test(tc_mult_number, mult_2);
  tcase_add_test(tc_mult_number, mult_3);
  tcase_add_test(tc_mult_number, mult_4);
  tcase_add_test(tc_mult_number, mult_5);

  return s;
}