/*
	Feito por Thiago Vieira
*/

#include "solver.h"

void solve(FILE *foutput, graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack)
{
	int i, j, p, maxValue, index;
	matrix3d m;
	path *before;
	pthread_t *thread = (pthread_t*) alloc(v, sizeof(pthread_t));
	thread_data *data = (thread_data*) alloc(v, sizeof(thread_data));
	
	initMatrix(&m, d+1, v, wKnapsack+1);
	BaseCase(&m, tPesos, tQualidades, v, wKnapsack);
	
	for(i = 1; i <= d; i++)
	{
		for(j = 0; j < v; j++)
		{
			p = floor(((double)wKnapsack)/GetValue(tPesos, j));
			
			data[j].m = &m;
			data[j].g = g;
			data[j].tPesos = tPesos;
			data[j].tQualidades = tQualidades;
			data[j].i = i;
			data[j].j = j;
			data[j].p = p;
			data[j].w = wKnapsack;
			
			pthread_create(&thread[j], NULL, solveKnapsackThread, &data[j]);
			//solveKnapsack(&m, g, tPesos, tQualidades, i, j, k, p);
		}
		
		for(j = 0; j < v; j++)
			pthread_join(thread[j], NULL);
	}
	
	/* BEGIN - Pegar a mochila com maior valor */
	maxValue = GetValueMatrix(&m, d, 0, wKnapsack);
	index = 0;
	for(i = 1; i < v; i++)
		if(GetValueMatrix(&m, d, i, wKnapsack) > maxValue)
		{
			maxValue = GetValueMatrix(&m, d, i, wKnapsack);
			index = i;
		}
	/* END - Pegar a mochila com maior valor */
	
	/* BEGIN - Imprimir resultado*/
	fprintf(foutput, "%d", maxValue);
	before = GetPath(&m, d, index, wKnapsack)->before;
	do{
		fprintf(foutput, " %d %d", before->vertex+1, before->quant);
		before = before->before;
	}while(before != NULL);
	fprintf(foutput, "\n");
	/* END - Imprimir resultado */
	
	free(thread);
	free(data);
	freeMatrix(&m, d+1, v, wKnapsack+1);
}

void* solveKnapsackThread(void *input)
{
	int k, l, h, temp, nAdj;
	
	thread_data data = *((thread_data*)input);
	matrix3d *m = data.m;
	graph *g = data.g;
	vector *tPesos = data.tPesos;
	vector *tQualidades = data.tQualidades;
	int i = data.i, j = data.j, p = data.p, wKnapsack = data.w;
	
	for(k = 0; k <= wKnapsack; k++)
	{
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
	
	pthread_exit(NULL);
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
	int i, j;
	for(i = 0; i < v; i++)
	{
		/* Inicializando  */
		SetValueMatrix(m, 0, i, 0, 0);
		SetVertexPath(m, 0, i, 0, i);
		SetQuantityPath(m, 0, i, 0, 0);
		SetBeforePath(m, 0, i, 0, NULL);
		
		for(j = 1; j <= w; j++)
		{	
			SetValueMatrix(m, 0, i, j, 0);
			if(GetValue(tPesos, i) <= j)
			{
				if(GetValueMatrix(m, 0, i, j) < GetValueMatrix(m, 0, i, j-GetValue(tPesos, i))+GetValue(tQualidades, i))
				{
					SetValueMatrix(m, 0, i, j, GetValueMatrix(m, 0, i, j-GetValue(tPesos, i))+GetValue(tQualidades, i));
					SetQuantityPath(m, 0, i, j, 1+GetQuantityPath(m, 0, i, j-GetValue(tPesos, i)));
				}
			}
		}
	}
}

