#ifndef S21_3DV_V1_H
#define S21_3DV_V1_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/s21_matrix.h"

#define S_SIZE 1024

typedef struct facets {                // структура для хранения полигонов
  unsigned int *vertexes;              // кол-во вершин не может быть отрицательным
  int numbers_of_vertexes_in_facets;   // кол-во вершин необходимых для соединения
} polygon_t;

typedef struct data {                  // структура с количеством вершин и полигонов
  int count_of_vertexes;               // кол-во вершин
  int count_of_facets;                 // кол-во полигонов соединений
  double *massiv;
  double max_coord;
  matrix_t matrix_3d;                  // структура матриц  
  polygon_t *polygons;                 // структура полигонов
  unsigned int *massivPolygons;        // массив полигонов не может быть отрицательным
  unsigned int sizePolygons;           // размер полигонов не может быть отрицательным
  double *massiv_const;
} data_t;

int s21_parsing(data_t *data, char *model_file_name);                        // Главный парсинг
int s21_parsingDataSize(data_t *data, char *model_file_name);                // Парсинг количества вершин и полигонов
int s21_parsingСonditions(char c, char *string_file, int *step);             // Соответсвие условиям парсинга
int s21_findPolygons(polygon_t *polygons, char *string_file);                // Парсинг полигонов

int s21_massivPolygons(data_t *data);                                        // Массив полигонов
int s21_matrix_to_massiv(matrix_t matrix, double *massiv, double *massiv2);  // Перевод из матрицы в массив
void s21_array_minmax(data_t data, double *max_coord);                       // МаксМин array

void s21_remove_data(data_t *data);                                          // Удаление стуктуры data, освобождение памяти
void s21_remove_massiv(data_t *data);                                        // Удаление массивов, освобождение памяти
void s21_remove_polygons(data_t *data);                                      // Удаление полигонов, освобождение памяти

int s21_string_to_double(char *str, int *step, double *number);             // Перевод из строки в double
int s21_Euler_search(char *str, int *step, double *num);                    // Находит число Эйлера
int s21_is_digit(char c);                                                   // Поиск цифры
int s21_num_digits(int num);                                                // Возвращает Количество цифр в числе
int s21_skip_space(char *str, int *step);                                   // Пропуск пробелов
int s21_is_space(char c);                                                   // Поиск пробела

void s21_scale(data_t *data, long double scale, long double scale_prev);  

#endif //S21_3DV_V1_H
