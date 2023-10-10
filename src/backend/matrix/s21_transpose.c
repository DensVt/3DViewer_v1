#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int func_output = OK;
  if (A != NULL) {
    int rows = A->columns;
    int columns = A->rows;
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else
      func_output = ERROR_UNCORRECT;
  } else
    func_output = ERROR_UNCORRECT;
  return func_output;
}