/*
	Feito por Thiago Vieira
*/

#include "utility.h"

/* Função que retorna o maior valor entre a e b. */
int max(int a, int b)
{
	return a > b ? a : b;
}

/* Função que retorna o menor valor entre a e b. */
int min(int a, int b)
{
	return a < b ? a : b;
}

/* Função que aloca n posições de nBytes bytes e retorna um ponteiro de void. */
void* alloc(int n, size_t nBytes)
{
    void *ptr = calloc(n, nBytes);
    if(ptr == NULL)
    {
        printf("Error: Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
