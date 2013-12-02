/*
    Feito por Thiago Vieira
*/

#include "matrix3d.h"

/* Método que imprime a matriz matrix na stream foutput. */
void printMatrix(matrix3d m, int x, int y, int z)
{
    int i, j, k;
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%d", m.matrix[i][j][0]);
            for(k = 1; k < z; k++)
                printf(" %d", m.matrix[i][j][k]);
            printf("\n\n");
        }
    }
    printf("\n");
}

/* Método que desaloca a matriz matrix */
void freeMatrix(matrix3d *m, int x, int y, int z)
{
    int i, j;
    
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            free(m->matrix[i][j]);
            free(m->p[i][j]);
            m->matrix[i][j] = NULL; //Para evitar dangling pointer;
        	m->p[i][j] = NULL;
        }
        free(m->matrix[i]);
        free(m->p[i]);
        m->matrix[i] = NULL; 
    	m->p[i] = NULL;
    }
    free(m->matrix);
    free(m->p);
    m->matrix = NULL; 
	m->p = NULL;
}

/* Método que aloca um espaço de memória para uma matriz de tamanho x*y*z */
void initMatrix(matrix3d *m, int x, int y, int z)
{
    int i, j;
    
    m->matrix = (int***)alloc(x, sizeof(int**));
    m->p = (path***)alloc(x, sizeof(path**));
    for(i = 0; i < x; i++)
    {
        m->matrix[i] = (int**)alloc(y, sizeof(int*));
        m->p[i] = (path**)alloc(y, sizeof(path*));
        for(j = 0; j < y; j++)
        {
            m->matrix[i][j] = (int*)alloc(z, sizeof(int));
            m->p[i][j] = (path*)alloc(z, sizeof(path));
    	}
    }
}


/* Função que retorna o valor de uma posição da matriz. */
int GetValueMatrix(matrix3d *m, int x, int y, int z)
{
	return m->matrix[x][y][z];
}

/* Método que seta o valor de uma posição da matriz. */
void SetValueMatrix(matrix3d *m, int x, int y, int z, int value)
{
	m->matrix[x][y][z] = value;
}

/* Método que seta o valor do vertice de uma posição de path. */
void SetVertexPath(matrix3d *m, int x, int y, int z, int value)
{
	m->p[x][y][z].vertex = value;
}

/* Método que seta o valor da quantidade de uma posição de path. */
void SetQuantityPath(matrix3d *m, int x, int y, int z, int value)
{
	m->p[x][y][z].quant = value;
}

/* Método que seta o elemento anterior de uma posição de path. */
void SetBeforePath(matrix3d *m, int x, int y, int z, path *value)
{
	m->p[x][y][z].before = value;
}

/* Método que muda o elemento before de uma posição de path. */
void ChangeBeforePath(matrix3d *m, int x, int y, int z, int newX, int newY, int newZ)
{
	m->p[x][y][z].before = &m->p[newX][newY][newZ];
	m->p[x][y][z].vertex = y;
	m->p[newX][newY][newZ].vertex = newY;
}

/* Função que retorna o valor do vertice de uma posição de path. */
int GetVertexPath(matrix3d *m, int x, int y, int z)
{
	return m->p[x][y][z].vertex;
}

/* Função que retorna o valor da quantidade de uma posição de path. */
int GetQuantityPath(matrix3d *m, int x, int y, int z)
{
	return m->p[x][y][z].quant;
}

/* Função que retorna o elemento anterior de uma posição de path. */
path* GetBeforePath(matrix3d *m, int x, int y, int z)
{
	return m->p[x][y][z].before;
}

/* Função que retorna o valor do vertice de uma posição de path. */
int GetVertexPathAnother(path *p)
{
	return p->vertex;
}

/* Função que retorna a path da posição [x][y][z] */
path* GetPath(matrix3d *m, int x, int y, int z)
{
	return &(m->p[x][y][z]);
}
