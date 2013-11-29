/*
	Feito por Thiago Vieira
*/

#include "queue.h"

/* Método que inicializa a queue. */
void InitQueue(queue *nodes)
{
	nodes->begin = (item_queue*)alloc(1, sizeof(item_queue));
	nodes->begin->next = NULL;
}

/* Método que insere um novo valor na queue. */
void PushQueue(queue *nodes, int_pair newValue)
{
	item_queue *newItem = (item_queue*)alloc(1, sizeof(item_queue));
	item_queue *temp = nodes->begin;
	
	while(temp->next != NULL)
		temp = temp->next;
	
	newItem->value = newValue;
	newItem->next = NULL;
	
	temp->next = newItem;
}

/* Função que verifica se a queue está vazia */
int EmptyQueue(queue nodes)
{
	return nodes.begin->next == NULL;
}

/* Função que retorna o primeiro elemento da queue. */
int_pair FrontQueue(queue nodes)
{
	if(nodes.begin->next == NULL) return make_intpair(-1, -1);
	return nodes.begin->next->value;
}

/* Método que retira o elemento da frente da queue. */
void PopQueue(queue *nodes)
{
	if(nodes == NULL || nodes->begin == NULL) return;
	
	item_queue *oldItem = nodes->begin;
	nodes->begin = oldItem->next;
	free(oldItem);
}

