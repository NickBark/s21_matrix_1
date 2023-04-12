#include <stdio.h>

#include "s21_matrix.h"

int main() {
    matrix_t* matrix1 = malloc(sizeof(matrix_t));
    matrix_t* matrix2 = malloc(sizeof(matrix_t));

    s21_create_matrix(10, 10, matrix1);
    s21_create_matrix(10, 10, matrix2);

    fill_matrix(0.12345679, matrix1);
    fill_matrix(0.12345679, matrix2);

    print_matrix(matrix1);
    print_matrix(matrix2);

    printf("eq: %d\n", s21_eq_matrix(matrix1, matrix2));

    s21_remove_matrix(matrix1);
    s21_remove_matrix(matrix2);

    free(matrix1);
    free(matrix2);

    return 0;
}