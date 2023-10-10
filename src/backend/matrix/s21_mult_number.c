#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int func_output = OK;
  if (A->matrix != NULL) {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else
      func_output = ERROR_UNCORRECT;
  } else
    func_output = ERROR_UNCORRECT;
  return func_output;
}