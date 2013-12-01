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

typedef int*** matrix3d;

/* Método que imprime a matriz matrix na stream foutput. */
void printMatrix(matrix3d matrix, int x, int y, int z);

/* Método que desaloca a matriz matrix */
void freeMatrix(matrix3d *matrix, int x, int y, int z);

/* Método que aloca um espaço de memória para uma matriz de tamanho x*y*z */
void initMatrix(matrix3d *matrix, int x, int y, int z);

/* Função que retorna o valor de uma posição da matriz. */
int GetValueMatrix(matrix3d *matrix, int x, int y, int z);

/* Método que seta o valor de uma posição da matriz. */
void SetValueMatrix(matrix3d *matrix, int x, int y, int z, int value);

#endif
