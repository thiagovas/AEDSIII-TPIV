/*
	Feito por Thiago Vieira
*/

#ifndef _utility_h
#define _utility_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* Função que retorna o maior valor entre a e b. */
int max(int a, int b);

/* Função que retorna o menor valor entre a e b. */
int min(int a, int b);

/* Função que aloca n posições de nBytes bytes e retorna um ponteiro de void. */
void* alloc(int n, size_t nBytes);

#endif
