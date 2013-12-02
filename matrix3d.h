/*
    Feito por Thiago Vieira
*/

#ifndef _matrix3d_h
#define _matrix3d_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vector.h"
#include "utility.h"

typedef struct sPath{
	int vertex, quant;
	struct sPath *before; 
} path;

typedef struct sMatrix{
	int ***matrix;
	path ***p;
} matrix3d;

/* Método que imprime a matriz matrix na stream foutput. */
void printMatrix(matrix3d m, int x, int y, int z);

/* Método que desaloca a matriz matrix */
void freeMatrix(matrix3d *m, int x, int y, int z);

/* Método que aloca um espaço de memória para uma matriz de tamanho x*y*z */
void initMatrix(matrix3d *m, int x, int y, int z);

/* Função que retorna o valor de uma posição da matriz. */
int GetValueMatrix(matrix3d *m, int x, int y, int z);

/* Método que seta o valor de uma posição da matriz. */
void SetValueMatrix(matrix3d *m, int x, int y, int z, int value);

/* Método que seta o valor do vertice de uma posição de path. */
void SetVertexPath(matrix3d *m, int x, int y, int z, int value);

/* Método que seta o valor da quantidade de uma posição de path. */
void SetQuantityPath(matrix3d *m, int x, int y, int z, int value);

/* Método que seta o elemento anterior de uma posição de path. */
void SetBeforePath(matrix3d *m, int x, int y, int z, path *value);

/* Método que muda o elemento before de uma posição de path. */
void ChangeBeforePath(matrix3d *m, int x, int y, int z, int newX, int newY, int newZ);

/* Função que retorna o valor do vertice de uma posição de path. */
int GetVertexPath(matrix3d *m, int x, int y, int z);

/* Função que retorna o valor da quantidade de uma posição de path. */
int GetQuantityPath(matrix3d *m, int x, int y, int z);

/* Função que retorna o elemento anterior de uma posição de path. */
path* GetBeforePath(matrix3d *m, int x, int y, int z);

/* Função que retorna a path da posição [x][y][z] */
path* GetPath(matrix3d *m, int x, int y, int z);

/* Função que retorna o valor do vertice de uma posição de path. */
int GetVertexPathAnother(path *p);

#endif
