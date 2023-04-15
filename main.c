#include <stdio.h>

#include "s21_matrix.h"

int main() {
    matrix_t* matrix1 = malloc(sizeof(matrix_t));
    matrix_t* matrix2 = malloc(sizeof(matrix_t));
    matrix_t* result = malloc(sizeof(matrix_t));

    s21_create_matrix(2, 2, matrix1);
    s21_create_matrix(2, 3, matrix2);

    fill_matrix_interactive(matrix1);
    fill_matrix_interactive(matrix2);

    // fill_matrix(0.12345679, matrix1);
    // fill_matrix(0.12345679, matrix2);

    print_matrix(matrix1);
    print_matrix(matrix2);

    printf("mul: %d\n", s21_mult_matrix(matrix1, matrix2, result));

    print_matrix(result);

    s21_remove_matrix(matrix1);
    s21_remove_matrix(matrix2);

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}