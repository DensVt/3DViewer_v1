#include "add_func.h"

// void output_matrix(matrix_t matrix) {
//   int row = matrix.rows;
//   int col = matrix.columns;
//   for (int i = 0; i < row; i++) {
//     for (int j = 0; j < col - 1; j++) {
//       printf("%lf ", matrix.matrix[i][j]);
//     }
//     printf("%lf\n", matrix.matrix[i][col - 1]);
//   }
// }

// Метод Гаусса расчет определителя квадратной матрицы
double gaus_det(double **matrix, int n) {  // n - размер матрицы
  int p = 1;
  double x;
  int zero = 1;
  // приведение матрицы к треугольному виду (нули ниже главной диагонали)
  for (int k = 0; k < n; k++) {
    // проход по колонкам 'k'
    // если эл-т гл диагонали к-го столбца == 0 меняем столбцы местами
    if (matrix[k][k] == 0) {
      for (int i = k; i < n; i++) {
        double temp = matrix[k][i];
        matrix[k][i] = matrix[n - 1][i];
        matrix[n - 1][i] = temp;
      }
      zero = -1;
    } else
      zero = 1;
    for (int i = p; i < n; i++) {  // перебор колонки  'i'
      x = -(matrix[i][k]) / matrix[k][k];
      if (matrix[i][k] != 0) {
        for (int j = k; j < n; j++) {  // перебор элементов  i-й строки 'j'
          matrix[i][j] += (matrix[k][j] * x);
        }
      }
    }
    p++;
  }
  //  умножение элементов главной диагонали
  double result = 1;
  for (int i = 0; i < n; i++) {
    result *= matrix[i][i];
  }
  return zero * result;
}

// Добавляем к матрице единичную спарва
void add_one_matrix(double **matrix, int n, double **new_matrix) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      new_matrix[i][j] = matrix[i][j];
    }
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = n; j < (2 * n); j++) {
      if (j == n + k)
        new_matrix[i][j] = 1;
      else
        new_matrix[i][j] = 0;
    }
    k++;
  }
}

// Копирование квадратной матрицы
void copy_matrix(double **matrix, int n, double **new_matrix) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      new_matrix[i][j] = matrix[i][j];
    }
  }
}

// Поиск минора элемента i j
//(перебираем матрицу и все значения кроме тех что находятся в ряду row и
// колонке colomns)
double minor_element(matrix_t matrix, int rows, int columns) {
  double result = 0;
  matrix_t temp;
  int k = 0, n = 0;
  s21_create_matrix(matrix.rows - 1, matrix.columns - 1, &temp);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      if (i != rows && j != columns) {
        temp.matrix[k][n] = matrix.matrix[i][j];
        n++;
      }
      if (n == matrix.columns - 1) {
        k++;
        n = 0;
      }
    }
  }
  s21_determinant(&temp, &result);
  s21_remove_matrix(&temp);
  return result;
}
