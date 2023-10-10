#include "s21_3DV_v1.h"

int s21_parsing(data_t *data, char *model_file_name) {
  int flag = 1;
  char string_file[S_SIZE] = {'\0'};
  FILE *f = NULL;
  int row = 1;
  matrix_t mat = {0};
  int polygonsCounter = 0;
  if (s21_parsingDataSize(data, model_file_name)) { ///^
    polygon_t *polygon = (polygon_t *)calloc((data->count_of_facets), sizeof(polygon_t));
    if (polygon != NULL) {
      if (s21_create_matrix(data->count_of_vertexes + 1, 3, &mat) == 0) {
        if ((f = fopen(model_file_name, "r")) != NULL) {
          while (flag && fgets(string_file, S_SIZE, f)) {
            int step = 0;
            if (s21_parsingСonditions('v', string_file, &step)) {
              for (int i = 0; i < 3; i++) {
                int s = 0;
                double num = 0;
                s21_string_to_double(&string_file[step], &s, &num);
                mat.matrix[row][i] = num;
                step += s;
              }
              row++;
            } else if (s21_parsingСonditions('f', string_file, 0)) {
              if (s21_findPolygons(&polygon[polygonsCounter], string_file)) {
                polygonsCounter++;
              } else {
                flag = 0;
              }
            }
            string_file[0] = 0;
          }
          fclose(f);
          if (flag) {
            data->matrix_3d = mat;
            data->polygons = polygon;
            if (!s21_massivPolygons(data)) {
              flag = 0;
            }
          }
        } else {
          flag = 0;
        }
      } else {
        flag = 0;
      }
    } else {
      flag = 0;
    }
  } else {
    flag = 0;
  }
  if (flag) {
    data->massiv =
        (double *)calloc((data->count_of_vertexes + 1) * 3, sizeof(double));
    data->massiv_const =
        (double *)calloc((data->count_of_vertexes + 1) * 3, sizeof(double));
    if (data->massiv_const != NULL && data->massiv != NULL) {
      s21_matrix_to_massiv(data->matrix_3d, data->massiv, data->massiv_const);
      s21_array_minmax(*data, &data->max_coord);
    } else {
      flag = 0;
    }
  }
  return flag;
}

int s21_parsingDataSize(data_t *data, char *model_file_name) {   //Парсинг количества вершин и полигонов
  int flag = 1;
  FILE *f;
  char string_file[S_SIZE] = {'\0'};
  if ((f = fopen(model_file_name, "r")) != NULL) {
    while (fgets(string_file, S_SIZE, f)) {
      if (s21_parsingСonditions('v', string_file, NULL)) {
        data->count_of_vertexes++;
      } else if (s21_parsingСonditions('f', string_file, NULL)) {
        data->count_of_facets++;
      }
      string_file[0] = 0;
    }
    fclose(f);
  } else {
    flag = 0;
  }
  return flag;
}

int s21_parsingСonditions(char c, char *string_file, int *step) { // Соответсвие условиям парсинга
  int flag = 0;
  int s = 0;
  s21_skip_space(string_file, &s);
  if (string_file[s] == c) {
    if (string_file[s + 1] == ' ') {
      flag = 1;
    }
  }
  step ? *step = s + 2 : 0;
  return flag;
}

int s21_findPolygons(polygon_t *polygons, char *string_file) { // Парсинг полигонов
  int step = 0;
  int i = 0;
  int flag = 1;
  polygons->vertexes = (unsigned int *)calloc(128, sizeof(unsigned int));
  polygons->numbers_of_vertexes_in_facets = 0;
  if (polygons->vertexes != NULL) {
    while (step < (int)strlen(string_file)) {
      int s = 0;
      double num = 0;
      if (s21_string_to_double(&string_file[step], &s, &num)) {
        step += s;
        if (string_file[step - s21_num_digits((int)num) - 1] == ' ') {
          if ((int) num < 0) num = num*(-1);
          if (polygons->numbers_of_vertexes_in_facets != 0) {
            polygons->vertexes[i++] = (int) num;
          }
          polygons->vertexes[i++] = (int) num;
          polygons->numbers_of_vertexes_in_facets++;
        }
      }
      step++;
    }
    if (polygons->numbers_of_vertexes_in_facets > 1) {
      polygons->vertexes[i++] = polygons->vertexes[0];
    }
  } else {
    flag = 0;
  }
  return flag;
}

int s21_matrix_to_massiv(matrix_t matrix, double *massiv, double *massiv2) { // Перевод из матрицы в массив
  int flag = 1;
  int massivSize = 0;
  if (massiv != NULL) {
    for (int i = 0; i < matrix.rows; i++) {
      for (int j = 0; j < matrix.columns; j++) {
        massiv[massivSize] = massiv2[massivSize] = matrix.matrix[i][j];
        massivSize++;
      }
    }
  } else {
    flag = 0;
  }
  return flag;
} 

void s21_array_minmax(data_t data, double *max_coord) { // МаксМин array
  *max_coord = 0;
  double max_array = 0;
  double min_array = 0;
  for (int i = 0; i < data.count_of_vertexes; i++) {
    if (data.massiv[i] > max_array) {
      max_array = data.massiv[i];
    }
    if (data.massiv[i] < min_array) {
      min_array = data.massiv[i];
    }
  }
  *max_coord = fabs(min_array) > max_array ? fabs(min_array) : max_array;
  *max_coord *= 1.2f;
}

int s21_massivPolygons(data_t *data) { // Массив полигонов
  int flag = 1;
  for (int i = 0; i < data->count_of_facets; i++) {
    data->sizePolygons += data->polygons[i].numbers_of_vertexes_in_facets * 2;
  }
  data->massivPolygons =
      (unsigned int *)calloc(data->sizePolygons, sizeof(unsigned int));

  if (data->massivPolygons != NULL) {
    data->sizePolygons = 0;
    for (int i = 0; i < data->count_of_facets; i++) {
      for (int j = 0; j < data->polygons[i].numbers_of_vertexes_in_facets * 2; j++) {
        printf("%d\n", data->polygons[i].vertexes[j]); ///!!!!!
        if (data->polygons[i].vertexes[j] < 0){
           data->polygons[i].vertexes[j] = data->polygons[i].vertexes[j]*(-1);
        } 
        data->massivPolygons[data->sizePolygons++] = data->polygons[i].vertexes[j];
      }
    }
  } else {
    flag = 0;
  }
  return flag;
}

int s21_num_digits(int num) { // Возвращает Количество цифр в числе
  int count = 0;
  if (num == 0) {
    count = 1;
  } else if (num < 0) {
    count++;
    num = -num;
  }
  while (num > 0) {
    count++;
    num /= 10;
  }
  return count;
}

int s21_is_digit(char c) { // Поиск цифры
  int flag = 0;
  if (c >= '0' && c <= '9') {
    flag = 1;
  }
  return flag;
}

int s21_skip_space(char *str, int *step) { //Пропуск пробелов
  int flag = 0;
  *step = 0;
  while (s21_is_space(str[*step]) == 1) {
    (*step)++;
    flag = 1;
  }
  return flag;
}

int s21_is_space(char c) { //Поиск пробела
  int flag = 0;
  if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\v') || (c == '\f') ||
      (c == '\r')) {
    flag = 1;
  }
  return flag;
}

void s21_remove_data(data_t *data) { // Удаление структуры data, освобождение памяти
  s21_remove_massiv(data);
  s21_remove_matrix(&data->matrix_3d);
  s21_remove_polygons(data);
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->sizePolygons = 0;
  data->max_coord = 0;
  data->matrix_3d.matrix = NULL;
}

void s21_remove_massiv(data_t *data) {  // Удаление массивов, освобождение памяти
  if (data->massiv != NULL) {
    free(data->massiv);
  }
  if (data->massiv_const != NULL) {
    free(data->massiv_const);
  }
  data->massiv = NULL;
  data->massiv_const = NULL;
}

void s21_remove_polygons(data_t *data) { // Удаление полигонов, освобождение памяти
  if (data->polygons != NULL) {
    for (int i = 0; i < data->count_of_facets; i++) {
      if (data->polygons[i].vertexes != NULL) {
        free(data->polygons[i].vertexes);
      }
    }
    free(data->polygons);
  }
  if (data->massivPolygons != NULL) {
    free(data->massivPolygons);
  }
  data->polygons = NULL;
  data->massivPolygons = NULL;
}

int s21_string_to_double(char *str, int *step, double *number) { // Перевод из строки в double
  int flag = 1;
  double num = 0;
  int dot = 0;
  int i = 0;
  int neg = 1;
  s21_skip_space(str, &i);
  if (s21_is_digit(str[i]) == 0) {
    if (str[i] == '-' || str[i] == '+') {
      if (str[i] == '-') {
        neg = -1;
      }
      i++;
    } else {
      flag = 0;
    }
  }
  if (flag == 1) {
    for (;; i++) {
      if (s21_is_digit(str[i]) == 0) {
        if (str[i] != '.') {
          break;
        }
      }
      if (str[i] == '.') {
        dot = 10;
      }
      if (dot == 0) {
        num = (num * 10) + (double)(str[i] - '0');
      } else if (str[i] != '.') {
        num += (double)(str[i] - '0') / dot;
        dot *= 10;
      }
    }
  }
  *step = i;
  if (s21_Euler_search(&str[i], &i, &num)) {
    *step = i;
  }
  *number = num * neg;
  return flag;
}

int s21_Euler_search(char *str, int *step, double *num) { // Находит число Эйлера
  int e = 0;
  int negative = 1;
  int flag = 1;
  int i = 0;
  if (str[i] == 'e' || str[i] == 'E') {
    i++;
    if (str[i] && str[i] == '-') {
      negative = -1;
      i++;
    } else if (str[i] && str[i] == '+') {
      negative = 1;
      i++;
    }
    if (str[i] && s21_is_digit(str[i]) == 1) {
      e = (e * 10) + (int)(str[i] - '0');
      i++;
    } else {
      flag = 0;
    }
    if (str[i] && s21_is_digit(str[i]) == 1) {
      e = (e * 10) + (int)(str[i] - '0');
    }
  } else {
    flag = 0;
  }
  double ten = 10;
  if (flag == 1) {
    if (negative == -1) {
      ten = 0.1;
    }
    for (int i = 0; i < e; i++) {
      *num *= ten;
    }
  }
  *step = i;

  return flag;
}

// int main(){
//   data_t data;
//   data.count_of_vertexes = 0;
//   data.sizePolygons = 0;
//   data.count_of_facets = 0;
//   char test_1[] = "../../files_obj/cube.obj";
//   char test_2[] = "../../files_obj/skull.obj"; 
//   char test_3[] = "../../files_obj/Skull_v3.obj";



//   int n = s21_parsing(&data, test_2);
//   // printf("@%d %d %d\n", data.count_of_vertexes, data.count_of_facets, data.sizePolygons);
//   // for (int i = 0; i < data.sizePolygons; i++){
//   //   printf("%d\n", data.massivPolygons[i]);
//   // }
//   return 0;
// }

// add to transform
void s21_scale(data_t *data, long double scale, long double scale_prev) {
  for (int i = 0; data->massiv && i < (data->count_of_vertexes + 1) * 3; i++) {
    data->massiv[i] *= scale / scale_prev;
  }
}