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
#include "solver.h"

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
