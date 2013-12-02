/*
	Feito por Thiago Vieira
*/

#include "solver.h"

void solve(graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack)
{
	int i, j, k, p, maxValue, index;
	matrix3d m;
	path *before;
	
	initMatrix(&m, d+1, v, wKnapsack+1);
	BaseCase(&m, tPesos, tQualidades, v, wKnapsack);
	
	printf("OH %d %d %d\n", m.matrix[0][0][wKnapsack], GetValue(tPesos, 0), GetValue(tQualidades, 0));
	
	for(i = 1; i <= d; i++)
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
	
	maxValue = GetValueMatrix(&m, d, 0, wKnapsack);
	index = 0;
	for(i = 1; i < v; i++)
		if(GetValueMatrix(&m, d, i, wKnapsack) > maxValue)
		{
			maxValue = GetValueMatrix(&m, d, i, wKnapsack);
			index = i;
		}
	
	printf("%d", maxValue);
	before = GetPath(&m, d, index, wKnapsack);
	do{
		printf(" %d %d", before->vertex+1, before->quant);
		before = before->before;
	}while(before != NULL);
	printf("\n");
	
	freeMatrix(&m, d+1, v, wKnapsack+1);
}

void solveKnapsack(matrix3d *m, graph *g, vector *tPesos, vector *tQualidades, int i, int j, int k, int p)
{
	int l, h, temp, nAdj;
	
	SetValueMatrix(m, i, j, k, GetValueMatrix(m, i-1, j, k));
	SetVertexPath(m, i, j, k, j);
	SetQuantityPath(m, i, j, k, GetQuantityPath(m, i-1, j, k));
	SetBeforePath(m, i, j, k, GetBeforePath(m, i-1, j, k));
	for(l = 0; l <= p; l++)
	{
		nAdj = NumAdjacents(g, j);
		
		for(h = 0; h < nAdj; h++)
		{
			if(CostFromEdge(g, j, h) <= i && l*GetValue(tPesos, j) <= k)
			{
				temp = GetValueMatrix(m, i-CostFromEdge(g, j, h), AdjacentNode(g, j, h), k-l*GetValue(tPesos, j));
				if(GetValueMatrix(m, i, j, k) < l*GetValue(tQualidades, j)+temp)
				{
					SetValueMatrix(m, i, j, k, l*GetValue(tQualidades, j)+temp);
					SetQuantityPath(m, i, j, k, l);
					ChangeBeforePath(m, i, j, k, i-CostFromEdge(g, j, h), AdjacentNode(g, j, h), k-l*GetValue(tPesos, j));
				}
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
		SetVertexPath(m, 0, i, 0, i);
		SetQuantityPath(m, 0, i, 0, 0);
		SetBeforePath(m, 0, i, 0, NULL);
		
		for(j = 1; j <= w; j++)
		{
			SetValueMatrix(m, 0, i, j, 0);
			SetVertexPath(m, 0, i, j, i);
			SetQuantityPath(m, 0, i, j, 0);
			SetBeforePath(m, 0, i, j, NULL);
			for(l = 0; l < SizeVector(*tPesos); l++)
			{
				if(GetValue(tPesos, l) <= j)
				{
					if(GetValueMatrix(m, 0, i, j) < GetValueMatrix(m, 0, i, j-GetValue(tPesos, l))+GetValue(tQualidades, l))
					{
						SetValueMatrix(m, 0, i, j, GetValueMatrix(m, 0, i, j-GetValue(tPesos, l))+GetValue(tQualidades, l));
						SetQuantityPath(m, 0, i, j, 1+GetQuantityPath(m, 0, i, j-GetValue(tPesos, l)));
					}
				}
			}
		}
	}
}

