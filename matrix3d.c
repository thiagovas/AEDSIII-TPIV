/*
    Feito por Thiago Vieira
*/

#include "matrix3d.h"

/* Método que imprime a matriz matrix na stream foutput. */
void printMatrix(matrix3d matrix, int x, int y, int z)
{
    int i, j, k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%d", matrix[i][j][0]);
            for(k = 1; k < z; k++)
                printf(" %d", matrix[i][j][k]);
            printf("\n");
        }
    }
    printf("\n");
}

/* Método que desaloca a matriz matrix */
void freeMatrix(matrix3d *matrix, int x, int y, int z)
{
    int i, j;
    
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            free((*matrix)[i][j]);
            (*matrix)[i][j] = NULL; //Para evitar dangling pointer;
        }
        free((*matrix)[i]);
        (*matrix)[i] = NULL; 
    }
    free(*matrix);
    *matrix = NULL; 
}

/* Método que aloca um espaço de memória para uma matriz de tamanho x*y*z */
void initMatrix(matrix3d *matrix, int x, int y, int z)
{
    int i, j;
    
    *matrix = (double***)alloc(x, sizeof(double**));
    for(i = 0; i < x; i++)
    {
        (*matrix)[i] = (double**)alloc(y, sizeof(double*));
        for(j = 0; j < y; j++)
            (*matrix)[i][j] = (double*)alloc(z, sizeof(double));
    }
}


/* Função que retorna o valor de uma posição da matriz. */
int GetValueMatrix(matrix3d *matrix, int x, int y, int z)
{
	return (*matrix)[x][y][z];
}

/* Método que seta o valor de uma posição da matriz. */
void SetValueMatrix(matrix3d *matrix, int x, int y, int z, int value)
{
	(*matrix)[x][y][z] = value;
}

