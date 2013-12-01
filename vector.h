/*
    Made by Thiago Vieira
*/

#ifndef _vector_h
#define _vector_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utility.h"

typedef struct{
	int value;
} item;

typedef struct{
	item *list;
	int sizeObj; //Size of this object
} vector;

/* Método que inicializa a estrutura vector e já preenche as posições com o defaultValue. */
void InitVector(vector *obj, int size, int defaultValue);

/* Método que inicializa um vector vazio. */
void InitEmptyVector(vector *obj);

/* Método que insere um novo elemento no fim do vector obj. */
void Push_back(vector *obj, int value);

/* Método que insere um novo elemento no inicio do vector. */
void Push_front(vector *obj, int value);

/* Método que retira o último elemento do vector. */
void Pop_back(vector *obj);

/* Método que imprime os valores do vector. */
void PrintVector(vector obj);

/* Função que retorna o tamanho do vector. */
int SizeVector(vector obj);

/* Função que retorna se o vector esta vazio */
int Empty(vector *obj);

/* Método que limpa o vector. */
void ClearVector(vector *obj);

/* Função que retorna o valor do elemento de posição index do vector. */
int GetValue(vector *obj, int index);

/* Método que seta o valor de uma posição do vector. */
void SetValue(vector *obj, int index, int value);

/* Método que edita o valor de um elemento do vector. */
void EditItem(vector *obj, int index, int newValue);

#endif

