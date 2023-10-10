#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000000
#define MAX_FACES 1000000

typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    int v1, v2, v3;
} Face;

typedef struct {
    int rows;
    int cols;
    float **data;
} Matrix;

typedef struct {
    float u, v;
} Texture;

typedef struct {
    float i, j, k;
} Normal;

extern Texture textures[MAX_VERTICES];
extern Normal normals[MAX_VERTICES];
extern Vertex vertices[MAX_VERTICES];
extern Face faces[MAX_FACES];
extern int num_vertices;
extern int num_faces;
extern int num_textures;
extern int num_normals;

Matrix matrix_multiply(Matrix m1, Matrix m2);
void scale_model(float scale_factor);
void parse_obj_file(const char *filename);

#endif // PARSER_H