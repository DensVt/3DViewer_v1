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

#endif