#include "parcer.h"

int isdouble(char ch){
    int result = 0;
    if ((ch <= 57 && ch >= 48) || ch == 46 || ch == '-') result = 1;
    return result;
}

int isint(char ch){
    int result = 0;
    if ((ch <= 57 && ch >= 48) || ch == '-') result = 1;
    return result;
}

double max_from_axes(double x, double y, double z){
  double result = y;
  if (x > y) {
    result = x;
    if (z > x) result = z;
  }
  return result;
}
void find_max_min(main_data *data){
  data->max_X = data->arr_ver->matrix[0][0];
  data->max_Y = data->arr_ver->matrix[0][1];
  data->max_Z = data->arr_ver->matrix[0][2];
  data->min_X = data->arr_ver->matrix[0][0];
  data->min_Y = data->arr_ver->matrix[0][1];
  data->min_Z = data->arr_ver->matrix[0][2];

  for (unsigned int i = 0; i < data->count_ver; i++){
      if (fabs(data->arr_ver->matrix[i][0]) > data->max_X) data->max_X = fabs(data->arr_ver->matrix[i][0]);
      if (fabs(data->arr_ver->matrix[i][1]) > data->max_Y) data->max_Y = fabs(data->arr_ver->matrix[i][1]);
      if (fabs(data->arr_ver->matrix[i][2]) > data->max_Z) data->max_Z = fabs(data->arr_ver->matrix[i][2]);
      if (fabs(data->arr_ver->matrix[i][0]) < data->min_X) data->min_X = fabs(data->arr_ver->matrix[i][0]);
      if (fabs(data->arr_ver->matrix[i][1]) < data->min_Y) data->min_Y = fabs(data->arr_ver->matrix[i][1]);
      if (fabs(data->arr_ver->matrix[i][2]) < data->min_Z) data->min_Z = fabs(data->arr_ver->matrix[i][2]);
  }
}
void centr(main_data *data){
  if (data->count_ver > 0){
    double center_x = data->min_X+(data->max_X-data->min_X)/2;
    double center_y = data->min_Y+(data->max_Y-data->min_Y)/2;
    double center_z = data->min_Z+(data->max_Z-data->min_Z)/2;
    for (unsigned int i = 0; i < data->count_ver; i++){
      data->arr_ver->matrix[i][0] -= center_x;
      data->arr_ver->matrix[i][1] -= center_y;
      data->arr_ver->matrix[i][2] -= center_z;
    }
  }
}

void counter(main_data *data, FILE *file){              // считаем вершины и соединения  
    char buffer[BUF_SIZE];
    while (fgets(buffer, BUF_SIZE, file)) {
        if (buffer[0] == 'v' && buffer[1] == ' '){
            data->count_ver += 1;
            // if (data->arr_count_steps[data->step_index] != 0){
                // unsigned *temp = data->arr_count_steps;
                // data->arr_count_steps = realloc(data->arr_count_steps, (data->step_index+1) * sizeof(unsigned));
                // if (data->arr_count_steps) data->step_index++;
                // else free(temp);
            // }
        }
        else if (buffer[0] == 'f'){
            data->count_edge += 1;
            data->arr_count_steps[data->step_index] += 1;
        }
    }
}

void v_parcer(main_data *data, char *str){             // парсим в структуру координаты вершин
    char temp_buffer[BUF_SIZE];
    int k = 0; // temp_buffer index
    short num_flag = 0;
    short index = 0;
    for (int i = 1; str[i] != '\0'; i++){
        if (isdouble(str[i])){
            temp_buffer[k] = str[i];
            temp_buffer[k+1] = '\0';
            num_flag = 1;
            k++;
        }
        else if ((str[i] == ' ' && num_flag == 1) || str[i] == '\n'){
            data->arr_ver->matrix[data->index_v][index] = atof(temp_buffer);
            index++;
            num_flag = 0;
            k = 0;
        }
    }
}

int counter_points_in_f(char *str){
    int result = 0;
    char temp_buffer[BUF_SIZE];
    int k = 0; // temp_buffer index
    int num_flag = 0;
    short slesh_flag = 0;
    for (int i = 1; str[i] != '\0'; i++){
        if (isint(str[i]) && slesh_flag == 0 && str[i] != '-'){
            temp_buffer[k] = str[i];
            temp_buffer[k+1] = '\0';
            num_flag = 1;
            k++;
        }
        else if (num_flag == 1 && (str[i] == '\n' || str[i] == '\0' || str[i] == ' ')){
            result++;
            num_flag = 0;
            slesh_flag = 0;       
        }
        else if (str[i] == '/'){
            slesh_flag = 1;
        }
    }
    return result;
}

void parcer_f(main_data *data,char *str){
    char temp_buffer[BUF_SIZE];
    int k = 0; // temp_buffer index
    int num_flag = 0;
    short slesh_flag = 0;
    int j = 0;
    int size = (int) counter_points_in_f(str);
    if (s21_create_matrix(1, size, &data->poligons[data->index_f]) == 0){
        for (int i = 1; str[i] != '\0'; i++){
            if (isint(str[i]) && slesh_flag == 0){
                temp_buffer[k] = str[i];
                temp_buffer[k+1] = '\0';
                num_flag = 1;
                k++;
            }
            else if (num_flag == 1 && (str[i] == '\n' || str[i] == '\0' || str[i] == ' ')){
                int num = atoi(temp_buffer);
                if (num < 0 || num > data->count_ver) {
                    num*=-1;
                    // num = data->arr_count_steps[data->step_current]-num;
                    data->correct_obj = 0;
                }
                
                data->poligons[data->index_f].matrix[0][j] = (double)num-1;
                num_flag = 0;
                k = 0;
                slesh_flag = 0;
                j++;
            }
            else if (str[i] == '/')
                slesh_flag = 1;
        }
    }
}

void check_str_state(char *str, main_data *data){     // проверяем вершина или порядок (v ? f)
    if (str[0] == 'v' && str[1] == ' '){
        v_parcer(data, str);
        data->index_v++;
    }
    else if (str[0] == 'f'){
        parcer_f(data, str);
        data->index_f += 1;
    }
}

void reading_file(FILE *file, main_data *data){      // чтение строки из файла
    char buffer[BUF_SIZE];
    // int previos_f = 0;
    while (fgets(buffer, BUF_SIZE, file)) {
        check_str_state(buffer, data);
        // if (previos_f == 1 && buffer[0] == 'v' && buffer[1] == ' '){
        //     data->step_current+=1;
        //     previos_f = 0;
        // }
        // else if (buffer[0] == 'f') previos_f = 1;
    }
}

int parcer(char *path_to_file, main_data *data){    // основная функция парсинга
    data->correct_obj = 1;
    int result = 0;
    FILE *file = fopen(path_to_file, "r");
    if (file){
        data->arr_count_steps = malloc(1*sizeof(unsigned));
        counter(data, file);
        data->step_index+=1; // !
        fseek(file, SEEK_SET, 0);
        data->arr_ver = malloc(1 * sizeof(matrix_t));
        data->poligons = malloc(data->count_edge * sizeof(matrix_t));
        if (data->count_ver > 0 && data->count_edge > 0 && data->arr_ver && data->poligons)
            if (s21_create_matrix(data->count_ver, 3, data->arr_ver) == 0){
                reading_file(file, data);
                to_less_one(data);
                find_max_min(data);
                centr(data);
                result = 1;
            }
        fclose(file);
    }
    line_output(data->arr_count_steps, data->step_index);
    return result;
}

// scale
void scale(double scale, main_data *data){
  if (data->count_ver > 0){
      for (unsigned int i = 0; i < data->count_ver; i++){
            data->arr_ver->matrix[i][0] *= scale;
            data->arr_ver->matrix[i][1] *= scale;
            data->arr_ver->matrix[i][2] *= scale;
      }
  }
}

/* Перевод из градусов в радианы */
double grad_to_rad(double grad) {
    return (grad * PI) / (double) 180;
}
// rotate around z
 void rot_z(main_data *data, double angle){
    double angle_rad = grad_to_rad(angle);
    // double matrix[3][3];
    // matrix[0][0] = cos(angle);  matrix[0][1] = sin(angle); matrix[0][2] = 0;
    // matrix[1][0] = -sin(angle); matrix[1][1] = cos(angle); matrix[1][2] = 0;
    // matrix[2][0] = 0;           matrix[2][1] = 0;          matrix[2][2] = 1;
    for (int i = 0; i < (int) data->count_ver; i++){
      double x = data->arr_ver->matrix[i][0]*cos(angle_rad) + data->arr_ver->matrix[i][1]*sin(angle_rad) + data->arr_ver->matrix[i][2] *0;
      double y = data->arr_ver->matrix[i][0]*(-sin(angle_rad)) + data->arr_ver->matrix[i][1]*cos(angle_rad) + data->arr_ver->matrix[i][2]*0;
      double z = data->arr_ver->matrix[i][0]*0+ data->arr_ver->matrix[i][1]*0+ data->arr_ver->matrix[i][2]*1;
      data->arr_ver->matrix[i][0] = x;
      data->arr_ver->matrix[i][1] = y;
      data->arr_ver->matrix[i][2] = z;
    }
 }
 // rot around y
void rot_y(main_data *data, double angle){
     double angle_rad = grad_to_rad(angle);
     // double matrix[3][3];
     // matrix[0][0] = cos(angle);  matrix[0][1] = 0; matrix[0][2] = sin(angle);
     // matrix[1][0] = 0;           matrix[1][1] = 1; matrix[1][2] = 0;
     // matrix[2][0] = -sin(angle); matrix[2][1] = 0; matrix[2][2] = cos(angle);
     for (int i = 0; i < (int) data->count_ver; i++){
       double x = data->arr_ver->matrix[i][0]*cos(angle_rad) + data->arr_ver->matrix[i][1]*0 + data->arr_ver->matrix[i][2]*sin(angle_rad);
       double y = data->arr_ver->matrix[i][0]*0 + data->arr_ver->matrix[i][1]*1 + data->arr_ver->matrix[i][2]*0;
       double z = data->arr_ver->matrix[i][0]*(-sin(angle_rad))+ data->arr_ver->matrix[i][1]*0+ data->arr_ver->matrix[i][2]*cos(angle_rad);
       data->arr_ver->matrix[i][0] = x;
       data->arr_ver->matrix[i][1] = y;
       data->arr_ver->matrix[i][2] = z;
     }
  }
// rot around x
 void rot_x(main_data *data, double angle){
   double angle_rad = grad_to_rad(angle);
   // double matrix[3][3];
   // matrix[0][0] = 1;  matrix[0][1] = 0;          matrix[0][2] = 0;
   // matrix[1][0] = 0;  matrix[1][1] = cos(angle); matrix[1][2] = -sin(angle);
   // matrix[2][0] = 0;  matrix[2][1] = sin(angle); matrix[2][2] = cos(angle);
   for (int i = 0; i < (int) data->count_ver; i++){
     double x = data->arr_ver->matrix[i][0]*1 + data->arr_ver->matrix[i][1]*0 + data->arr_ver->matrix[i][2]*0;
     double y = data->arr_ver->matrix[i][0]*0 + data->arr_ver->matrix[i][1]*cos(angle_rad) + data->arr_ver->matrix[i][2]*(-sin(angle_rad));
     double z = data->arr_ver->matrix[i][0]*0+ data->arr_ver->matrix[i][1]*sin(angle_rad)+ data->arr_ver->matrix[i][2]*cos(angle_rad);
     data->arr_ver->matrix[i][0] = x;
     data->arr_ver->matrix[i][1] = y;
     data->arr_ver->matrix[i][2] = z;
   }
}
 // moove
 void moove(main_data *data, double a, double b){
   for (int i = 0; i < (int) data->count_ver; i++){
        data->arr_ver->matrix[i][0] += a;
        data->arr_ver->matrix[i][1] += b; 
   }
}

void remove_data(main_data *data){
    s21_remove_matrix(data->arr_ver);
    if (data->poligons){
        for (int i = 0; i < (int) data->count_edge; i++){
            s21_remove_matrix(&data->poligons[i]);
        }
    }
    free(data->poligons);
    free(data->arr_ver);
    free(data->arr_count_steps);
}   

void to_less_one(main_data *data){
  if (data->count_ver > 0){
      find_max_min(data);
      double x = data->max_X;
      double y = data->max_Y;
      double z = data->max_Z;
      double max_coord = max_from_axes(x, y, z);
      for (unsigned int i = 0; i < data->count_ver; i++){
            data->arr_ver->matrix[i][0] /= (max_coord+max_coord);
            data->arr_ver->matrix[i][1] /= (max_coord+max_coord);
            data->arr_ver->matrix[i][2] /= (max_coord+max_coord);
      }
  }
}

void output_poligons(main_data *data){
    for (int i = 0; i < data->count_edge; i++){
        for (int j = 0; j < data->poligons[i].columns; j++){
            printf("%d ", (int) data->poligons[i].matrix[0][j]);
        }
        printf("\n");
    }
}

void line_output(unsigned *arr, unsigned size){
    for (unsigned i = 0; i < size; i++){
        printf("%d$", arr[i]);
    }
    printf("\n");
}

// int main (){
//     main_data data;
//     data.count_ver = 0; data.count_edge = 0; data.index_v = 0; data.index_f = 0; data.step_index = 0; data.arr_count_steps[0] = 0; data.step_current = 0;
//     parcer("/Users/artemefimov/Documents/GitHub/3d-v1/3dViewer/files_obj/obj/Empty.obj", &data);
//     printf("v=%d f=%d max%.2lf\n", data.count_ver, data.count_edge, data.max_Y);
//     // output(*data.arr_ver);
//     // output_poligons(&data);
//     // line_output(data.arr_count_steps, data.step_index);
//     remove_data(&data);
//     return 0;
// }
