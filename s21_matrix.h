#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define S21_EPS 1e-6

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t* result);
void s21_remove_matrix(matrix_t* A);
int s21_eq_matrix(matrix_t* A, matrix_t* B);
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_mult_number(matrix_t* A, double number, matrix_t* result);
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_transpose(matrix_t* A, matrix_t* result);
int s21_calc_complements(matrix_t* A, matrix_t* result);
int s21_inverse_matrix(matrix_t* A, matrix_t* result);

// support func
void print_matrix(matrix_t* matrix);
void fill_matrix(double val, matrix_t* matrix);
void fill_matrix_interactive(matrix_t* matrix);
double round_to_seven(double x);
void get_minor(matrix_t* A, matrix_t* result);  // вроде не нужна
void minor_matrix(matrix_t* source, matrix_t* minor, int im, int jm);

double recursion_determ(matrix_t* A);

double low_method(matrix_t* matrix);

#endif  // S21_MATRIX_H