#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int func_output = OK;
  if (A->columns == B->rows && A != NULL &&
      B != NULL) {  //  Произведение A * B определено если количество столбцов
                    //  матрицы A равно количеству строк матрицы B
    if (s21_create_matrix(A->rows, B->columns, result) ==
        OK) {  // Выделяем память под результат, количество строк новой матрицы
               // берем из матрицы A количество столбцов из матрицы B
      for (int i = 0; i < A->rows; i++) {       // проход v -A
        for (int j = 0; j < B->columns; j++) {  // проход > -B
          int temp = 0;
          for (int k = 0; k < B->rows; k++) {  // проход v -B > -A
            temp += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = temp;
        }
      }
    }
  } else
    func_output = ERROR_CALCULATION;

  return func_output;
}