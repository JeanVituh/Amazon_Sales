#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED

#include "dados.h"

void insertionSortPorPreco(AmazonSales produtos[], int n, int ordem);
void insertionSortPorRating(AmazonSales produtos[], int n, int ordem);
void insertionSortPorDesconto(AmazonSales produtos[], int n, int ordem);
int removerDuplicatas(AmazonSales* produtos, int count);
#endif // ORDENACAO_H_INCLUDED
