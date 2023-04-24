#include "unit.h"

START_TEST(sub_1) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  // s21_create_matrix(rows, columns, &result);
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_2) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  int Arows = 5, Acolumns = 5;
  int Brows = 4, Bcolumns = 5;
  s21_create_matrix(Arows, Acolumns, &A);
  s21_create_matrix(Brows, Bcolumns, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  A.matrix = NULL, B.matrix = NULL;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 1);
}
END_TEST

Suite *suite_s21_sub_matrix(void) {
  Suite *s = suite_create("sub_matrix");
  TCase *tc_sub_matrix = tcase_create("sub_matrix");
  suite_add_tcase(s, tc_sub_matrix);

  tcase_add_test(tc_sub_matrix, sub_1);
  tcase_add_test(tc_sub_matrix, sub_2);
  tcase_add_test(tc_sub_matrix, sub_3);
  tcase_add_test(tc_sub_matrix, sub_4);
  tcase_add_test(tc_sub_matrix, sub_5);

  return s;
}
