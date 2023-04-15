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

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int ret = 0;

    if (A == 0 || B == 0) {
        ret = 1;
    } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        result->rows = A->rows;
        result->columns = A->columns;
    } else {
        ret = 2;
    }

    return ret;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int ret = 0;

    if (A == 0 || B == 0) {
        ret = 1;
    } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        result->rows = A->rows;
        result->columns = A->columns;
    } else {
        ret = 2;
    }

    return ret;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
    int ret = 0;
    if (A == 0) {
        ret = 1;
    } else {
        s21_remove_matrix(result);
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        result->rows = A->rows;
        result->columns = A->columns;
    }

    return ret;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int ret = 0;

    if (A == 0 || B == 0) {
        ret = 1;
    } else if (A->columns == B->rows) {
        s21_remove_matrix(result);
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++)
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
        result->rows = A->rows;
        result->columns = B->columns;
    } else {
        ret = 2;
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

void fill_matrix_interactive(matrix_t* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            scanf("%lf", &(matrix->matrix[i][j]));
        }
    }
}

double round_to_seven(double x) {
    double scale = pow(10, 7);
    return round(x * scale) / scale;
}
