#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int func_output = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) {
    func_output = SUCCESS;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((A->matrix[i][j] - B->matrix[i][j]) > EXP) {
          func_output = FAILURE;
          break;
        }
      }
    }
  }
  return func_output;
}