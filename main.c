// #include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"
#define NN 6

// void foo() {
//     float a[NN][NN], kst;
//     int i, j, n, im, jm, p, k = 0, t;
//     char yn;

//     // <----Ввод размера квадратной матрицы---->

//     while (k == 0) {
//         printf("\nВведите размер матрицы (от 2 до %d): N=", NN);
//         // n = getche() - 48;
//         if ((n < 2) || (n > NN))
//             k = 0;
//         else
//             k = 1;
//     }

//     // <----Ввод матрицы a[NN][NN]---->

//     k = 0;
//     while (k == 0) {
//         printf("\n\nЗадать матрицу случайно? y/n: ");
//         // yn = getche();
//         if ((yn == 'y') || (yn == 'n'))
//             k = 1;
//         else
//             k = 0;
//     }
//     switch (yn) {
//         case 'y':
//             for (i = 0; i < n; i++)
//                 for (j = 0; j < n; j++) a[i][j] = rand() % 100;
//             break;
//         default: {
//             printf("\nВведите матрицу %dx%d\n", n, n);
//             for (i = 0; i < n; i++)
//                 for (j = 0; j < n; j++) scanf("%f", &a[i][j]);
//         } break;
//     }

//     // <----Выводим введенную матрицу---->
//     printf("\n");
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < n; j++) printf("%6.2f\t", a[i][j]);
//         printf("\n\n");
//     }

//     // <----Вводим минор---->
//     printf("По какому элементу искать минор? i=");
//     // im = getche() - 49;
//     printf(" j=");
//     // jm = getche() - 49;

//     // <----Считаем матрицу минора---->

//     for (i = 0; i < n; i++)
//         if (i == im)
//             for (p = i; p < n; p++)
//                 for (j = 0; j < n; j++) a[p][j] = a[p + 1][j];
//     for (j = 0; j < n; j++)
//         if (j == jm)
//             for (p = j; p < n; p++)
//                 for (i = 0; i < n; i++) a[i][p] = a[i][p + 1];
//     n -= 1;

//     // <----Выводим матрицу минора---->
//     printf("\n");
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < n; j++) printf("%6.2f\t", a[i][j]);
//         printf("\n\n");
//     }

//     // <----Считаем минор---->

//     p = 0;
//     for (i = 0; i < n - 1; i++) {
//         t = 1;
//         while (a[i][i] == 0) {
//             for (j = 0; j < n; j++) {
//                 a[i][j] = kst;
//                 a[i][j] = a[i + t][j];
//                 a[i + t][j] = kst;
//             }
//             p++;
//             t++;
//         }

//         for (k = i + 1; k < n; k++) {
//             kst = a[k][i] / a[i][i];
//             for (j = 0; j < n; j++) a[k][j] -= a[i][j] * kst;
//         }
//     }

//     kst = pow(-1, p);
//     for (i = 0; i < n; i++) kst *= a[i][i];

//     printf("Минор по А[%d][%d] равен: %14.3f", im + 1, jm + 1, kst);
//     getch();
// }

int main() {
    matrix_t* matrix1 = malloc(sizeof(matrix_t));
    matrix_t* matrix2 = malloc(sizeof(matrix_t));
    matrix_t* result = malloc(sizeof(matrix_t));

    s21_create_matrix(3, 3, matrix1);

    // s21_create_matrix(2, 3, matrix2);

    fill_matrix_interactive(matrix1);
    // fill_matrix_interactive(matrix2);

    // fill_matrix(0.12345679, matrix1);
    // fill_matrix(0.12345679, matrix2);

    print_matrix(matrix1);
    // print_matrix(matrix2);
    // printf("det %lf\n", recursion_determ(matrix1));
    // s21_calc_complements(matrix1, result);
    s21_inverse_matrix(matrix1, result);
    // get_minor(matrix1, result);
    // printf("tr: %d\n", s21_transpose(matrix1, result));

    // printf("mul: %d\n", s21_mult_number(matrix1, NAN, result));

    // printf("mul: %d\n", s21_mult_matrix(matrix1, matrix2, result));

    print_matrix(result);

    s21_remove_matrix(matrix1);
    // s21_remove_matrix(matrix2);

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
