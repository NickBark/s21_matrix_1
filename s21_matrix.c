#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
    int ret = 0;
    if (!rows || !columns) {
        ret = 1;
    } else {
        result->matrix = (double**)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double*)calloc(columns, sizeof(double));
        }
        result->rows = rows;
        result->columns = columns;
    }
    return ret;
}

void s21_remove_matrix(matrix_t* A) {
    for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
    }
    free(A->matrix);
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
    int ret = -1;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (round_to_seven(A->matrix[i][j]) !=
                    round_to_seven(B->matrix[i][j]))
                    ret = FAILURE;
            }
        }
        if (ret) ret = SUCCESS;
    } else {
        ret = FAILURE;
    }
    return ret;
}

// ---------------- support func ---------------- //
void print_matrix(matrix_t* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%.8lf ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void fill_matrix(double val, matrix_t* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->matrix[i][j] = val;
        }
    }
}

double round_to_seven(double x) {
    double scale = pow(10, 7);
    return round(x * scale) / scale;
}
