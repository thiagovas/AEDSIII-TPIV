/*
	Feito por Thiago Vieira
*/

#ifndef _queue_h
#define _queue_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pair.h"
#include "vector.h"

typedef struct itemqueue{
	int_pair value;
	struct itemqueue *next;
} item_queue;

typedef struct{
	item_queue *begin;
} queue;

/* Método que inicializa a queue. */
void InitQueue(queue *nodes);

/* Método que insere um novo valor na queue. */
void PushQueue(queue *nodes, int_pair newValue);

/* Função que verifica se a queue está vazia */
int EmptyQueue(queue nodes);

/* Função que retorna o primeiro elemento da queue. */
int_pair FrontQueue(queue nodes);

/* Método que retira o elemento da frente da queue. */
void PopQueue(queue *nodes);

#endif
