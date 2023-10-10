#ifndef PARCER_H
#define PARCER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./matrix/s21_matrix.h"
#define BUF_SIZE 1024
#define PI 3.14159265359

typedef struct main_struct {
  matrix_t *arr_ver;  // матрица вершин
  unsigned int index_v;
  matrix_t *poligons;  // массив матриц полигонов
  unsigned int index_f;
  unsigned int count_ver;   // количество вершин
  unsigned int count_edge;  // количество ребер
  double min_X;
  double max_X;
  double min_Y;
  double max_Y;
  double min_Z;
  double max_Z;
  double current_scale;
  unsigned *arr_count_steps;
  unsigned step_index;
  unsigned step_current;
  short correct_obj;
} main_data;

int isdouble(char ch);
int isint(char ch);

double max_from_axes(double x, double y, double z);
void find_max_min(main_data *data);
void centr(main_data *data);
void scale(double scale, main_data *data);

void parcer_f(main_data *data, char *str);
void v_parcer(main_data *data, char *str);
void check_str_state(char *str, main_data *data);
void counter(main_data *data, FILE *file);
void reading_file(FILE *file, main_data *data);
int parcer(char *path_to_file, main_data *data);

// trans
double grad_to_rad(double grad);
void scale(double scale, main_data *data);
void rot_z(main_data *data, double angle);
void rot_y(main_data *data, double angle);
void rot_x(main_data *data, double angle);
void moove(main_data *data, double a, double b);
void to_less_one(main_data *data);

void remove_data(main_data *data);
int counter_points_in_f(char *str);
// temp func
void output_poligons(main_data *data);
void line_output(unsigned *arr, unsigned size);

#endif
