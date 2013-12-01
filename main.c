/*
	Feito por Thiago Vieira
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "graph.h"
#include "vector.h"
#include "matrix3d.h"
#include "utility.h"

void solve(graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack);
/* Método que roda o caso base da dp, ou seja, quando d=0 */
void BaseCase(matrix3d *m, vector *tPesos, vector *tQualidades, int v, int w);
void solveKnapsack(matrix3d *m, graph *g, vector *tPesos, vector *tQualidades, int i, int j, int k, int p);


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Comando incorreto. Informe somente o arquivo de entrada seguido pelo arquivo de saida.\n");
		return 1;
	}
	
	int trees, d, wMochila, caminhos, k;
	int arvore, peso, qualidade;
	int u, v;
	graph g;
	vector tPesos, tQualidades;
	FILE *finput = fopen(argv[1], "r"), *foutput = fopen(argv[2], "w");
	
	fscanf(finput, "%d", &k);
	while(k-- > 0)
	{
		fscanf(finput, "%d %d %d %d", &trees, &d, &wMochila, &caminhos);
		InitGraph(&g, trees, 0);
		InitVector(&tPesos, trees, 0);
		InitVector(&tQualidades, trees, 0);
		
		// Lendo os pesos e qualidades das árvores.
		while(trees-- > 0)
		{
			fscanf(finput, "%d %d %d", &arvore, &peso, &qualidade);
			SetValue(&tPesos, arvore-1, peso);
			SetValue(&tQualidades, arvore-1, qualidade);
		}
		
		// Lendo o grafo da instância
		while(caminhos-- > 0)
		{
			fscanf(finput, "%d %d %d", &u, &v, &peso);
			AddEdge(&g, u-1, v-1, peso);
			AddEdge(&g, v-1, u-1, peso);
		}
		
		solve(&g, &tPesos, &tQualidades, d, SizeGraph(g), wMochila);
		ClearGraph(&g);
		ClearVector(&tPesos);
		ClearVector(&tQualidades);
	}
	
	fclose(finput);
	fclose(foutput);
	return 0;
}

void solve(graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack)
{
	int i, j, k, p;
	matrix3d m;
	
	initMatrix(&m, d, v, wKnapsack);
	BaseCase(&m, tPesos, tQualidades, v, wKnapsack);
	
	for(i = 1; i < d; i++)
	{
		for(j = 0; j < SizeGraph(*g); j++)
		{
			p = floor(((double)wKnapsack)/GetValue(tPesos, j));
			for(k = 0; k < wKnapsack; k++)
			{
				solveKnapsack(&m, g, tPesos, tQualidades, i, j, k, p);
			}
		}
	}
	
	freeMatrix(&m, d, v, wKnapsack);
}

/* Método que roda o caso base da dp, ou seja, quando d=0 */
void BaseCase(matrix3d *m, vector *tPesos, vector *tQualidades, int v, int w)
{
	int i, j, l;
	for(i = 0; i < v; i++)
	{
		SetValueMatrix(m, 0, i, 0, 0);
		for(j = 1; j < w; j++)
		{
			SetValueMatrix(m, 0, i, j, 0);
			for(l = 0; l < SizeVector(*tPesos); l++)
				if(GetValue(tPesos, l) <= j)
					SetValueMatrix(m, 0, i, j, max(GetValueMatrix(m, 0, i, j), GetValueMatrix(m, 0, i, j-GetValue(tPesos, l))
						+GetValue(tQualidades, l)));
		}
	}
}

void solveKnapsack(matrix3d *m, graph *g, vector *tPesos, vector *tQualidades, int i, int j, int k, int p)
{
	int l;
	
	for(l = 0; l < p; l++)
	{
		
	}
}
