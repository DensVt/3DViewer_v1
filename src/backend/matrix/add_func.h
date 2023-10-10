#ifndef ADD_FUNC_H
#define ADD_FUNC_H

#include <stdio.h>

#include "s21_matrix.h"

void output_matrix(matrix_t matrix);
double gaus_det(double **matrix, int n);
void add_one_matrix(double **matrix, int n, double **new_matrix);
double minor_element(matrix_t matrix, int rows, int columns);
void copy_matrix(double **matrix, int n, double **new_matrix);

#endif