/*
	Feito por Thiago Vieira
*/
#include "graph.h"

/* Método que inicializa a estrutura graph */
void InitGraph(graph *g, int nNodes, int defaultValue)
{
	int i = 0;
	g->numberNodes = nNodes;
	g->nodes = (node*)alloc(nNodes, sizeof(node));
	
	for(i = 0; i < nNodes; i++)
	{
		g->nodes[i].value = defaultValue;
		g->nodes[i].edges = NULL;
		g->nodes[i].numAdjacents = 0;
	}
}

/* Método que adiciona uma edge do FromNode para ToNode. */
void AddEdge(graph *g, int FromNode, int ToNode, double cost)
{
	int tam = NumAdjacents(g, FromNode);
	size_t newtam = (tam+1)*sizeof(edge);
	
 	edge *tempPtr = (edge*)realloc(g->nodes[FromNode].edges, newtam);
 	
 	if(tempPtr == NULL)
 	{
 		// TODO: Printar uma msg de erro.
 		free(g->nodes[FromNode].edges);
 	}
 	g->nodes[FromNode].edges = tempPtr;
 	
	g->nodes[FromNode].edges[tam].value = -1;
	g->nodes[FromNode].edges[tam].from = FromNode;
	g->nodes[FromNode].edges[tam].to = ToNode;
	g->nodes[FromNode].edges[tam].cost = cost;
	g->nodes[FromNode].numAdjacents += 1;
}

/* Método usado para limpar a estrutura graph */
void ClearGraph(graph *g)
{
	int i = 0;
	for(i = 0; i < g->numberNodes; i++)
	{
		free(g->nodes[i].edges);
		g->nodes[i].edges = NULL;
		g->nodes[i].numAdjacents = 0;
	}
	free(g->nodes);
	g->nodes = NULL;
	g->numberNodes = 0;
}

/* Método que retorna o número de vértices do grafo */
int SizeGraph(graph g)
{ return g.numberNodes; }

/* Retorna o valor do vértice node. */
int ValueFromNode(graph *g, int node)
{
	if(g->nodes == NULL) return -1;
	
	return g->nodes[node].value;
}

/* Método, usado somente internamente do TAD, que retorna a edge de indice index da lista de FromNode. */
edge* GetEdge(graph *g, int FromNode, int index)
{
	if(FromNode < 0) return NULL;
	if(g->nodes == NULL || g->nodes[FromNode].edges == NULL) return NULL;
	if(index < 0 || index >= NumAdjacents(g, FromNode)) return NULL;
	
	return &(g->nodes[FromNode].edges[index]);
}

/* Função que retorna o custo de uma edge. */
double CostFromEdge(graph *g, int FromNode, int index)
{
	edge *retEdge = GetEdge(g, FromNode, index);
	
	if(retEdge == NULL) return -1;
	else return retEdge->cost;
}

/* Função que retorna o valor de uma edge. */
int ValueFromEdge(graph *g, int FromNode, int index)
{
	edge *retEdge = GetEdge(g, FromNode, index);
	
	if(retEdge == NULL) return -1;
	else return retEdge->value;
}

/* Retorna o ToNode da edge de indice index da lista de adjacencia de FromNode. */
int AdjacentNode(graph *g, int FromNode, int index)
{
	edge *retEdge = GetEdge(g, FromNode, index);
	
	if(retEdge == NULL) return -1;
	else return retEdge->to;
}

/* Retorna o número de adjacentes do vértice node. */
int NumAdjacents(graph *g, int node)
{
	return g->nodes[node].numAdjacents;
}

/* Método que edita o valor de um vértice */
void EditNodeValue(graph *g, int node, int newValue)
{
	g->nodes[node].value = newValue;
}

