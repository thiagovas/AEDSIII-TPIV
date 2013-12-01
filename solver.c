/*
	Feito por Thiago Vieira
*/

#include "solver.h"

void solve(graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack)
{
	int i, j, k, p;
	matrix3d m;
	
	initMatrix(&m, d, v, wKnapsack+1);
	BaseCase(&m, tPesos, tQualidades, v, wKnapsack);
	
	for(i = 1; i < d; i++)
	{
		for(j = 0; j < v; j++)
		{
			p = floor(((double)wKnapsack)/GetValue(tPesos, j));
			for(k = 0; k <= wKnapsack; k++)
			{
				solveKnapsack(&m, g, tPesos, tQualidades, i, j, k, p);
			}
		}
	}
	
	
	for(i = 0; i < v; i++)
		printf("%d ", GetValueMatrix(&m, d-1, i, wKnapsack));
	printf("\n");
	
	freeMatrix(&m, d, v, wKnapsack);
}

void solveKnapsack(matrix3d *m, graph *g, vector *tPesos, vector *tQualidades, int i, int j, int k, int p)
{
	int l, h, temp, nAdj;
	
	SetValueMatrix(m, i, j, k, 0);
	for(l = 0; l <= p; l++)
	{
		nAdj = NumAdjacents(g, j);
		
		for(h = 0; h < nAdj; h++)
		{
			if(CostFromEdge(g, j, h) <= i && l*GetValue(tPesos, j) <= k)
			{
				temp = GetValueMatrix(m, i-CostFromEdge(g, j, h), AdjacentNode(g, j, h), k-l*GetValue(tPesos, j));
				SetValueMatrix(m, i, j, k, max(GetValueMatrix(m, i, j, k), l*GetValue(tQualidades, j)+temp));
			}
		}
	}
}

/* Método que roda o caso base da dp, ou seja, quando d=0 */
void BaseCase(matrix3d *m, vector *tPesos, vector *tQualidades, int v, int w)
{
	int i, j, l;
	for(i = 0; i < v; i++)
	{
		SetValueMatrix(m, 0, i, 0, 0);
		for(j = 1; j <= w; j++)
		{
			SetValueMatrix(m, 0, i, j, 0);
			for(l = 0; l < SizeVector(*tPesos); l++)
				if(GetValue(tPesos, l) <= j)
					SetValueMatrix(m, 0, i, j, max(GetValueMatrix(m, 0, i, j), GetValueMatrix(m, 0, i, j-GetValue(tPesos, l))
						+GetValue(tQualidades, l)));
		}
	}
}

