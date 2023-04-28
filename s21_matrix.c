#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
    int ret = 0;
    if (rows < 1 || columns < 1 || !result) {
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
    if (!check_error(A)) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
    }
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
    int ret = -1;
    if (check_error(A) || check_error(B)) {
        ret = FAILURE;
    } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
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

    if (A == 0 || B == 0 || A->matrix == 0 || B->matrix == 0 ||
        A->columns == 0 || A->rows == 0 || B->columns == 0 || B->rows == 0) {
        ret = 1;
    } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
        // s21_remove_matrix(result);
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    } else {
        ret = 2;
    }

    return ret;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int ret = 0;

    if (check_error(A) || check_error(B)) {
        ret = 1;
    } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
        // s21_remove_matrix(result);
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    } else {
        ret = 2;
    }

    return ret;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
    int ret = 0;
    if (check_error(A)) {
        ret = 1;
    } else {
        // s21_remove_matrix(result);
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }

    return ret;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
    int ret = 0;

    if (check_error(A) || check_error(B)) {
        ret = 1;
    } else if (A->columns == B->rows) {
        // s21_remove_matrix(result);
        s21_create_matrix(A->rows, B->columns, result);

        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++)
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
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
        // s21_remove_matrix(result);
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }
    return ret;
}

int s21_calc_complements(matrix_t* A, matrix_t* result) {
    int ret = 0;

    if (check_error(A)) {
        ret = 1;
    } else if (A->rows != A->columns) {
        ret = 2;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        if (A->rows == 1) {
            result->matrix[0][0] = A->matrix[0][0];
        } else {
            matrix_t* minor = malloc(sizeof(matrix_t));
            s21_create_matrix(A->rows - 1, A->columns - 1, minor);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    minor_matrix(A, minor, i, j);
                    result->matrix[i][j] =
                        pow(-1, i + j) * recursion_determ(minor);
                }
            }
            s21_remove_matrix(minor);
            free(minor);
        }
    }

    return ret;
}

int s21_determinant(matrix_t* A, double* result) {
    int ret = 0;

    if (check_error(A)) {
        ret = 1;
    } else if (A->rows != A->columns) {
        ret = 2;
    } else {
        *result = recursion_determ(A);
    }

    return ret;
}

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
    int ret = 0;
    double det = 0;

    if (check_error(A)) {
        ret = 1;
    } else if (A->rows != A->columns) {
        ret = 2;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        if (A->rows == 1) {
            result->matrix[0][0] = 1.0 / A->matrix[0][0];
        } else {
            matrix_t* calc_comp = malloc(sizeof(matrix_t));
            matrix_t* tran = malloc(sizeof(matrix_t));
            s21_create_matrix(A->rows, A->columns, calc_comp);
            s21_create_matrix(A->rows, A->columns, tran);
            s21_calc_complements(A, calc_comp);
            det = recursion_determ(A);
            if (fabs(det) < S21_EPS) {
                ret = 2;
            } else {
                s21_transpose(calc_comp, tran);
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = tran->matrix[i][j] / det;
                    }
                }
            }
            s21_remove_matrix(calc_comp);
            free(calc_comp);
            s21_remove_matrix(tran);
            free(tran);
        }
    }

    return ret;
}

// ---------------- support func ---------------- //

int check_error(matrix_t* A) {
    int ret = 0;
    if (A == 0 || A->columns == 0 || A->rows == 0 || A->matrix == 0) {
        ret = 1;
    }
    return ret;
}

double recursion_determ(matrix_t* A) {
    double det = 0;

    if (A->rows == 1 && A->columns == 1) {
        det += A->matrix[0][0];
    } else {
        matrix_t* minor = malloc(sizeof(matrix_t));
        s21_create_matrix(A->rows - 1, A->columns - 1, minor);
        for (int j = 0; j < A->columns; j++) {
            minor_matrix(A, minor, 0, j);
            det +=
                A->matrix[0][j] * pow(-1, j) *
                (minor->rows > 3 ? recursion_determ(minor) : low_method(minor));
        }

        s21_remove_matrix(minor);
        free(minor);
    }
    return det;
}

double low_method(matrix_t* matrix) {
    double det = 0;
    if (matrix->columns == 3) {
        det =
            matrix->matrix[0][0] * matrix->matrix[1][1] * matrix->matrix[2][2] +
            matrix->matrix[1][0] * matrix->matrix[2][1] * matrix->matrix[0][2] +
            matrix->matrix[0][1] * matrix->matrix[1][2] * matrix->matrix[2][0] -
            matrix->matrix[0][2] * matrix->matrix[1][1] * matrix->matrix[2][0] -
            matrix->matrix[0][1] * matrix->matrix[1][0] * matrix->matrix[2][2] -
            matrix->matrix[0][0] * matrix->matrix[2][1] * matrix->matrix[1][2];
    } else if (matrix->columns == 2) {
        det = matrix->matrix[0][0] * matrix->matrix[1][1] -
              matrix->matrix[0][1] * matrix->matrix[1][0];
    } else if (matrix->columns == 1) {
        det = matrix->matrix[0][0];
    }

    return det;
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
    if (matrix->rows) {
        for (int i = 0; i < matrix->rows; i++) {
            for (int j = 0; j < matrix->columns; j++) {
                printf("%.8lf ", matrix->matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void fill_matrix_auto(double val, matrix_t* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->matrix[i][j] = val;
        }
    }
}

void fill_matrix(matrix_t* A, double start, double step) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            A->matrix[i][j] = start;
            start += step;
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

// void get_minor(matrix_t* A, matrix_t* result) {
//     s21_remove_matrix(result);
//     s21_create_matrix(A->rows, A->columns, result);
//     matrix_t* minor = malloc(sizeof(matrix_t));
//     s21_create_matrix(A->rows - 1, A->columns - 1, minor);
//     fill_matrix(0, minor);
//     minor->rows = A->rows - 1;
//     minor->columns = A->columns - 1;

//     for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//             minor_matrix(A, minor, i, j);
//             print_matrix(minor);
//             if (minor->rows == 3) {
//                 result->matrix[i][j] = low_method(minor);
//             } else if (minor->rows == 2) {
//                 result->matrix[i][j] =
//                     minor->matrix[0][0] * minor->matrix[1][1] -
//                     minor->matrix[0][1] * minor->matrix[1][0];
//             } else if (minor->rows == 1) {
//                 result->matrix[i][j] = minor->matrix[0][0];
//             } else if (minor->rows > 3) {
//                 get_minor(minor, minor);
//             }
//         }
//     }

//     s21_remove_matrix(minor);
//     free(minor);
// }