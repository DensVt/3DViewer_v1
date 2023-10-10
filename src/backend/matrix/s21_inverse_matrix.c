#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  matrix_t new_A;
  int func_output = OK, col = A->columns * 2;
  double det = 0;
  if ((func_output = s21_determinant(A, &det)) == OK) {
    if (det == 0)
      func_output = ERROR_CALCULATION;
    else {
      if (A && s21_create_matrix(A->rows, col, &new_A) == 0 &&
          A->rows == A->columns) {
        add_one_matrix(A->matrix, A->rows, new_A.matrix);
        for (int k = 0; k < A->rows; k++) {
          if (new_A.matrix[k][k] != 1) {
            double temp = new_A.matrix[k][k];
            for (int j = 0; j < col; j++) {
              new_A.matrix[k][j] = new_A.matrix[k][j] / temp;
            }
          }
          int p = k + 1;
          if (p < A->rows) {
            for (int i = p; i < A->rows; i++) {
              double temp2 = new_A.matrix[i][k];
              for (int j = 0; j < col; j++) {
                new_A.matrix[i][j] -= new_A.matrix[k][j] * temp2;
              }
              p++;
            }
          }
        }
        for (int k = 1; k < A->rows; k++) {
          for (int i = 0; i < k; i++) {
            double temp3 = new_A.matrix[i][k];
            for (int j = 0; j < col; j++) {
              new_A.matrix[i][j] -= new_A.matrix[k][j] * temp3;
            }
          }
        }
        if (s21_create_matrix(A->rows, A->rows, result) == 0) {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->rows; j++) {
              result->matrix[i][j] = new_A.matrix[i][j + A->rows];
            }
          }
        } else
          func_output = ERROR_UNCORRECT;
        s21_remove_matrix(&new_A);
      } else
        func_output = ERROR_UNCORRECT;
    }
  }
  return func_output;
}