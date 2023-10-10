#include "s21_matrix.h"

void output(matrix_t matrix){
    for (int i = 0; i < matrix.rows; i++){
        for (int j = 0; j < matrix.columns-1; j++){
            printf("%.2lf ", matrix.matrix[i][j]);
        }
        printf("%.2lf\n", matrix.matrix[i][matrix.columns-1]);
    }
}