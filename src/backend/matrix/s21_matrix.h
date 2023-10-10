#ifndef S21_MATRIX_H
#define S21_MATRIX_H

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "add_func.h"

#define OK 0
#define ERROR_UNCORRECT 1 /* - Ошибка, некорректная матрица */
#define ERROR_CALCULATION                                                                                                                 \
  2 /* - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой \
       нельзя провести вычисления и т.д.)*/
#define SUCCESS 1 /* Результат функции сравнения */
#define FAILURE 0 /* Результат функции сравнения */
#define EXP 1e-6

int s21_create_matrix(int rows, int columns,
                      matrix_t *result); /* Функция создания матрицы */
void s21_remove_matrix(matrix_t *A); /* Функция очистки матрицы */
int s21_eq_matrix(matrix_t *A, matrix_t *B); /* Функция сравнения */
int s21_sum_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result); /* Функция сложения матриц */
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result); /* Функция вычитания матриц */
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result); /* Функция умножения матрицы на число */
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result); /* Функция умножения матриц */
int s21_transpose(matrix_t *A,
                  matrix_t *result); /* Функция транспонирования матрицы (меняем
                                        местами row/col) */
int s21_calc_complements(matrix_t *A,
                         matrix_t *result); /* Функция вычисления матрицы
                                               алгебраических дополнений */
int s21_determinant(
    matrix_t *A, double *result); /* Функция вычисления определителя матрицы */
int s21_inverse_matrix(matrix_t *A,
                       matrix_t *result); /* Функция поиска обратной матрицы */

void output(matrix_t matrix);

#endif