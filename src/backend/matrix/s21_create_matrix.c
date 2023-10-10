#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int func_output;
  if (rows > 0 && columns > 0) {
    func_output = OK;
    result->matrix =
        malloc(rows * columns * sizeof(double) + rows * sizeof(double *));
    if (result->matrix) {
      double *pointer = (double *)(result->matrix + rows);
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = pointer + columns * i;
      }
      result->columns = columns;
      result->rows = rows;
    }
  } else {
    func_output = 1;
  }
  return func_output;
}