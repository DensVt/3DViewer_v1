#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int func_output = OK;
  if (A->matrix != NULL) {
    if (A->columns == A->rows) {
      if (s21_create_matrix(A->rows, A->columns, result) == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = minor_element(*A, i, j) * pow(-1, (i + j));
          }
        }
      } else
        func_output = ERROR_UNCORRECT;
    } else
      func_output = ERROR_CALCULATION;
  } else
    func_output = ERROR_UNCORRECT;
  return func_output;
}