#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "avl.h"
#include "dados.h"
#include "busca_binaria.h"
#include "ordenacao.h"
#include <stdbool.h>

int removerDuplicatas(AmazonSales* produtos, int count) {
    if (count < 2) {
        return count;
    }

    int novoTamanho = 1;
    // Começa a verificar a partir do segundo produto
    for (int i = 1; i < count; i++) {
        bool encontrado = false;
        for (int j = 0; j < novoTamanho; j++) {
            if (strcmp(produtos[i].product_id, produtos[j].product_id) == 0) {
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            produtos[novoTamanho] = produtos[i];
            novoTamanho++;
        }
    }
    return novoTamanho;
}
void insertionSortPorPreco(AmazonSales produtos[], int n, int ordem)
{
    int i, j;
    AmazonSales chave;
    for (i = 1; i < n; i++)
    {
        chave = produtos[i];
        j = i - 1;
        if (ordem == 1)// Crescente
        {
            while (j >= 0 && produtos[j].discounted_price > chave.discounted_price)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        else// Decrescente
        {
            while (j >= 0 && produtos[j].discounted_price < chave.discounted_price)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        produtos[j + 1] = chave;
    }
}

void insertionSortPorRating(AmazonSales produtos[], int n, int ordem)
{
    int i, j;
    AmazonSales chave;
    for (i = 1; i < n; i++)
    {
        chave = produtos[i];
        j = i - 1;
        if (ordem == 1)
        {
            while (j >= 0 && produtos[j].rating > chave.rating)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && produtos[j].rating < chave.rating)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        produtos[j + 1] = chave;
    }
}

void insertionSortPorDesconto(AmazonSales produtos[], int n, int ordem)
{
    int i, j;
    AmazonSales chave;
    for (i = 1; i < n; i++)
    {
        chave = produtos[i];
        j = i - 1;
        if (ordem == 1)
        {
            while (j >= 0 && produtos[j].discount_percentage > chave.discount_percentage)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && produtos[j].discount_percentage < chave.discount_percentage)
            {
                produtos[j + 1] = produtos[j];
                j = j - 1;
            }
        }
        produtos[j + 1] = chave;
    }
}
