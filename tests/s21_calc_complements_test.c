#include "unit.h"

START_TEST(calc_complements_1) {
  matrix_t A, result;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j / 3.3;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A, result;
  int rows = 6, columns = 6;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j / 0.23456;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A, result;
  int rows = 10, columns = 7;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A, result;
  A.matrix = NULL;
  result.matrix = NULL;
  ck_assert_int_eq(s21_calc_complements(&A, &result), 1);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t A, result, result_true;
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &result_true);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  result_true.matrix[0][0] = 0;
  result_true.matrix[0][1] = 10;
  result_true.matrix[0][2] = -20;
  result_true.matrix[1][0] = 4;
  result_true.matrix[1][1] = -14;
  result_true.matrix[1][2] = 8;
  result_true.matrix[2][0] = -8;
  result_true.matrix[2][1] = -2;
  result_true.matrix[2][2] = 4;
  s21_calc_complements(&A, &result);
  // s21_output(result);
  // s21_output(result_true);
  ck_assert_int_eq(s21_eq_matrix(&result, &result_true), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_true);
  s21_remove_matrix(&result);
}
END_TEST

// START_TEST(calc_complements_5) {
//   matrix_t *A, result, result_true;
//   int rows = 3, columns = 3;
//   s21_create_matrix(rows, columns, A);
//   s21_create_matrix(rows, columns, result_true);
//   A->matrix = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
//   result_true0matrix = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
//   s21_calc_complements(A, result);
//   s21_output(*result);
//   s21_output(*result_true);
//   ck_assert_int_eq(s21_eq_matrix(result, result_true), 1);
//   s21_remove_matrix(A);
//   s21_remove_matrix(result_true);
//   s21_remove_matrix(result);
// }
// END_TEST

Suite *suite_s21_calc_complements(void) {
  Suite *s = suite_create("calc_complements");
  TCase *tc_calc_complements = tcase_create("calc_complements");
  suite_add_tcase(s, tc_calc_complements);

  tcase_add_test(tc_calc_complements, calc_complements_1);
  tcase_add_test(tc_calc_complements, calc_complements_2);
  tcase_add_test(tc_calc_complements, calc_complements_3);
  tcase_add_test(tc_calc_complements, calc_complements_4);
  tcase_add_test(tc_calc_complements, calc_complements_5);

  return s;
}