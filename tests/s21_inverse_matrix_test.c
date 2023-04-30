#include "unit.h"

START_TEST(inverse_matrix_1) {
    matrix_t A, result;
    int rows = 5, columns = 5;
    s21_create_matrix(rows, columns, &A);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            A.matrix[i][j] = pow((i + j / 4.5), i + j);
        }
    }
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_2) {
    matrix_t A = {0}, result;
    int rows = 6, columns = 6;
    s21_create_matrix(rows, columns, &A);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            A.matrix[i][j] = (i + j);
        }
    }
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_3) {
    matrix_t A, result;
    int rows = 10, columns = 7;
    s21_create_matrix(rows, columns, &A);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            A.matrix[i][j] = (double)(rand()) / RAND_MAX;
        }
    }
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_4) {
    matrix_t A, result;
    A.matrix = NULL;
    result.matrix = NULL;
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 1);
}
END_TEST

START_TEST(inverse_matrix_5) {
    matrix_t A, result, result_true;
    int rows = 3, columns = 3;
    s21_create_matrix(rows, columns, &A);
    s21_create_matrix(rows, columns, &result_true);
    A.matrix[0][0] = 2;
    A.matrix[0][1] = 5;
    A.matrix[0][2] = 7;
    A.matrix[1][0] = 6;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = -3;
    result_true.matrix[0][0] = 1;
    result_true.matrix[0][1] = -1;
    result_true.matrix[0][2] = 1;
    result_true.matrix[1][0] = -38;
    result_true.matrix[1][1] = 41;
    result_true.matrix[1][2] = -34;
    result_true.matrix[2][0] = 27;
    result_true.matrix[2][1] = -29;
    result_true.matrix[2][2] = 24;
    s21_inverse_matrix(&A, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &result_true), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result_true);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_6) {
    matrix_t A, result;
    s21_create_matrix(1, 1, &A);
    A.matrix[0][0] = 1.0;
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 0);
    ck_assert_int_eq(result.matrix[0][0], 1.0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_7) {
    matrix_t A;
    matrix_t B;
    // double result = 0;
    int rows = 1, columns = 1;
    s21_create_matrix(rows, columns, &A);
    double vars[1] = {7};
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            A.matrix[i][j] = vars[k++];
        }
    }
    ck_assert_int_eq(s21_inverse_matrix(&A, &B), 0);
    ck_assert_double_eq(B.matrix[0][0], 1.0 / 7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(inverse_matrix_14) {
    matrix_t A;
    matrix_t B;
    // double result = 0;
    int rows = 1, columns = 1;
    s21_create_matrix(rows, columns, &A);
    double vars[1] = {-7};
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            A.matrix[i][j] = vars[k++];
        }
    }
    ck_assert_int_eq(s21_inverse_matrix(&A, &B), 0);
    ck_assert_double_eq(B.matrix[0][0], -1.0 / 7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(inverse_matrix_10) {
    matrix_t A;
    matrix_t expected;
    matrix_t result;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &expected);
    A.matrix[0][0] = 5;
    expected.matrix[0][0] = 0.2;
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 0);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&expected);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_11) {
    matrix_t A;
    matrix_t result;
    s21_create_matrix(4, 5, &A);
    ck_assert_int_eq(s21_inverse_matrix(&A, &result), 2);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_13) {
    matrix_t result;
    ck_assert_int_eq(s21_inverse_matrix(NULL, &result), 1);
}
END_TEST

Suite *suite_s21_inverse_matrix(void) {
    Suite *s = suite_create("inverse_matrix");
    TCase *tc_inverse_matrix = tcase_create("inverse_matrix");
    suite_add_tcase(s, tc_inverse_matrix);

    tcase_add_test(tc_inverse_matrix, inverse_matrix_1);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_2);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_3);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_4);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_5);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_6);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_7);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_10);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_11);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_13);
    tcase_add_test(tc_inverse_matrix, inverse_matrix_14);
    return s;
}
