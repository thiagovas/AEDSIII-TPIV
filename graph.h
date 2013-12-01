/*
    Feito por Thiago Vieira
*/

#ifndef _graph_h
#define _graph_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "vector.h"
#include "utility.h"

typedef struct{
	int value;
	int from, to;
	double cost;
} edge;

typedef struct{
	edge *edges;
	int value, numAdjacents;
} node;

typedef struct{
	node *nodes;
	int numberNodes; //Number of nodes
} graph;

/* Método que inicializa a estrutura graph */
void InitGraph(graph *g, int nNodes, int defaultValue);

/* Método que adiciona uma edge do FromNode para ToNode. */
void AddEdge(graph *g, int FromNode, int ToNode, double cost);

/* Método usado para limpar a estrutura graph */
void ClearGraph(graph *g);

/* Método que retorna o número de vértices do grafo */
int SizeGraph(graph g);

/* Método, usado somente internamente do TAD, que retorna a edge de indice index da lista de FromNode. */
edge* GetEdge(graph *g, int FromNode, int index);

/* Função que retorna o custo de uma edge. */
double CostFromEdge(graph *g, int FromNode, int index);

/* Função que retorna o valor de uma edge. */
int ValueFromEdge(graph *g, int FromNode, int index);

/* Retorna o ToNode da edge de indice index da lista de adjacencia de FromNode. */
int AdjacentNode(graph *g, int FromNode, int index);

/* Retorna o número de adjacentes do vértice node. */
int NumAdjacents(graph *g, int node);

/* Retorna o valor do vértice node. */
int ValueFromNode(graph *g, int node);

/* Método que edita o valor de um vértice */
void EditNodeValue(graph *g, int node, int newValue);

#endif
