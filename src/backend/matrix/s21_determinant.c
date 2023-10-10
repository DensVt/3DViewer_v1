#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int func_output = OK;
  if (A->matrix != NULL) {
    if (A->rows == A->columns) {  // Определитель существует только для
                                  // квадратных матриц. Проверяем условие
      if (A->rows == 1)
        *result = A->matrix[0][0];  //  Определитель матрицы первого порядка
      else if (A->rows == 2)
        *result = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[0][1] *
                   A->matrix[1][0]);  // Определитель матрицы второго порядка
      else {
        matrix_t temp;
        if (s21_create_matrix(A->rows, A->columns, &temp) == OK) {
          copy_matrix(A->matrix, A->rows, temp.matrix);
          *result = gaus_det(temp.matrix, A->rows);  // Прочие матрицы
          s21_remove_matrix(&temp);
        } else
          func_output = ERROR_UNCORRECT;
      }
    } else
      func_output = ERROR_CALCULATION;
  } else
    func_output = ERROR_UNCORRECT;
  return func_output;
}
