#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int func_output = OK;
  if (A->rows != B->rows ||
      A->columns !=
          B->columns) { /* Проверяем одинаковая ли размерность матриц. Вычитать
                           допускается матрицы одинаковой размерности*/
    func_output = ERROR_CALCULATION;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) ==
        OK) { /* Выделяем память под результирующую матрицу */
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else
      func_output = ERROR_UNCORRECT;
  }
  return func_output;
}