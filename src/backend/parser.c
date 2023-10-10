#include "parser.h"

Texture textures[MAX_VERTICES];
Normal normals[MAX_VERTICES];

Vertex vertices[MAX_VERTICES];
Face faces[MAX_FACES];
int num_vertices = 0;
int num_faces = 0;
int num_textures = 0;
int num_normals = 0;

Matrix matrix_multiply(Matrix m1, Matrix m2) {
    Matrix result;
    result.rows = m1.rows;
    result.cols = m2.cols;
    result.data = malloc(result.rows * sizeof(float *));
    for (int i = 0; i < result.rows; i++) {
        result.data[i] = malloc(result.cols * sizeof(float));
        for (int j = 0; j < result.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < m1.cols; k++) {
                result.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return result;
}

void scale_vertex(float scale_factor, int vertex_index) {
    Matrix scale_matrix;
    scale_matrix.rows = 3;
    scale_matrix.cols = 3;
    scale_matrix.data = malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++) {
        scale_matrix.data[i] = malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++) {
            scale_matrix.data[i][j] = (i == j) ? scale_factor : 0;
        }
    }

    Matrix vertex_matrix;
    vertex_matrix.rows = 3;
    vertex_matrix.cols = 1;
    vertex_matrix.data = malloc(3 * sizeof(float *));
    vertex_matrix.data[0] = malloc(sizeof(float));
    vertex_matrix.data[0][0] = vertices[vertex_index].x;
    vertex_matrix.data[1] = malloc(sizeof(float));
    vertex_matrix.data[1][0] = vertices[vertex_index].y;
    vertex_matrix.data[2] = malloc(sizeof(float));
    vertex_matrix.data[2][0] = vertices[vertex_index].z;

    Matrix result_matrix = matrix_multiply(scale_matrix, vertex_matrix);
    vertices[vertex_index].x = result_matrix.data[0][0];
    vertices[vertex_index].y = result_matrix.data[1][0];
    vertices[vertex_index].z = result_matrix.data[2][0];

    for (int i = 0; i < vertex_matrix.rows; i++) {
        free(vertex_matrix.data[i]);
    }
    free(vertex_matrix.data);
    for (int i = 0; i < result_matrix.rows; i++) {
        free(result_matrix.data[i]);
    }
    free(result_matrix.data);
    for (int i = 0; i < scale_matrix.rows; i++) {
        free(scale_matrix.data[i]);
    }
    free(scale_matrix.data);
}

void parse_obj_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            if (sscanf(line, "v %f %f %f", &vertices[num_vertices].x, &vertices[num_vertices].y, &vertices[num_vertices].z) != 3) {
                printf("Error: Incorrect vertex data format in line: %s\n", line);
            } else {
                scale_vertex(2.0, num_vertices);
                num_vertices++;
            }
        } else if (line[0] == 'v' && line[1] == 't') {
            if (sscanf(line, "vt %f %f", &textures[num_textures].u, &textures[num_textures].v) != 2) {
                printf("Error: Incorrect texture coordinate data format in line: %s\n", line);
            } else {
                num_textures++;
            }
        } else if (line[0] == 'v' && line[1] == 'n') {
            if (sscanf(line, "vn %f %f %f", &normals[num_normals].i, &normals[num_normals].j, &normals[num_normals].k) != 3) {
                printf("Error: Incorrect normal data format in line: %s\n", line);
            } else {
                num_normals++;
            
                printf("Error: Incorrect normal data format\n");
            }
        } else if (line[0] == 'f') {
            int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
            if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3) == 9 ||
                sscanf(line, "f %d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3) == 6 ||
                sscanf(line, "f %d/%d %d/%d %d/%d", &v1, &vt1, &v2, &vt2, &v3, &vt3) == 6 ||
                sscanf(line, "f %d %d %d", &v1, &v2, &v3) == 3) {
                faces[num_faces].v1 = v1;
                faces[num_faces].v2 = v2;
                faces[num_faces].v3 = v3;
                num_faces++;
            } else {
                printf("Error: Incorrect face data format\n");
            }
        }
    }

    fclose(file);
}

//int main() {
//    parse_obj_file("bugatti.obj");
//    printf("Number of vertices: %d\n", num_vertices);
//    printf("Number of faces: %d\n", num_faces);
//    printf("Number of texture coordinates: %d\n", num_textures);
//    printf("Number of normals: %d\n", num_normals);

//    return 0;
//}
