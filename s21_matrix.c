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

int s21_transpose(matrix_t* A, matrix_t* result) {
    int ret = 0;
    if (A == 0 || A->columns == 0 || A->rows == 0) {
        ret = 1;
    } else {
        s21_remove_matrix(result);
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
            result->rows = A->columns;
            result->columns = A->rows;
        }
    }
    return ret;
}

int s21_calc_complements(matrix_t* A, matrix_t* result) {}

// ---------------- support func ---------------- //
void get_minor(matrix_t* A, matrix_t* result) {
    s21_remove_matrix(result);
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t* minor = malloc(sizeof(matrix_t));
    s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    fill_matrix(0, minor);
    minor->rows = A->rows - 1;
    minor->columns = A->columns - 1;

    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
            minor_matrix(A, minor, i, j);
            print_matrix(minor);
            if (minor->rows == 3) {
                result->matrix[i][j] = triangle_rule(minor);
            } else if (minor->rows == 2) {
                result->matrix[i][j] =
                    minor->matrix[0][0] * minor->matrix[1][1] -
                    minor->matrix[0][1] * minor->matrix[1][0];
            } else if (minor->rows == 1) {
                result->matrix[i][j] = minor->matrix[0][0];
            } else if (minor->rows > 3) {
                get_minor(minor, minor);
            }
        }
    }

    s21_remove_matrix(minor);
    free(minor);
}

double triangle_rule(matrix_t* matrix) {
    return matrix->matrix[0][0] * matrix->matrix[1][1] * matrix->matrix[2][2] +
           matrix->matrix[1][0] * matrix->matrix[2][1] * matrix->matrix[0][2] +
           matrix->matrix[0][1] * matrix->matrix[1][2] * matrix->matrix[2][0] -
           matrix->matrix[0][2] * matrix->matrix[1][1] * matrix->matrix[2][0] -
           matrix->matrix[0][1] * matrix->matrix[1][0] * matrix->matrix[2][2] -
           matrix->matrix[0][0] * matrix->matrix[2][1] * matrix->matrix[1][2];
}

void minor_matrix(matrix_t* source, matrix_t* minor, int im, int jm) {
    int n = source->rows;
    int k = 0;
    int l = 0;

    for (int i = 0; i < n; i++) {
        if (i == im) continue;
        l = 0;
        for (int j = 0; j < n; j++) {
            if (j == jm) continue;
            minor->matrix[k][l] = source->matrix[i][j];
            l++;
        }
        k++;
    }
}

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
